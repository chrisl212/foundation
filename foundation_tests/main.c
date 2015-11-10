//
//  main.c
//  foundation_tests
//
//  Created by Christopher Loonam on 11/8/15.
//  Copyright (c) 2015 Christopher Loonam. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "foundation.h"

char *testfmt(const char *str, unsigned long *len) {
    char *newstr = malloc(strlen(str) + 6);
    strcpy(newstr, str);
    strcat(newstr, "TEST");
    (*len) = strlen(newstr);
    
    return newstr;
}

int main() {
    puts("Array Tests\n===========");
    array_t *arr = arrnew("Hello", ",", "World", "!", NULL);
    printf("%s %s\n", arrobj(arr, 0), arrobj(arr, 2));
    arradd(arr, "TEST");
    puts(arrobj(arr, 4));
    arrrm(arr, 1);
    puts(arrobj(arr, 1));
    
    puts("\nDictionary Tests\n================");
    dict_t *dict = dictnew("Obj1", "Key1", "Obj2", "Key2", "Obj3", "Key3", NULL);
    puts(dictobj(dict, "Key3"));
    
    fmtdef();
    dictadd(deflt, (void *)testfmt, "T");
    putfmt("This is a %d%P test and this %s is a string. The address of dict is %p. This is a test %T.", 43223, "'This is a test string'", arr, "testfmt");
}
