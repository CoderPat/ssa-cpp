#include "dialogue_line.hpp"

dialogue_line::dialogue_line(size_t lineno, const std::string &line, const std::string &character)
    : basic_line(lineno, line)
    , character_(character) {}

const std::string &dialogue_line::character() const {
  return character_;
}

void dialogue_line::output_to(std::ostream &o) const {
  o << lineno() << ":[" << character() << "] " << line() << '\n';
}

