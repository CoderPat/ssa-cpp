#include "utils.hpp"

#include <algorithm>
#include <string>

std::string trim(std::string s) {
  s.erase(s.begin(), std::find_if_not(s.begin(), s.end(), isspace));
  s.erase(std::find_if_not(s.rbegin(), s.rend(), isspace).base(), s.end());

  return s;
}

// (Mostly) a shameless copy of count_words below
std::vector<std::string> words_of(const std::string &s) {
  std::vector<std::string> words;
  auto it = s.cbegin();
  auto et = s.cend();

  // skip initial spaces
  it = std::find_if_not(it, et, isspace);

  while (it != et) {
    auto eet = std::find_if(it, et, isspace);
    words.emplace_back(it, eet);

    if (eet == et) break;

    it = std::find_if_not(eet, et, isspace);
  }

  return words;
}

// We don't take advantage of the previous function because it does
// unnecessary work
size_t count_words(const std::string &s) {
  size_t count = 0;
  auto it = s.cbegin();
  auto et = s.cend();

  // skip initial spaces
  it = std::find_if_not(it, et, isspace);

  while (it != et) {
    ++count;
    it = std::find_if(it, et, isspace);
    if (it == et) break;
    it = std::find_if_not(it, et, isspace);
  }

  return count;
}

bool is_all_upper(const std::string &s) {
  return std::all_of(s.cbegin(), s.cend(), [](char c) {
    return ispunct(c) || isspace(c) || isupper(c);
  });
}

