#ifndef DATETIME_H
#define DATETIME_H

namespace asf {
namespace time {

class Time {
public:
  virtual ~Time() = default;

protected:
  Time() = default;
};

} // namespace time
} // namespace asf

#endif // DATETIME_H
