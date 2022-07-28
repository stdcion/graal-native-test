#ifndef DXFEED_NATIVE_CANDLEJNI_H_
#define DXFEED_NATIVE_CANDLEJNI_H_

#include "jni_wrapper.h"
#include <string>

struct Candle {
  std::string eventSymbol;
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


  std::string toString() const {
    return std::string("Candle{") + eventSymbol +
        std::string(", eventTime=") + std::to_string(eventTime) +
        std::string(", eventFlags=") + std::to_string(eventFlags) +
        std::string(", time=") + std::to_string(time) +
        std::string(", count=") + std::to_string(count) +
        std::string(", open=") + std::to_string(open) +
        std::string(", high=") + std::to_string(high) +
        std::string(", low=") + std::to_string(low) +
        std::string(", close=") + std::to_string(close) +
        std::string(", volume=") + std::to_string(volume) +
        std::string(", vwap=") + std::to_string(VWAP) +
        std::string(", bidVolume=") +  std::to_string(bidVolume) +
        std::string(", askVolume=") + std::to_string(askVolume) +
        std::string(", impVolatility=") + std::to_string(impVolatility) +
        std::string(", openInterest=") + std::to_string(openInterest) +
        "}";
  }
};

class CandleMapping {
 public:
  CandleMapping(JNIEnv_ *env, dxfeed::OnCloseHandler handler) {
    clazz_ = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("com/dxfeed/event/candle/Candle")));
    onClose_ = handler;
    idGetEventSymbol = env->GetMethodID(clazz_, "getEventSymbolString", "()Ljava/lang/String;");
    idGetEventTime = env->GetMethodID(clazz_, "getEventTime", "()J");
    idGetEventFlags = env->GetMethodID(clazz_, "getEventFlags", "()I");
    idGetIndex = env->GetMethodID(clazz_, "getIndex", "()J");
    idGetTime = env->GetMethodID(clazz_, "getTime", "()J");
    idGetSequence = env->GetMethodID(clazz_, "getSequence", "()I");
    idGetCount = env->GetMethodID(clazz_, "getCount", "()J");
    idGetOpen = env->GetMethodID(clazz_, "getOpen", "()D");
    idGetHigh = env->GetMethodID(clazz_, "getHigh", "()D");
    idGetLow = env->GetMethodID(clazz_, "getLow", "()D");
    idGetClose = env->GetMethodID(clazz_, "getClose", "()D");
    idGetVolumeAsDouble = env->GetMethodID(clazz_, "getVolumeAsDouble", "()D");
    idGetVWAP = env->GetMethodID(clazz_, "getVWAP", "()D");
    idGetBidVolumeAsDouble = env->GetMethodID(clazz_, "getBidVolumeAsDouble", "()D");
    idGetAskVolumeAsDouble = env->GetMethodID(clazz_, "getAskVolumeAsDouble", "()D");
    idGetImpVolatility = env->GetMethodID(clazz_, "getImpVolatility", "()D");
    idGetOpenInterestAsDouble = env->GetMethodID(clazz_, "getOpenInterestAsDouble", "()D");
  }

  ~CandleMapping() {
      onClose_(clazz_);
  }

  const char *getEventSymbol1(JNIEnv_ *env, jobject object) {
    auto obj = reinterpret_cast<jstring>(env->CallObjectMethod(object, idGetEventSymbol));
    auto cstr = env->GetStringUTFChars(obj, JNI_FALSE);
    auto str = std::string(cstr);
    env->ReleaseStringUTFChars(obj, cstr);
    return cstr;
  }

  dxfeed_candle buildCandle1(JNIEnv_ *env, jobject object) {
    dxfeed_candle candle{};
    candle.eventSymbol = getEventSymbol1(env, object);
    candle.eventTime = getEventTime(env, object);
    candle.eventFlags = getEventFlags(env, object);
    candle.index = getEventIndex(env, object);
    candle.time = getTime(env, object);
    candle.sequence = getSequnce(env, object);
    candle.count = getCount(env, object);
    candle.open = getOpen(env, object);
    candle.high = getHigh(env, object);
    candle.close = getClose(env, object);
    candle.volume = getVolume(env, object);
    candle.VWAP = getVWAP(env, object);
    candle.bidVolume = getBidVolume(env, object);
    candle.askVolume = getAskVolume(env, object);
    candle.impVolatility = getImpVolatility(env, object);
    candle.openInterest = getOpenInterest(env, object);
    return candle;
  }

  Candle buildCandle(JNIEnv_ *env, jobject object) {
    Candle candle{};
    candle.eventSymbol = getEventSymbol(env, object);
    candle.eventTime = getEventTime(env, object);
    candle.eventFlags = getEventFlags(env, object);
    candle.index = getEventIndex(env, object);
    candle.time = getTime(env, object);
    candle.sequence = getSequnce(env, object);
    candle.count = getCount(env, object);
    candle.open = getOpen(env, object);
    candle.high = getHigh(env, object);
    candle.close = getClose(env, object);
    candle.volume = getVolume(env, object);
    candle.VWAP = getVWAP(env, object);
    candle.bidVolume = getBidVolume(env, object);
    candle.askVolume = getAskVolume(env, object);
    candle.impVolatility = getImpVolatility(env, object);
    candle.openInterest = getOpenInterest(env, object);
    return candle;
  }

  std::string getEventSymbol(JNIEnv_ *env, jobject object) {
    auto obj = reinterpret_cast<jstring>(env->CallObjectMethod(object, idGetEventSymbol));
    auto cstr = env->GetStringUTFChars(obj, JNI_FALSE);
    auto str = std::string(cstr);
    env->ReleaseStringUTFChars(obj, cstr);
    return str;
  }

  int64_t getEventTime(JNIEnv_ *env, jobject object) {
    return env->CallLongMethod(object, idGetEventTime);
  }

  int32_t getEventFlags(JNIEnv_ *env, jobject object) {
    return env->CallIntMethod(object, idGetEventFlags);
  }

  int64_t getEventIndex(JNIEnv_ *env, jobject object) {
    return env->CallLongMethod(object, idGetIndex);
  }

  int64_t getTime(JNIEnv_ *env, jobject object) {
    return env->CallLongMethod(object, idGetTime);
  }

  int32_t getSequnce(JNIEnv_ *env, jobject object) {
    return env->CallIntMethod(object, idGetSequence);
  }

  int64_t getCount(JNIEnv_ *env, jobject object) {
    return env->CallLongMethod(object, idGetCount);
  }

  double getOpen(JNIEnv_ *env, jobject object) {
    return env->CallDoubleMethod(object, idGetOpen);
  }

  double getHigh(JNIEnv_ *env, jobject object) {
    return env->CallDoubleMethod(object, idGetHigh);
  }

  double getLow(JNIEnv_ *env, jobject object) {
    return env->CallDoubleMethod(object, idGetLow);
  }

  double getClose(JNIEnv_ *env, jobject object) {
    return env->CallDoubleMethod(object, idGetClose);
  }

  double getVolume(JNIEnv_ *env, jobject object) {
    return env->CallDoubleMethod(object, idGetVolumeAsDouble);
  }

  double getVWAP(JNIEnv_ *env, jobject object) {
    return env->CallDoubleMethod(object, idGetVWAP);
  }

  double getBidVolume(JNIEnv_ *env, jobject object) {
    return env->CallDoubleMethod(object, idGetBidVolumeAsDouble);
  }

  double getAskVolume(JNIEnv_ *env, jobject object) {
    return env->CallDoubleMethod(object, idGetAskVolumeAsDouble);
  }

  double getImpVolatility(JNIEnv_ *env, jobject object) {
    return env->CallDoubleMethod(object, idGetImpVolatility);
  }

  double getOpenInterest(JNIEnv_ *env, jobject object) {
    return env->CallDoubleMethod(object, idGetOpenInterestAsDouble);
  }

 private:
  jclass clazz_;
  jmethodID idGetEventSymbol;
  jmethodID idGetEventTime;
  jmethodID idGetEventFlags;
  jmethodID idGetIndex;
  jmethodID idGetTime;
  jmethodID idGetSequence;
  jmethodID idGetCount;
  jmethodID idGetOpen;
  jmethodID idGetHigh;
  jmethodID idGetLow;
  jmethodID idGetClose;
  jmethodID idGetVolumeAsDouble;
  jmethodID idGetVWAP;
  jmethodID idGetBidVolumeAsDouble;
  jmethodID idGetAskVolumeAsDouble;
  jmethodID idGetImpVolatility;
  jmethodID idGetOpenInterestAsDouble;
  jmethodID idToString;
  dxfeed::OnCloseHandler onClose_;
};

#endif //DXFEED_NATIVE_CANDLEJNI_H_
