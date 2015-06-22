#include "utils.hpp"

#include <algorithm>
#include <string>

std::string trim(std::string s) {
  s.erase(s.begin(), std::find_if_not(s.begin(), s.end(), isspace));
  s.erase(std::find_if_not(s.rbegin(), s.rend(), isspace).base(), s.end());

  return s;
}

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
