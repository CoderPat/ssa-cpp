#ifndef UTILS_HPP__
#define UTILS_HPP__

#include "basic_line.hpp"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using block_type = std::vector<basic_line>;

// Based on http://stackoverflow.com/a/217605/2052998
std::string trim(std::string s);

std::vector<std::string> words_of(const std::string &s);

bool is_all_upper(const std::string &s);

/// Reads blocks of lines separated by blank lines. Preserves whitespace.
template <typename InputStream>
std::vector<block_type> read_blocks(InputStream &in) {
  std::vector<block_type> blocks;
  size_t lineno = 0;
  bool lastWasEmpty = false;

  for (std::string line; std::getline(in, line);) {
    ++lineno;

    if (line.empty() || std::all_of(line.begin(), line.end(), isspace)) {
      // skip empty lines at start
      if (blocks.empty()) continue;

      lastWasEmpty = true;
      continue;
    }

    if (line[0] == '\x12') {
      std::cout << "Warning: line break at line " << lineno << " may break the parser (true story)" << std::endl;
    }

    // In case the stream starts with a non-empty line
    if (lastWasEmpty || blocks.empty()) blocks.emplace_back();

    blocks.back().emplace_back(lineno, line);
    lastWasEmpty = false;
  }

  return blocks;
}

template <typename InputIt,
          typename Comp = std::equal_to<typename InputIt::value_type>>
auto group(InputIt it, InputIt et, Comp cmp = Comp()) {
  std::vector<std::vector<typename InputIt::value_type>> ret;

  for (; it != et; ) {
    auto iit = it+1;
    ret.push_back({*it});

    while (iit != et && cmp(*it, *iit)) {
      ret.back().emplace_back(*iit);
      ++iit;
    }

    it = iit;
  }

  return ret;
}

size_t count_words(const std::string &s);

#endif // UTILS_HPP__
