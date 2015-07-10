#ifndef DIALOGUE_LINE_HPP__
#define DIALOGUE_LINE_HPP__

#include "basic_line.hpp"
#include <string>

class dialogue_line : public basic_line {
  std::string character_;

public:
  dialogue_line(size_t lineno, const std::string &line, const std::string &character);

  void output_to(std::ostream &o) const override;

  const std::string &character() const;
};

#endif // DIALOGUE_LINE_HPP__
