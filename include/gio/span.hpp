#ifndef GIO_SPAN_HPP
#define GIO_SPAN_HPP

#include <iterator>
#include <type_traits>

namespace gio {
  template <class T>
  class Span {
    static constexpr auto is_nothrow_copy = std::is_nothrow_copy_constructible_v<T>;

  public:
    using Iter = T;
    using Size = typename std::iterator_traits<Iter>::difference_type;
    using RevIter = std::reverse_iterator<Iter>;

    constexpr Span(Iter first, Iter last) noexcept(is_nothrow_copy)
        : first_{first}
        , last_{last} {
    }

    constexpr Iter begin() const noexcept(is_nothrow_copy) {
      return first_;
    }

    constexpr Iter end() const noexcept(is_nothrow_copy) {
      return last_;
    }

    [[nodiscard]] constexpr Size size() const {
      return std::distance(first_, last_);
    }

    [[nodiscard]] constexpr bool empty() const {
      return size() == 0;
    }

    [[nodiscard]] constexpr Span<RevIter> reverse() const {
      return {
          std::reverse_iterator{last_},
          std::reverse_iterator{first_}};
    }

  private:
    Iter first_;
    Iter last_;
  };
}

#endif //GIO_SPAN_HPP
