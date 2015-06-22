#ifndef SUBTITLE_LINE_HPP__
#define SUBTITLE_LINE_HPP__

#include "basic_line.hpp"
#include "srt_time.hpp"

class subtitle_line : public basic_line {
  srt_time start_time_;
  srt_time end_time_;

public:
  subtitle_line(int lineno,
                const std::string &line,
                srt_time startTime,
                srt_time endTime);

  srt_time start_time() const;
  srt_time end_time() const;

  virtual ~subtitle_line();
};

#endif // SUBTITLE_LINE_HPP__
