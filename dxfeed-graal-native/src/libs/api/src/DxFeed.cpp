#include <api/DxFeed.hpp>
#include <api/Connection.h>
#include <dxfeed_c_api.h>

namespace dxfeed {
static JNIEnv *JNI;
DxFeed &dxfeed::DxFeed::getInstance() {
  static DxFeed instance{};
  return instance;
}

DxFeed::DxFeed() :
    graal_{createIsolate()},
    env_{JNI},
    quoteMapping_{env_, onClose},
    listMapping_{env_, onClose},
    candleMapping_{env_, onClose} {
}

void DxFeed::setSystemProperty(std::string key, std::string value){
  DxFeedCApi_setSystemProperties(graal_, key.c_str(), value.c_str());
}

Connection* DxFeed::createConnection(const std::string &address) {

  return new Connection(graal_, address);
}
QuoteMapping &DxFeed::getQuoteMapping() {
  return quoteMapping_;
}
ListMapping &DxFeed::getListMapping() {
  return listMapping_;
}
CandleMapping &DxFeed::getCandleMapping() {
  return candleMapping_;
}
graal_isolatethread_t* DxFeed::createIsolate() {
  auto graal = EntryPoints_createIsolate();
  JNIHelper_initJNI(graal);
  return static_cast<graal_isolatethread_t *>(graal);
}

void DxFeed::onClose(jclass clazz) {
    JNI->DeleteGlobalRef(clazz);
}
}

extern "C" {
JNIEXPORT
void Java_com_dxfeed_JNIHelper_nInitJNI(JNIEnv_ *env, jclass *) {
  dxfeed::JNI = env;
}
}
