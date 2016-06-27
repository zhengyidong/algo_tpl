#ifndef CSL_ATOMIC
#define CSL_ATOMIC

// TODO
#define BOOST_FORCEINLINE
#define BOOST_NOEXCEPT

namespace csl
{
enum memory_order
{
    memory_order_relaxed = 0,
    memory_order_consume = 1,
    memory_order_acquire = 2,
    memory_order_release = 4,
    memory_order_acq_rel = 6, // acquire | release
    memory_order_seq_cst = 14 // acq_rel | 8
};

template <typename T>
class Atomic
{
public:
  static BOOST_FORCEINLINE void fence_before(memory_order order) BOOST_NOEXCEPT
  {
      if ((order & memory_order_release) != 0)
          __asm__ __volatile__ ("" ::: "memory");
  }

  static BOOST_FORCEINLINE void fence_after(memory_order order) BOOST_NOEXCEPT
  {
      if ((order & memory_order_acquire) != 0)
          __asm__ __volatile__ ("" ::: "memory");
  }

  explicit Atomic(T data) BOOST_NOEXCEPT : data_(data) {}

  void store(T data, memory_order order=memory_order_seq_cst) BOOST_NOEXCEPT
  {
    if (order != memory_order_seq_cst) {
      fence_before(order);
      data_ = data;
      fence_after(order);
    } else {
      fence_before(order);
      data_ = data;
      __sync_synchronize();
    }
  }
  T load(memory_order order=memory_order_seq_cst)
  {
    T data = data_;
    fence_after(order);
    return data;
  }

private:
  volatile T data_;
};
}

#endif // CSL_ATOMIC

