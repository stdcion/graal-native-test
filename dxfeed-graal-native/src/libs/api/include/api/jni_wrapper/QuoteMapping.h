#ifndef DXFEED_NATIVE_QUOTEJNI_H_
#define DXFEED_NATIVE_QUOTEJNI_H_

#include "jni_wrapper.h"
#include <string>

struct Quote {
  std::string eventSymbol;
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

  std::string toString() const {
    return std::string("Quote{") + eventSymbol +
        std::string(", eventTime=") + std::to_string(eventTime) +
        std::string(", time=") + std::to_string(time) +
        std::string(", timeNanos=") + std::to_string(timeNanos) +
        std::string(", timeNanoPart=") + std::to_string(timeNanoPart) +
        std::string(", sequence=") + std::to_string(sequnce) +
        std::string(", bidTime=") + std::to_string(bidTime) +
        std::string(", bidExchange=") + bidExchangeCode +
        std::string(", bidPrice=") + std::to_string(bidPrice) +
        std::string(", bidSize=") + std::to_string(bidSize) +
        std::string(", askTime=") + std::to_string(askTime) +
        std::string(", askExchange=") + askExchangeCode +
        std::string(", askPrice=") + std::to_string(askPrice) +
        std::string(", askSize=") + std::to_string(askSize) +
        "}";
  }
};

class QuoteMapping {
 public:
  QuoteMapping(JNIEnv_ *env, dxfeed::OnCloseHandler handler) {
    clazz_ = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/dxfeed/event/market/Quote")));
    onClose_ = handler;
    idGetEventSymbol_ = env->GetMethodID(clazz_, "getEventSymbol", "()Ljava/lang/String;");
    idGetEventTime_ = env->GetMethodID(clazz_, "getEventTime", "()J");
    idGetSequence_ = env->GetMethodID(clazz_, "getSequence", "()I");
    idGetTime_ = env->GetMethodID(clazz_, "getTime", "()J");
    idGetTimeNanos_ = env->GetMethodID(clazz_, "getTimeNanos", "()J");
    idGetTimeNanoPart_ = env->GetMethodID(clazz_, "getTimeNanoPart", "()I");
    idGetBidTime_ = env->GetMethodID(clazz_, "getBidTime", "()J");
    idGetBidExchangeCode_ = env->GetMethodID(clazz_, "getBidExchangeCode", "()C");
    idGetBidPrice_ = env->GetMethodID(clazz_, "getBidPrice", "()D");
    idGetBidSizeAsDouble_ = env->GetMethodID(clazz_, "getBidSizeAsDouble", "()D");
    idGetAskTime_ = env->GetMethodID(clazz_, "getAskTime", "()J");
    idGetAskExchangeCode_ = env->GetMethodID(clazz_, "getAskExchangeCode", "()C");
    idGetAskPrice_ = env->GetMethodID(clazz_, "getAskPrice", "()D");
    idGetAskSizeAsDouble_ = env->GetMethodID(clazz_, "getAskSizeAsDouble", "()D");
  }

  ~QuoteMapping() {
      onClose_(clazz_);
  }

  dxfeed_quote buildQuote1(JNIEnv_ *env, jobject object) {
    dxfeed_quote quote{};
    quote.eventSymbol = getEventSymbol1(env, object);
    quote.eventTime = getEventTime(env, object);
    quote.sequnce = getSequence(env, object);
    quote.time = getTime(env, object);
    quote.timeNanos = getTimeNanos(env, object);
    quote.timeNanoPart = getTimeNanoPart(env, object);
    quote.bidTime = getBidTime(env, object);
    quote.bidExchangeCode = getBidExchangeCode(env, object);
    quote.bidPrice = getBidPrice(env, object);
    quote.bidSize = getBidSize(env, object);
    quote.askTime = getAskTime(env, object);
    quote.askExchangeCode = getAskExchangeCode(env, object);
    quote.askPrice = getAskPrice(env, object);
    quote.askSize = getAskSize(env, object);
    return quote;
  }

