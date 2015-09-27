#include <stdio.h>
#include <string.h>

#define MX (z>>5^y<<2) + (y>>3^z<<4) ^ (sum^y) + (k[p&3^e]^z);

long btea(long* v, long n, long* k) {
  unsigned long z=v[n-1], y=v[0], sum=0, e, DELTA=0x9e3779b9;
  long p, q ;
  if (n > 1) {          /* Coding Part */
    q = 6 + 52/n;
    while (q-- > 0) {
      sum += DELTA;
      e = (sum >> 2) & 3;
      for (p=0; p<n-1; p++) y = v[p+1], z = v[p] += MX;
      y = v[0];
      z = v[n-1] += MX;
    }
    return 0 ;
  } else if (n < -1) {  /* Decoding Part */
    n = -n;
    q = 6 + 52/n;
    sum = q*DELTA ;
    while (sum != 0) {
      e = (sum >> 2) & 3;
      for (p=n-1; p>0; p--) z = v[p-1], y = v[p] -= MX;
      z = v[n-1];
      y = v[0] -= MX;
      sum -= DELTA;
    }
    return 0;
  }
  return 1;
}

#define NITERS 3000

int main(int argc, char *argv[])
{
    unsigned char key[16];
    unsigned char block[16];
    int puzzId;
    int i, j;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <flag>\n", argv[0]);
        return 0;
    }

    for (j = 0; j < 10000; j++) {
    memset(block, 0, 16);
    block[15] = 1;
    strncpy(key, argv[1], 8);
    strncpy(key + 8, argv[1], 8);

    for (i = 0; i < 16; i++) {
        key[i] = toupper(key[i]);
    }

    for (i = 0; i < NITERS; i++) {
        btea((long *)block, 4, (long *)key);
    }

    printf("{ ");
    for (i = 0; i < 16; i++) {
        printf("0x%02x, ", block[i]);
    }
    printf("}\n");

    btea((long *)block, 4, (long *)key);

    printf("{ ");
    for (i = 0; i < 16; i++) {
        printf("0x%02x, ", block[i]);
    }
    printf("}\n");
    }

    return 1;
}
