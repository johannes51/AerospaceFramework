#ifndef DATETIME_H
#define DATETIME_H

namespace asf {
namespace time {

class Time {
public:
  virtual ~Time() = 0;

protected:
  Time() = default;
};

inline Time::~Time() { }

} // namespace time
} // namespace asf

#endif // DATETIME_H
