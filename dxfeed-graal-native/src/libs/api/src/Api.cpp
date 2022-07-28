#include <api/Api.h>
#include <api/DxFeed.hpp>
#include <api/Connection.h>

void *dxfeed_get_instance() {
  auto &feed = dxfeed::DxFeed::getInstance();
  return &feed;
}

void *dxfeed_create_connection(void *feed, const char *address) {
  return reinterpret_cast<dxfeed::DxFeed *>(feed)->createConnection(address);
}

void *dxfeed_create_subscription(void *connection, int eventType) {
  return reinterpret_cast<dxfeed::Connection *>(connection)->createSubscription(static_cast<EventType>(eventType));
}

void dxfeed_add_symbol(void *subscription, const char *symbol) {
  reinterpret_cast<dxfeed::Subscription *>(subscription)->addSymbol(symbol);
}

void dxfeed_add_listener(void *subscription, dx_feed_listener listener) {
  reinterpret_cast<dxfeed::Subscription *>(subscription)->addListener(reinterpret_cast<void (*)(const void *,
                                                                                                size_t)>(listener));
}

void dxfeed_get_candle_snapshot(void *connection,
                                dx_feed_listener listener,
                                const char *symbol,
                                int64_t from_time,
                                int64_t to_time,
                                int64_t timeout) {
  reinterpret_cast<dxfeed::Connection *>(connection)->getCandleSnapshot(symbol, from_time, to_time, timeout,
                                                                        (reinterpret_cast<void (*)(const void *,
                                                                                                   size_t)>(listener)));
}

extern "C" {
    JNIEXPORT
    void Java_com_dxfeed_JNIHelper_nLog(JNIEnv* env, jclass clazz, jstring log) {
            const char* eventData = env->GetStringUTFChars(log, 0);
            fprintf(stdout, "[Java] %s", eventData);
            env->ReleaseStringUTFChars(log, eventData);
    }
}
