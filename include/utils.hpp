#ifndef UTILS_HPP__
#define UTILS_HPP__

#include "basic_line.hpp"

#include <algorithm>
#include <string>
#include <vector>

using block_type = std::vector<basic_line>;

// Based on http://stackoverflow.com/a/217605/2052998
std::string trim(std::string s);

/// Reads blocks of lines separated by blank lines. Preserves whitespace.
template <typename InputStream>
std::vector<block_type> read_blocks(InputStream &in) {
  std::vector<block_type> blocks;
  std::string line;
  size_t lineno = 0;

  while (std::getline(in, line)) {
    ++lineno;

    if (trim(line).empty()) {
      if (!blocks.empty() && !blocks.back().empty())
        blocks.emplace_back();
      continue;
    }

    if (blocks.empty())
      blocks.emplace_back();

    blocks.back().emplace_back(lineno, line);
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
