#ifndef DXFEED_NATIVE_DXFEED_HPP
#define DXFEED_NATIVE_DXFEED_HPP

#include <graal_isolate.h>
#include <string>
#include <memory>
#include "api/jni_wrapper/QuoteMapping.h"
#include "api/jni_wrapper/ListMapping.h"
#include "api/jni_wrapper/CandleMapping.h"

namespace dxfeed {

    class Connection;

    class DxFeed final {
    public:
        DxFeed(const DxFeed &other) = delete;
        DxFeed(DxFeed &&other) = delete;
        DxFeed &operator=(const DxFeed &other) = delete;
        DxFeed &operator=(DxFeed &&other) = delete;
        static DxFeed &getInstance();
        void setSystemProperty(std::string key, std::string value);
        Connection *createConnection(const std::string &address);
        QuoteMapping &getQuoteMapping();
        ListMapping &getListMapping();
        CandleMapping &getCandleMapping();

    private:
        DxFeed();
        graal_isolatethread_t *createIsolate();
        graal_isolatethread_t *graal_;
        JNIEnv *env_;
        QuoteMapping quoteMapping_;
        ListMapping listMapping_;
        CandleMapping candleMapping_;

        static void onClose(jclass);
    };
}

#endif //DXFEED_NATIVE_DXFEED_HPP
