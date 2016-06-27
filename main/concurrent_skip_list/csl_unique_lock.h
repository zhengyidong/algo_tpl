#ifndef CSL_UNIQUE_LOCK_H
#define CSL_UNIQUE_LOCK_H


#include <stdint.h>
#include <time.h>
#include "csl_atomic.h"

namespace csl
{
class Sleeper {
  static const uint32_t MAX_ACTIVE_SPIN = 4000;

  uint32_t spin_count_;

public:
  Sleeper() : spin_count_(0) {}

  void wait()
  {
    if (spin_count_ < MAX_ACTIVE_SPIN) {
      ++spin_count_;
      asm volatile("pause");
    } else {
      struct timespec ts = { 0, 500000 };
      nanosleep(&ts, 0);
    }
  }
};
struct SpinLock {
  enum { FREE = 0, LOCKED = 1 };
  uint8_t lock_;

  void init() {
    payload()->store(FREE);
  }

  bool try_lock() {
    return cas(FREE, LOCKED);
  }

  void lock() {
    Sleeper sleeper;
    do {
      while (payload()->load() != FREE) {
        sleeper.wait();
      }
    } while (!try_lock());
  }

  void unlock() {
    payload()->store(FREE, memory_order_release);
  }

private:
  Atomic<uint8_t>* payload() {
    return reinterpret_cast<Atomic<uint8_t>*>(&this->lock_);
  }

  bool cas(uint8_t compare, uint8_t new_val) {
    return __sync_bool_compare_and_swap(&lock_, compare, new_val);
  }
};


template <typename Mutex>
class UniqueLock
{
private:
  Mutex *m_;
public:
  UniqueLock()
    :m_(0)
  {}
  explicit UniqueLock(Mutex &m)
    :m_(&m){
    lock();
  }
  void lock()
  {
    if (m_ == 0) {//TODO
    }
    m_->lock();
  }
};
}

#endif // CSL_UNIQUE_LOCK_H

