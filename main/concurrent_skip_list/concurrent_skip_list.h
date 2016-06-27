
#ifndef CONCURRENT_SKIP_LIST_H
#define CONCURRENT_SKIP_LIST_H

#define DEBUG

#include <algorithm>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "csl_allocator.h"
#include "csl_atomic.h"

namespace csl
{
// skip list node
template <typename T>
class SkipListNode
{
  enum
  {
    IS_HEAD_NODE = 1,
    MARKED_FOR_REMOVAL = (1 << 1),
    FULLY_LINKED = (1 << 2),
  };

#ifndef DEBUG
private:
#else
public:
#endif
  template <typename NodeAlloc>
  static SkipListNode *create(NodeAlloc &alloc, const T &data, int height, bool is_head = false)
  {
    size_t size = sizeof(SkipListNode) + height * sizeof(Atomic<SkipListNode*>);
    SkipListNode *node = static_cast<SkipListNode*>(alloc.allocate(size));

    new (node) SkipListNode(height, data, is_head);
    return node;
  }

  template <typename NodeAlloc>
  static void destroy(NodeAlloc &alloc, SkipListNode *node)
  {
    node->~SkipListNode();
    alloc.deallocate(node);
  }

public:
  typedef T value_type;
private:
  SkipListNode(uint8_t height, const T &data, bool is_head)
    :height_(height), data_(data)
  {
    for(uint8_t i=0; i<height_; ++i) {
      new (&next_[i]) Atomic<SkipListNode*>(NULL);
    }
  }

  ~SkipListNode()
  {
    //TODO 析构的时候应该做什么？
  }

  const uint8_t height_;
  value_type data_;
  Atomic<SkipListNode*> next_[0];
};



template <typename T,
          typename Comp = std::less<T>,
          typename NodeALloc = SysAlloc,
          int MAX_HEIGHT = 24>
class ConcurrentSkipList
{
public:
  int random_height()
  {
    srand(time(NULL));
    static const unsigned int p = 4;
    uint8_t v = 1;
    while (v < MAX_HEIGHT && (rand() % p == 0)) {
      ++v;
    }
    if (v > MAX_HEIGHT) v = MAX_HEIGHT;
    return v;
  }

private:
  typedef T node_type;
  Atomic<node_type*> head_;
  Atomic<size_t> size_;
};
}

#endif // CONCURRENT_SKIP_LIST_H

