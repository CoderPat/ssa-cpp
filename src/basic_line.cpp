#include "basic_line.hpp"

basic_line::basic_line(size_t lineno, const std::string &line)
    : line_(line), lineno_(lineno) { }

const std::string& basic_line::line() const {
  return line_;
}

size_t basic_line::lineno() const {
  return lineno_;
}

basic_line::~basic_line() = default;
