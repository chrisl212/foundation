/*
 dict.h
 foundation
 
 Created by Christopher Loonam on 11/8/15.
   Copyright (c) 2015 Christopher Loonam. All rights reserved.
*/

#ifndef __foundation__dict__
#define __foundation__dict__

#include <stdio.h>

typedef struct dict dict_t;

dict_t * dictnew(void *, const char *, ...); /* obj, key, terminate with NULL */
void * dictobj(dict_t *, const char *);
void dictadd(dict_t *, void *, const char *); /* obj, key */
unsigned dictcnt(dict_t *);

#endif /* defined(__foundation__dict__) */
