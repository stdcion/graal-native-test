#ifndef DXFEED_NATIVE_API_H_
#define DXFEED_NATIVE_API_H_
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif
struct dxfeed_quote {
  const char* eventSymbol;
  int64_t eventTime;
  int32_t sequnce;
  int64_t time;
  int64_t timeNanos;
  int32_t timeNanoPart;
  int64_t bidTime;
  char bidExchangeCode;
  double bidPrice;
  double bidSize;
  int64_t askTime;
  char askExchangeCode;
  double askPrice;
  double askSize;
};

struct dxfeed_candle {
  const char *eventSymbol;
  int64_t eventTime;
  int32_t eventFlags;
  int64_t index;
  int64_t time;
  int64_t sequence;
  int64_t count;
  double open;
  double high;
  double low;
  double close;
  double volume;
  double VWAP;
  double bidVolume;
  double askVolume;
  double impVolatility;
  double openInterest;
};

typedef void(*dx_feed_listener)(const void *events, int count);

void *dxfeed_get_instance();
void *dxfeed_create_connection(void *feed, const char *address);
void *dxfeed_create_subscription(void *connection, int eventType);
void dxfeed_add_symbol(void *subscription, const char *symbol);
void dxfeed_add_listener(void *subscription, dx_feed_listener listener);
void dxfeed_get_candle_snapshot(void *connection,
                                dx_feed_listener listener,
                                const char *symbol,
                                int64_t from_time,
                                int64_t to_time,
                                int64_t timeout);

#ifdef __cplusplus
}
#endif

#endif //DXFEED_NATIVE_API_H_