  Quote buildQuote(JNIEnv_ *env, jobject object) {
    Quote quote{};
    quote.eventSymbol = getEventSymbol(env, object);
    quote.eventTime = getEventTime(env, object);
    quote.sequnce = getSequence(env, object);
    quote.time = getTime(env, object);
    quote.timeNanos = getTimeNanos(env, object);
    quote.timeNanoPart = getTimeNanoPart(env, object);
    quote.bidTime = getBidTime(env, object);
    quote.bidExchangeCode = getBidExchangeCode(env, object);
    quote.bidPrice = getBidPrice(env, object);
    quote.bidSize = getBidSize(env, object);
    quote.askTime = getAskTime(env, object);
    quote.askExchangeCode = getAskExchangeCode(env, object);
    quote.askPrice = getAskPrice(env, object);
    quote.askSize = getAskSize(env, object);
    return quote;
  }

  const char *getEventSymbol1(JNIEnv_ *env, jobject object) {
    auto obj = reinterpret_cast<jstring>(env->CallObjectMethod(object, idGetEventSymbol_));
    auto cstr = env->GetStringUTFChars(obj, JNI_FALSE);
    auto str = std::string(cstr);
    env->ReleaseStringUTFChars(obj, cstr);
    return cstr;
  }


    std::string getEventSymbol(JNIEnv_ *env, jobject object) {
    auto obj = reinterpret_cast<jstring>(env->CallObjectMethod(object, idGetEventSymbol_));
    auto cstr = env->GetStringUTFChars(obj, JNI_FALSE);
    auto str = std::string(cstr);
    env->ReleaseStringUTFChars(obj, cstr);
    return str;
  }

  std::int64_t getEventTime(JNIEnv_ *env, jobject object) {
    return env->CallLongMethod(object, idGetEventTime_);
  }

  std::int32_t getSequence(JNIEnv_ *env, jobject object) {
    return env->CallIntMethod(object, idGetSequence_);
  }

  std::int64_t getTime(JNIEnv_ *env, jobject object) {
    return env->CallLongMethod(object, idGetTime_);
  }

  std::int64_t getTimeNanos(JNIEnv_ *env, jobject object) {
    return env->CallLongMethod(object, idGetTimeNanos_);
  }

  std::int32_t getTimeNanoPart(JNIEnv_ *env, jobject object) {
    return env->CallIntMethod(object, idGetTimeNanoPart_);
  }

  std::int64_t getBidTime(JNIEnv_ *env, jobject object) {
    return env->CallLongMethod(object, idGetBidTime_);
  }

  char getBidExchangeCode(JNIEnv_ *env, jobject object) {
    return static_cast<char>(env->CallCharMethod(object, idGetBidExchangeCode_));
  }

  double getBidPrice(JNIEnv_ *env, jobject object) {
    return env->CallDoubleMethod(object, idGetBidPrice_);
  }

  double getBidSize(JNIEnv_ *env, jobject object) {
    return env->CallDoubleMethod(object, idGetBidSizeAsDouble_);
  }

  std::int64_t getAskTime(JNIEnv_ *env, jobject object) {
    return env->CallLongMethod(object, idGetAskTime_);
  }

  char getAskExchangeCode(JNIEnv_ *env, jobject object) {
    return static_cast<char>(env->CallCharMethod(object, idGetAskExchangeCode_));
  }

  double getAskPrice(JNIEnv_ *env, jobject object) {
    return env->CallDoubleMethod(object, idGetAskPrice_);
  }

  double getAskSize(JNIEnv_ *env, jobject object) {
    return env->CallDoubleMethod(object, idGetAskSizeAsDouble_);
  }
 private:
  jclass clazz_;
  jmethodID idGetEventSymbol_;
  jmethodID idGetEventTime_;
  jmethodID idGetSequence_;
  jmethodID idGetTime_;
  jmethodID idGetTimeNanos_;
  jmethodID idGetTimeNanoPart_;
  jmethodID idGetBidTime_;
  jmethodID idGetBidExchangeCode_;
  jmethodID idGetBidPrice_;
  jmethodID idGetBidSizeAsDouble_;
  jmethodID idGetAskTime_;
  jmethodID idGetAskExchangeCode_;
  jmethodID idGetAskPrice_;
  jmethodID idGetAskSizeAsDouble_;
  dxfeed::OnCloseHandler onClose_;
};

#endif //DXFEED_NATIVE_QUOTEJNI_H_
