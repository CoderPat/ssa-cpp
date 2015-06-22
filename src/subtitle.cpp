#include "subtitle.hpp"

subtitle::content_type::const_iterator subtitle::begin() const {
  return lines_.cbegin();
}

subtitle::content_type::const_iterator subtitle::end() const {
  return lines_.cend();
}
