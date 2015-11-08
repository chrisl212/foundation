//
//  main.c
//  foundation_tests
//
//  Created by Christopher Loonam on 11/8/15.
//  Copyright (c) 2015 Christopher Loonam. All rights reserved.
//

#include <stdio.h>
#include "foundation.h"

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
}
