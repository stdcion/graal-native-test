#include <api/Subscription.h>
#include <api/DxFeed.hpp>
#include <dxfeed_c_api.h>
#include <jni.h>
#include "api/jni_wrapper/QuoteMapping.h"

namespace dxfeed {
Subscription::Subscription(graal_isolatethread_t *graal, int64_t connection, EventType eventTypes) :
    graal_{graal},
    subscription_{DxFeedCApi_createSubscription(graal, connection, static_cast<int>(eventTypes))} {
}

void Subscription::addListener(Listener listener) const {
  DxFeedCApi_addEventListener(graal_, subscription_, reinterpret_cast<std::int64_t>(listener));
}

void Subscription::addSymbol(const std::string &symbol) const {
  DxFeedCApi_addSymbols(graal_, subscription_, symbol.c_str());
}

void Subscription::addSymbols(const std::vector<std::string> &symbols) const {
  for (const auto &symbol : symbols) {
    addSymbol(symbol);
  }
}
}

extern "C" {
JNIEXPORT
void Java_com_dxfeed_DxFeedCApi_nOnQuoteEventListener(JNIEnv_ *env, jclass clazz, jlong dxFeedSub, jint size,
                                                 jobject eventList, jlong userCallback) {
  auto& listMapping = dxfeed::DxFeed::getInstance().getListMapping();
  auto& quoteMapping = dxfeed::DxFeed::getInstance().getQuoteMapping();
  std::vector<dxfeed_quote> events{};
  events.reserve(size);
  for (std::size_t i = 0; i < size; ++i) {
    events.emplace_back(quoteMapping.buildQuote1(env, listMapping.get(env, eventList, i)));
  }
  reinterpret_cast<dxfeed::Subscription::Listener *>(userCallback)(events.data(), size);
}

JNIEXPORT
void Java_com_dxfeed_DxFeedCApi_nOnCandleEventListener(JNIEnv_ *env, jclass clazz, jlong dxFeedSub, jint size,
                                                      jobject eventList, jlong userCallback) {
  auto& listMapping = dxfeed::DxFeed::getInstance().getListMapping();
  auto& candleMapping = dxfeed::DxFeed::getInstance().getCandleMapping();
  std::vector<dxfeed_candle> events{};
  events.reserve(size);
  for (std::size_t i = 0; i < size; ++i) {
    events.emplace_back(candleMapping.buildCandle1(env, listMapping.get(env, eventList, i)));
  }
  reinterpret_cast<dxfeed::Subscription::Listener *>(userCallback)(events.data(), size);
}
}

