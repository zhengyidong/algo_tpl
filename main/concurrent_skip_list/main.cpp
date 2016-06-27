#include <iostream>

#include "csl_unique_lock.h"
#include "concurrent_skip_list.h"

using namespace std;
using namespace csl;

void test_sleeper()
{
  Sleeper spr;
  spr.wait();
}

void test_spin_lock()
{
  SpinLock sl;
  sl.lock();
  sl.unlock();
}

int main()
{
  test_sleeper();
  test_spin_lock();
//  csl::SysAlloc sa;
//  csl::SkipListNode<int> *sln = csl::SkipListNode<int>::create(sa, 0, 3);

  return 0;
}

