#ifndef __GRAALSAMPLE_H
#define __GRAALSAMPLE_H

#include <inttypes.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct __graal_isolatethread_t graal_isolatethread_t;

typedef enum ConnectState {
    NOT_CONNECTED,
    CONNECTING,
    CONNECTED,
    CLOSED
} ConnectState;

static inline const char* ToString(ConnectState v) {
    switch (v) {
        case NOT_CONNECTED:
            return "NOT_CONNECTED";
        case CONNECTING:
            return "CONNECTING";
        case CONNECTED:
            return "CONNECTED";
        case CLOSED:
            return "CLOSED";
        default:
            return "[Unknown ConnectState]";
    }
}

typedef void (*OnChangingStateOfConnectionListener)(ConnectState, ConnectState);


// @CEntryPoint
int64_t DxFeedCApi_createEndPoint(graal_isolatethread_t*);

//void DxFeedCApi_addStateChangeListener(graal_isolatethread_t*, int64_t, int64_t);

void DxFeedCApi_setSystemProperties(graal_isolatethread_t*, const char*, const char*);

int64_t DxFeedCApi_createConnect(graal_isolatethread_t*, int64_t, const char*);

int64_t DxFeedCApi_createSubscription(graal_isolatethread_t*, int64_t, int);

void DxFeedCApi_addEventListener(graal_isolatethread_t*, int64_t, int64_t);

void DxFeedCApi_addSymbols(graal_isolatethread_t*, int64_t, const char*);

void DxFeedCApi_getCandleSnapshot(graal_isolatethread_t*, int64_t, const char*, int64_t, int64_t, int64_t, int64_t);

graal_isolatethread_t* EntryPoints_createIsolate();

void JNIHelper_initJNI(graal_isolatethread_t*);

// @CFunction
void DxFeedCApi_nOnConnectStateChangeListener(int64_t, ConnectState, ConnectState);

#if defined(__cplusplus)
}
#endif
#endif
