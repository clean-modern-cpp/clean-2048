#ifndef CLEAN2048_COMMON_NONCOPYABLE_H_
#define CLEAN2048_COMMON_NONCOPYABLE_H_

namespace common {

class NonCopyable {
 public:
  NonCopyable() = default;
  NonCopyable(const NonCopyable&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;
  virtual ~NonCopyable() = default;
};

}  // namespace common

#endif
