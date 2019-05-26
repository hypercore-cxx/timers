#ifndef HYPER_UTIL_TIMERS_H
#define HYPER_UTIL_TIMERS_H

#include <thread>
#include <functional>
#include <future>
#include <chrono>
#include <thread>

namespace Hyper {
  namespace Util {
    using namespace std::literals;
    typedef std::function<void()> Callback;

    void sleep (int n) {
      auto ms = std::chrono::milliseconds(n);
      std::this_thread::sleep_for(ms);
    }

    class Timer {
      public:
        using clock_t = std::chrono::high_resolution_clock;
        using duration_t = clock_t::duration;

      private:
        clock_t::time_point start;

      public:
        Timer() :
          start(clock_t::now()) {}

        int ms() const {
          return (clock_t::now() - start) / 1ms;
        }

        void reset() {
          start = clock_t::now();
        }
    };

    class Timeout {
      std::thread th;
      bool active = true;

      public:
        bool isInterval;

        void start (Callback cb, int ms) {
          auto t = std::chrono::milliseconds(ms);

          th = std::thread([&, t]() -> void {
            while (active == true) {
              std::this_thread::sleep_for(t);
              if (active) cb();
              if (!isInterval) {
                active = false;
                return;
              }
            }
          });
        }

        void clear () {
          active = false;
          th.join();
        }

        ~Timeout () {
          if (th.joinable()) {
            th.join();
          }
        }
    };

    class Interval : public Timeout {
      public:
        Interval () {
          isInterval = true;
        }
    };
  } // namespace Util
} // namespace Hyper
#endif

