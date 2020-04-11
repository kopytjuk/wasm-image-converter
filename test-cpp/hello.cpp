#include <iostream>
using namespace std;

#include <zlib.h>

int main() {
    z_stream strm;
  /* allocate deflate state */
  int ret;
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  ret = deflateInit(&strm, 1);
  cout << "Hallo, Welt!" << std::endl;
  return 0;
}