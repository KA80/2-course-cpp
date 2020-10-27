#include <cstdint>
#include <algorithm>
#include <memory>

class PackageStream;

class BufferedReader {
  PackageStream *stream;
  int32_t pos_ = 0;
  std::unique_ptr<char[]> buf;
  int32_t remaining_package_len = 0;
  int32_t package_len = 0;

 public:
  explicit BufferedReader(PackageStream *stream) {
    this->stream = stream;
    buf = std::unique_ptr<char[]>(new char[stream->PackageLen()]);
  }

  int32_t Read(char *output_buffer, int32_t buffer_len) {
    int32_t real_buf_len = 0;
    int32_t pos = 0;
    int32_t remaining_len = buffer_len;

    do {
      if (pos_ == 0 || pos_ == stream->PackageLen()) {
        pos_ = 0;
        package_len = stream->ReadPackage(buf.get());
        remaining_package_len = package_len;
      }

      int32_t len = std::min(remaining_package_len, remaining_len);
      remaining_package_len -= remaining_len;
      memcpy(output_buffer + pos, buf.get() + pos_, len);
      real_buf_len += len;
      if (remaining_package_len <= 0) {
        buf.reset(new char[stream->PackageLen()]);
        pos_ = 0;
      } else {
        pos_ = package_len - remaining_package_len;
        break;
      }
      remaining_len -= len;
      pos += len;
    } while (remaining_len > 0 && package_len >= stream->PackageLen());

    return real_buf_len;
  }
};
