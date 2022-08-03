#include <Foo/Foo.hpp>
#include <dxfeed_c_api.h>
#include <iostream>
#include <jni.h>

int main() {
  Foo foo{};
  foo.printHello();

  auto graal = EntryPoints_createIsolate();
  std::cout << "Hello GraalVM: 0x" << graal << "!" << std::endl;
  JNIHelper_initJNI(graal);
}

extern "C" {
JNIEXPORT
void Java_com_dxfeed_JNIHelper_nInitJNI(JNIEnv_ *env, jclass *) {
 printf("jni init\r\n");
}
}