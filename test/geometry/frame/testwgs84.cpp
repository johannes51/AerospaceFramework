#include <gtest/gtest.h>

#include "date/date.h"

#include "geometry/frame/eci.h"
#include "geometry/frame/wgs84.h"
#include "geometry/vector.h"
#include "time/utc.h"

using namespace asf;
using namespace asf::geometry;

TEST(Wgs84Tests, Construction)
{
  EXPECT_NO_THROW(Wgs84(nullptr, time::UTC(std::chrono::system_clock::now())));
}

TEST(Wgs84Tests, Unwind)
{
  using namespace std::chrono;
  using namespace std::chrono_literals;
  auto eci = std::make_shared<ECI>(nullptr);
  std::tm timeinfo = tm();
  timeinfo.tm_year = 2014 - 1900;
  timeinfo.tm_mon = 1 - 1;
  timeinfo.tm_mday = 9;
  timeinfo.tm_hour = 2;
  timeinfo.tm_min = 35;
  timeinfo.tm_sec = 34;
  auto wgs = std::make_shared<Wgs84>(eci.get(), time::UTC(std::chrono::system_clock::from_time_t(timegm(&timeinfo))));
  auto vecWgs = std::make_shared<Vector>(wgs.get(), 40, 40, 40, TransformationBehaviour::Position);
  auto vecEci = wgs->to(*vecWgs, FrameType::ECI);
  //  EXPECT_NEAR(vecEci.element(0), -4.2848e6, 0.01e6); // TODO: collect data
}

TEST(Wgs84Tests, Embed)
{
  using namespace date;
  using namespace std::chrono_literals;
  auto eci = std::make_shared<ECI>(nullptr);
  auto wgs = std::make_shared<Wgs84>(eci.get(), time::UTC(sys_days { January / 9 / 2014 } + 2h + 35min + 34s));
  auto vecEci = std::make_shared<Vector>(eci.get(), TransformationBehaviour::Position);
  vecEci->element(0) = 4e6;
  vecEci->element(1) = 4e6;
  vecEci->element(2) = 3e6;
  auto vecWgs = wgs->to(*vecEci, FrameType::LLA);
  //  EXPECT_NEAR(vecWgs.element(0), 28.1517, 0.01); // TODO: collect data
}
