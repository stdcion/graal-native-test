#include <api/Connection.h>
#include <api/Subscription.h>
#include <dxfeed_c_api.h>

namespace dxfeed {

void c_changingStateOfConnection(ConnectState oldState, ConnectState newState) {
    fprintf(stdout, "[Native] change connection state: %s -> %s\n", ToString(oldState), ToString(newState));
    fflush(stdout);
}

void addStateChangeListener(graal_isolatethread_t* graalThread, int64_t dxFeedEndPoint,
                            OnChangingStateOfConnectionListener listener)
{
    //DxFeedCApi_addStateChangeListener(graalThread, dxFeedEndPoint, (int64_t)(listener));
}

Connection::Connection(graal_isolatethread_t *graal, const std::string &address) :
    graal_{graal},
    endpoint_(DxFeedCApi_createEndPoint(graal))
{
  auto listener = (OnChangingStateOfConnectionListener)(&c_changingStateOfConnection);
  listener(NOT_CONNECTED,NOT_CONNECTED);
  //addStateChangeListener(graal, endpoint_, &c_changingStateOfConnection);
    connection_ = DxFeedCApi_createConnect(graal, endpoint_, address.c_str());
}

Subscription* Connection::createSubscription(EventType types) {
  return new Subscription(graal_, connection_, types);
}

void Connection::getCandleSnapshot(const std::string &symbol, int64_t fromTime, int64_t toTime, int64_t timeout,
        Subscription::Listener listener)
{
  DxFeedCApi_getCandleSnapshot(graal_, connection_, symbol.c_str(), fromTime, toTime, timeout, (int64_t)listener);
}

#if defined(__cplusplus)
extern "C" {
#endif
void DxFeedCApi_nOnConnectStateChangeListener(int64_t userCallback, ConnectState oldState, ConnectState newState) {
    auto listener = (OnChangingStateOfConnectionListener)(userCallback);
    listener(oldState, newState);
}
#if defined(__cplusplus)
}
#endif

}
