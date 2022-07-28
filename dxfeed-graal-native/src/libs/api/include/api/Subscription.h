#ifndef DXFEED_NATIVE_SUBSCRIPTION_H_
#define DXFEED_NATIVE_SUBSCRIPTION_H_

#include <api/EventTypes.h>
#include <graal_isolate.h>
#include <string>
#include <vector>

namespace dxfeed {
class Subscription final {
 public:
  typedef void(Listener)(const void *events, std::size_t count);
  Subscription(graal_isolatethread_t *graal, int64_t connection, EventType eventTypes);
  Subscription(const Subscription &other) = delete;
  Subscription(Subscription &&other) = delete;
  Subscription &operator=(const Subscription &other) = delete;
  Subscription &operator=(Subscription &&other) = delete;
  void addListener(Listener listener) const;
  void addSymbol(const std::string &symbol) const;
  void addSymbols(const std::vector<std::string> &symbols) const;
 private:
  graal_isolatethread_t *graal_;
  std::int64_t subscription_;
};
}

#endif //DXFEED_NATIVE_SUBSCRIPTION_H_
