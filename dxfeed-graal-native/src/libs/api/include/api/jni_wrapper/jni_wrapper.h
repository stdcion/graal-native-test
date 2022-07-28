#ifndef APP_JNI_WRAPPER_H
#define APP_JNI_WRAPPER_H

#include "api/Api.h"
#include <jni.h>

namespace dxfeed {
    typedef void(*OnCloseHandler)(jclass clazz);
}

#endif //APP_JNI_WRAPPER_H
