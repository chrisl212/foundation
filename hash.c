/*
  hash.c
  foundation

  Created by Christopher Loonam on 11/8/15.
  Copyright (c) 2015 Christopher Loonam. All rights reserved.
*/

#include "hash.h"

#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
|| defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
+(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

#define LEN 101

uint32_t hash(const char *data) {
    uint32_t hsh, tmp;
    int rem, len;
    
    len = LEN;
    
    hsh = (uint32_t)len;
    
    if (len <= 0 || data == NULL) return 0;
    
    rem = len & 3;
    len >>= 2;
    
    /* Main loop */
    for (;len > 0; len--) {
        hsh  += get16bits (data);
        tmp    = (get16bits (data+2) << 11) ^ hsh;
        hsh   = (hsh << 16) ^ tmp;
        data  += 2*sizeof (uint16_t);
        hsh  += hsh >> 11;
    }
    
    /* Handle end cases */
    switch (rem) {
        case 3: hsh += get16bits (data);
            hsh ^= hsh << 16;
            hsh ^= (uint32_t)((signed char)data[sizeof (uint16_t)]) << 18;
            hsh += hsh >> 11;
            break;
        case 2: hsh += get16bits (data);
            hsh ^= hsh << 11;
            hsh += hsh >> 17;
            break;
        case 1: hsh += (uint32_t)(signed char)*data;
            hsh ^= hsh << 10;
            hsh += hsh >> 1;
    }
    
    /* Force "avalanching" of final 127 bits */
    hsh ^= hsh << 3;
    hsh += hsh >> 5;
    hsh ^= hsh << 4;
    hsh += hsh >> 17;
    hsh ^= hsh << 25;
    hsh += hsh >> 6;
    
    return hsh;
}
