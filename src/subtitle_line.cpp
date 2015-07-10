#include "subtitle_line.hpp"

subtitle_line::subtitle_line(int lineno,
                             const std::string &line,
                             srt_time startTime,
                             srt_time endTime)
  : basic_line(lineno, line)
  , start_time_(startTime)
  , end_time_(endTime) {}

srt_time subtitle_line::start_time() const {
  return start_time_;
}

srt_time subtitle_line::end_time() const {
  return end_time_;
}

subtitle_line::~subtitle_line() = default;

void subtitle_line::output_to(std::ostream &o) const {
  o << lineno() << ": " << start_time() << " --> " << end_time() << " | " << line() << '\n';
}

