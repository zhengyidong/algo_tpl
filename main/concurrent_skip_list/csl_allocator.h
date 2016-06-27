#ifndef CSL_ALLOCATOR_H
#define CSL_ALLOCATOR_H

#include <cstdlib>

namespace csl
{
class SysAlloc {
public:
  void* allocate(size_t size) {
    void* p = ::malloc(size);
//    if (!p) throw std::bad_alloc();
    return p;
  }
  void deallocate(void* p) {
    ::free(p);
  }
};
}

#endif // CSL_ALLOCATOR_H

