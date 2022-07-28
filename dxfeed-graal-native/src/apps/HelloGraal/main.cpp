#include <dxfeed_c_api.h>
#include <iostream>

int main() {
  auto graal = EntryPoints_createIsolate();
  std::cout << "Hello GraalVM: 0x" << graal << "!" << std::endl;
}
