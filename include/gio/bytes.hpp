#ifndef GIO_BYTES_HPP
#define GIO_BYTES_HPP

#include <cstddef>
#include <type_traits>

#include "gio/config.hpp"
#include "gio/span.hpp"

namespace gio::detail {
  inline constexpr auto ReverseEndian = Endian{!static_cast<bool>(NativeEndian)};

  template <class Value>
  using BytePtr = std::conditional_t<std::is_const_v<Value>, const std::byte*, std::byte*>;

  template <Endian ByteOrder>
  struct AsBytes;

  template <>
  struct AsBytes<NativeEndian> {
    template <class Value>
    static auto as_bytes(Value& value) noexcept {
      static_assert(std::is_trivially_copyable_v<Value>);
      auto first = reinterpret_cast<BytePtr<Value>>(&value);
      return Span{first, first + sizeof(Value)};
    }
  };

  template <>
  struct AsBytes<ReverseEndian> {
    template <class Value>
    static auto as_bytes(Value& value) noexcept {
      return AsBytes<NativeEndian>::as_bytes(value).reverse();
    }
  };
}

namespace gio {
  template <Endian ByteOrder = NativeEndian, class Value>
  auto as_bytes(Value& value) noexcept {
    return detail::AsBytes<ByteOrder>::as_bytes(value);
  }
}

#endif //GIO_BYTES_HPP
