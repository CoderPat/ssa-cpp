#ifndef SUBTITLE_HPP__
#define SUBTITLE_HPP__

#include "subtitle_line.hpp"
#include "utils.hpp"

#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

class subtitle {
public:
  using content_type = std::vector<std::shared_ptr<subtitle_line>>;

  content_type::const_iterator begin() const;
  content_type::const_iterator end() const;

public:
  /// Constructs a subtitle from an input stream in SRT format
  template <typename InputStream>
  void from_srt(InputStream &in);

private:
  content_type lines_;
};

template <typename InputStream>
void subtitle::from_srt(InputStream &in) {
  using namespace std;

  lines_.clear(); // XXX: should we really clear the subtitle?

  vector<block_type> blocks {read_blocks(in)};
  map<int, vector<shared_ptr<subtitle_line>>> blockBySequenceNum;

  for (const auto &rawblock : blocks) {
    assert(!rawblock.empty() && "read_blocks creates empty blocks");

    if (rawblock.size() < 3) {
      clog << "Invalid block at line " << rawblock.front().lineno()
           << " - block is too small" << endl;
      continue;
    }

    auto sequenceNum = 0;
    try {
      sequenceNum = stoi(rawblock.front().line(), nullptr, 10);
    } catch (const std::invalid_argument &iaex) {
      clog << "Invalid block at line " << rawblock.front().lineno()
           << " - block does not start with a sequence number" << endl;
      continue;
    }
    auto &timeLine = rawblock[1].line();
    auto sep_pos = timeLine.find("-->");

    if (sep_pos == timeLine.npos) {
      clog << "Invalid block at line " << rawblock.front().lineno()
           << " - invalid time span" << endl;
      continue;
    }

    srt_time startTime {trim(timeLine.substr(0, sep_pos))};
    srt_time endTime {trim(timeLine.substr(sep_pos + sizeof("-->") - 1))};

    if (endTime < startTime) {
      clog << "Invalid block at line " << rawblock.front().lineno()
           << " - start time is after end time" << endl;
      continue;
    }

    float duration = endTime.to_millis() - startTime.to_millis();

    // Do an aproximate time estimation for each subtitle line
    // 1. Count the words
    vector<float> wordCount;
    float totalWordCount {0};
    for (size_t i {2}; i < rawblock.size(); ++i) {
      auto wc = count_words(rawblock[i].line());

      wordCount.emplace_back(wc);
      totalWordCount += wc;
    }

    // 2. Each line last for time proportional to word count. Skip the first two
    // lines (sequence number and duration)
    vector<shared_ptr<subtitle_line>> block;
    for (size_t i = 2; i < rawblock.size(); ++i) {
      srt_time newStartTime {
        startTime.to_millis() + static_cast<unsigned>(
            wordCount[i-2] / totalWordCount * duration)
      };

      block.push_back(
          make_shared<subtitle_line>(
              rawblock[i].lineno(),
              rawblock[i].line(),
              startTime,
              newStartTime));

      startTime = newStartTime;
    }

    auto it = blockBySequenceNum.find(sequenceNum);
    if (it != blockBySequenceNum.end()) {
      clog << "Duplicate sequence number at line " << rawblock.front().lineno()
           << " - skipping" << endl;
    }

    blockBySequenceNum.emplace_hint(it, sequenceNum, move(block));
  }

  for (const auto &block : blockBySequenceNum) {
    for (const auto &line : block.second) {
      lines_.push_back(line);
    }
  }
}

#endif // SUBTITLE_HPP__
