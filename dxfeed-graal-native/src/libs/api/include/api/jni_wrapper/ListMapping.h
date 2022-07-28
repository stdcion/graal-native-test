#ifndef DXFEED_NATIVE_LISTMAPPING_H_
#define DXFEED_NATIVE_LISTMAPPING_H_

#include "jni_wrapper.h"
#include <cstdint>

class ListMapping {
 public:
  explicit ListMapping(JNIEnv_ *env, dxfeed::OnCloseHandler onClose) {
    onClose_ = onClose;
    clazz_ = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("java/util/List")));
    idGet_ = env->GetMethodID(clazz_, "get", "(I)Ljava/lang/Object;");
  }

    ~ListMapping() {
        onClose_(clazz_);
    }

  jobject get(JNIEnv_ *env, jobject object, size_t index) {
    return env->CallObjectMethod(object, idGet_, index);
  }

 private:
  jclass clazz_;
  jmethodID idGet_;
  dxfeed::OnCloseHandler onClose_;
};

#endif //DXFEED_NATIVE_LISTMAPPING_H_
