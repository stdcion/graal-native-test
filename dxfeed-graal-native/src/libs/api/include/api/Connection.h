#ifndef DXFEED_NATIVE_CONNECTION_H_
#define DXFEED_NATIVE_CONNECTION_H_

#include <api/EventTypes.h>
#include <api/Subscription.h>
#include <graal_isolate.h>
#include <string>
#include <vector>
#include <memory>

namespace dxfeed {
class Connection final {
 public:
  Connection(graal_isolatethread_t *graal, const std::string &address);
  Connection(const Connection &other) = delete;
  Connection(Connection &&other) = delete;
  Connection &operator=(const Connection &other) = delete;
  Connection &operator=(Connection &&other) = delete;
  Subscription* createSubscription(EventType types);
  void getCandleSnapshot(const std::string &symbol, int64_t fromTime, int64_t toTime, int64_t timeout, Subscription::Listener listener);
 private:
  graal_isolatethread_t *graal_;
  int64_t endpoint_;
  int64_t connection_;
};
}

#endif //DXFEED_NATIVE_CONNECTION_H_
