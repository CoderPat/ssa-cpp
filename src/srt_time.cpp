#include "srt_time.hpp"

#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace {
void check_bounds(unsigned hours,
                  unsigned minutes,
                  unsigned seconds,
                  unsigned millis) {
  if (hours   >=  100) throw std::out_of_range("hours not in 0 to 99");
  if (minutes >=   60) throw std::out_of_range("minutes not in 0 to 59");
  if (seconds >=   60) throw std::out_of_range("seconds not in 0 to 59");
  if (millis  >= 1000) throw std::out_of_range("milliseconds not in 0 to 999");
}
}

srt_time::srt_time(const std::string &s)
    : hours_(0), minutes_(0), seconds_(0), millis_(0) {
  if (s.length() != 12)
    throw std::invalid_argument("not in format hh:mm:ss,SSS");

  hours_ = std::stoi(s.c_str(), nullptr, 10);
  minutes_ = std::stoi(s.c_str() + 3, nullptr, 10);
  seconds_ = std::stoi(s.c_str() + 6, nullptr, 10);
  millis_ = std::stoi(s.c_str() + 9, nullptr, 10);

  ::check_bounds(hours_, minutes_, seconds_, millis_);
}

srt_time::srt_time(unsigned i)
    : hours_((i / 1000 / 60 / 60)),
      minutes_((i / 1000 / 60) % 60),
      seconds_((i / 1000) % 60),
      millis_(i % 1000) { }

srt_time::srt_time(unsigned hours,
                   unsigned minutes,
                   unsigned seconds,
                   unsigned milliseconds)
    : hours_(hours),
      minutes_(minutes),
      seconds_(seconds),
      millis_(milliseconds) {
  ::check_bounds(hours, minutes, seconds, milliseconds);
}

unsigned srt_time::hours() const {
  return hours_;
}

unsigned srt_time::minutes() const {
  return minutes_;
}

unsigned srt_time::seconds() const {
  return seconds_;
}

unsigned srt_time::millis() const {
  return millis_;
}

unsigned srt_time::to_millis() const {
  return millis_ + 1000 * (seconds_ + 60 * (minutes_ + 60 * hours_));
}

std::ostream &operator<<(std::ostream &o, const srt_time &s) {
  auto flags = o.flags();

  o << std::setfill('0')
    << std::setw(2) << s.hours()   << ':'
    << std::setw(2) << s.minutes() << ':'
    << std::setw(2) << s.seconds() << ','
    << std::setw(3) << s.millis();

  o.flags(flags);
  return o;
}

bool srt_time::operator<(const srt_time &other) const {
  if (hours() < other.hours()) return true;
  if (hours() > other.hours()) return false;
  if (minutes() < other.minutes()) return true;
  if (minutes() > other.minutes()) return false;
  if (seconds() < other.seconds()) return true;
  if (seconds() > other.seconds()) return false;
  if (millis() < other.millis()) return true;
  return false;
}

bool srt_time::operator==(const srt_time &other) const {
  return hours_ == other.hours_ &&
      minutes_ == other.minutes_ &&
      seconds_ == other.seconds_ &&
      millis_ == other.millis_;
}
