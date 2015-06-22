#ifndef SRT_TIME_HPP__
#define SRT_TIME_HPP__

#include <string>

class srt_time {
  unsigned hours_   : 7;  // [0, 99] -> [0, 128[
  unsigned minutes_ : 6;  // [0, 59[ -> [0,  64[
  unsigned seconds_ : 6;  // [0, 59[ -> [0,  64[
  unsigned millis_  : 10; // [0,999] -> [0,1024[

public:
  srt_time(unsigned hours,
           unsigned minutes,
           unsigned seconds,
           unsigned milliseconds);

  explicit srt_time(const std::string &s);
  explicit srt_time(unsigned i);

  unsigned hours() const;
  unsigned minutes() const;
  unsigned seconds() const;
  unsigned millis() const;

  unsigned to_millis() const;

  bool operator<(const srt_time &other) const;
  bool operator==(const srt_time &other) const;
};

std::ostream &operator<<(std::ostream &, const srt_time &);

#endif // SRT_TIME_HPP__
