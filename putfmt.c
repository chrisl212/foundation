/*
  putfmt.c
  foundation

  Created by Christopher Loonam on 11/9/15.
  Copyright (c) 2015 Christopher Loonam. All rights reserved.
*/

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "putfmt.h"
#include "dict.h"

dict_t *deflt;

typedef char *(*fmtfunc_t)(void *, unsigned long *);

char *fmtint(int, unsigned long *);
char *fmtstr(const char *, unsigned long *);
char *fmtflt(double, unsigned long *);
char *fmtptr(void *, unsigned long *);

char *fmtint(int i, unsigned long *len) {
    char *str;
    int tmp;
    
    tmp = i;
    *len = 1;
    while ((tmp /= 10))
        (*len)++;
    str = calloc(1, (*len) + 1);
    sprintf(str, "%d", i);
    
    return str;
}

char *fmtstr(const char *str, unsigned long *len) {
    *(len) = strlen(str);
    return strdup(str);
}

char *fmtflt(double f, unsigned long *len) {
    char *str;
    double tmp;
    
    tmp = f;
    *len = 1;
    while ((tmp /= 10))
        (*len)++;
    str = calloc(1, (*len) + 1);
    sprintf(str, "%f", f);
    
    return str;
}

char *fmtptr(void *o, unsigned long *len) {
    char *str;
    
    str = calloc(1, 64);
    sprintf(str, "%p", o);
    (*len) = strlen(str);
    
    return str;
}

void fmtdef(void) {
    deflt = dictnew((void *)fmtint, "d", (void *)fmtstr, "s", (void *)fmtflt, "f", (void *)fmtptr, "p", NULL);
}

char *svputfmt(const char *fmt, va_list lst) {
    char *cpy, *ret, *tmp, tok[2], *dat;
    fmtfunc_t func;
    unsigned long len;
    
    if (!deflt)
        fmtdef();
    
    ret = malloc(strlen(fmt) + 1);
    cpy = strdup(fmt);
    
    strcpy(ret, strtok(cpy, "%"));
    
    
    while ((tmp = strtok(NULL, "%"))) {
        tok[0] = tmp[0], tok[1] = '\0';
        if (tok[0] == 'P') {
            ret = realloc(ret, strlen(ret) + strlen(tmp) + 2);
            strcat(ret, "%");
            strcat(ret, ++tmp);
            continue;
        }
        
        func = (fmtfunc_t)dictobj(deflt, tok);
        
        dat = func(va_arg(lst, void *), &len);
        ret = realloc(ret, strlen(ret) + (size_t)len + strlen(tmp) + 1);
        strcat(ret, dat);
        strcat(ret, ++tmp);
        
        free(dat);
    }
    
    free(cpy);
    return ret;
}

char *sputfmt(const char *fmt, ...) {
    char *ret;
    va_list lst;
    
    va_start(lst, fmt);
    ret = svputfmt(fmt, lst);
    va_end(lst);
    
    return ret;
}

size_t putfmt(const char *fmt, ...) {
    char *ret;
    va_list lst;
    size_t len;
    
    va_start(lst, fmt);
    ret = svputfmt(fmt, lst);
    va_end(lst);
    
    len = fwrite(ret, 1, strlen(ret), stdout);
    free(ret);
    return len;
}
