#include <gio/config.hpp>
#include <ostream>

namespace gio {
  std::ostream& operator<<(std::ostream& os, Endian endian) {
    if (endian == LittleEndian) {
      os << "LittleEndian";
    } else if (endian == BigEndian) {
      os << "BigEndian";
    } else {
      os << "<unknown>";
    }
    return os;
  }
}
