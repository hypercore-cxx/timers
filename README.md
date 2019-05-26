# SYNOPSIS
Non blocking timers for `C++`.

# USAGE
This module is designed to work with the [`datcxx`][0] build tool. To add this
module to your project us the following command...

```bash
build add datcxx/timers
```

# TEST

```bash
build run test
```

# API

## TIMEOUT
```c++
Hyper::Util::Timeout t;

t.start([&] {
  // timer called!
}, 1000);
```

## TIMEOUT
```c++
Hyper::Util::Timeout t;

t.start([&] {
  // called after 1000ms.
}, 1000);
```

To clear a timeout use the `clear()` method.

```c++
t.clear();
```

## INTERVAL

```c++
Hyper::Util::Interval i;

i.start([]() {
  // called every 1000ms.
}, 1000);
```

To clear an interval use the `clear()` method.

```c++
i.clear();
```

## SLEEP
Put the current thread to sleep n for milliseconds.

```cpp
Hyper::Util::sleep(100);
```

## TIMER

```c++
Hyper::Util::Timer t; // starts the timer.

cout << "Milliseconds: " << t.ms(); // milliseconds since created.

t.reset(); // reset the timer.
```

[0]:https://github.com/datcxx/build
