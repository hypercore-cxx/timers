#include "../index.hxx"

#include <iostream>
#include <chrono>
#include <thread>

int main() {
  using namespace std::literals;

  Hyper::Util::Timeout t;
  int value = 0;

  t.start([&] {
    value += 1;
  }, 1000);

  if (value != 0) {
    std::cout << "FAIL: value == 0" << std::endl;
    exit(1);
  }

  std::cout << "OK: value == 0" << std::endl;

  auto ms = std::chrono::milliseconds(1500);
  std::this_thread::sleep_for(ms);

  if (value != 1) {
    std::cout << "FAIL: value == 1" << std::endl;
    exit(1);
  }

  std::cout << "OK: value == 1" << std::endl;

  //
  // Test clear()
  //
  {
    Hyper::Util::Timeout t;

    t.start([&] {
      std::cout << "FAIL: callback called" << std::endl;
      exit(1);
    }, 1000);

    t.clear();

    std::cout << "OK: timeout cleared" << std::endl;
  }

  {
    int value = 0;
    Hyper::Util::Interval i;
    i.start([&] {
      value++;
    }, 10);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    i.clear();

    if (value > 2) {
      std::cout << "OK: Interval called more than once " << value << std::endl;
    } else {
      std::cout << "FAIL: interval not called more than once" << std::endl;
    }
  }

  {
    Hyper::Util::Timer t;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "ELLAPSED: " << t.ms() << std::endl;
  }

  return 0;
}

