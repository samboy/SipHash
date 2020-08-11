// Public domain 2020 by Sam Trenholme
#include <stddef.h>

// Sip Hash needs well defined 64-bit ints, even on 32-bit systems
#include <stdint.h>
// Sip hash has a 128-bit key which should be fairly random
// This comes from the RadioGatun[32] hash of "https://maradns.samiam.org"
uint32_t sipKey1 = 0xded6cbc7;
uint32_t sipKey2 = 0x81875fe8;

void halfSipHashSetKey(uint32_t a, uint32_t b) {
  sipKey1 = a;
  sipKey2 = b;
}

uint32_t halfSipHash(const char *str, size_t l) {
  uint32_t v0, v1, v2, v3, m;
  int shift = 0, round = 0;
  size_t offset = 0;

  // We calculate the hash via SipHash, for security reasons
  v0 = sipKey1;
  v1 = sipKey2;
  v2 = sipKey1 ^ 0x6c796765;
  v3 = sipKey2 ^ 0x74656462;
  m = 0;
  while(offset <= l) {
    if(offset < l) {
      m |= (uint32_t)(str[offset] & 0xff) << shift;  
      shift += 8;
    }
    while(shift >= 32 || offset == l) { // "while" to avoid goto
      if(offset == l && shift != 32) {
        m |= (uint64_t)(l & 0xff) << 24;
        offset++;
      }
      shift = 0;
      v3 ^= m;
      for(round = 0; round < 2; round++) {
        v0 += v1; 
        v1 = (v1 << 5) | (v1 >> 27);
        v1 ^= v0;
        v0 = (v0 << 16) | (v0 >> 16);
        v2 += v3;
        v3 = (v3 << 8) | (v3 >> 24);
        v3 ^= v2; v0 += v3;
        v3 = (v3 << 7) | (v3 >> 25);
	v3 ^= v0; v2 += v1;
        v1 = (v1 << 13) | (v1 >> 19);
	v1 ^= v2;
	v2 = (v2 << 16) | (v2 >> 16);
      }
      v0 ^= m;
      shift = 0;
      m = 0;
    }
    offset++;
  }   
  v2 ^= 255;
  for(round = 0; round < 4; round++) {
    v0 += v1; 
    v1 = (v1 << 5) | (v1 >> 27);
    v1 ^= v0;
    v0 = (v0 << 16) | (v0 >> 16);
    v2 += v3;
    v3 = (v3 << 8) | (v3 >> 24);
    v3 ^= v2; v0 += v3;
    v3 = (v3 << 7) | (v3 >> 25);
    v3 ^= v0; v2 += v1;
    v1 = (v1 << 13) | (v1 >> 19);
    v1 ^= v2;
    v2 = (v2 << 16) | (v2 >> 16);
  }
  return v1 ^ v3;
} 

#ifdef MAIN
#include <stdlib.h>
#include <stdio.h>

int main() {
        char test[66];
        int a;
        uint32_t result;
        halfSipHashSetKey(0x03020100, 0x07060504);
        for(a = 0; a < 64; a++) { 
                test[a] = a;
                printf("%08x\n",halfSipHash(test, a)); 
        }
}
#endif // MAIN
