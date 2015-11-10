/*
  putfmt.c
  foundation

  Created by Christopher Loonam on 11/9/15.
  Copyright (c) 2015 Christopher Loonam. All rights reserved.
*/

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "putfmt.h"
#include "dict.h"

dict_t *deflt;

typedef char *(*fmtfunc_t)(void *, const char *);

char *fmtint(int *, const char *);
char *fmtstr(const char *, const char *);
char *fmtflt(double *, const char *);
char *fmtptr(void *, const char *);

char *fmtint(int *i, const char *mod) {
    char *str;
    int tmp, len;
    
    tmp = (int)i;
    len = 1;
    while ((tmp /= 10))
        len++;
    str = calloc(1, (size_t)len + 1);
    sprintf(str, mod, (int)*i);
    
    return str;
}

char *fmtstr(const char *str, const char *mod) {
    return strdup(str);
}

char *fmtflt(double *f, const char *mod) {
    char *str;

    asprintf(&str, mod, (double)*f);
    
    return str;
}

char *fmtptr(void *o, const char *mod) {
    char *str;
    
    str = calloc(1, 64);
    sprintf(str, mod, o);
    
    return str;
}

void fmtdef(void) {
    deflt = dictnew((void *)fmtint, "d", (void *)fmtstr, "s", (void *)fmtflt, "f", (void *)fmtptr, "p", NULL);
}

char *svputfmt(const char *fmt, va_list lst) {
    char *cpy, *ret, *tmp, tok[10], key[2], *dat;
    fmtfunc_t func;
    union {
        double dval;
        void *pval;
        int ival;
    } val;
    int i;
    
    if (!deflt)
        fmtdef();
    
    ret = malloc(strlen(fmt) + 1);
    cpy = strdup(fmt);
    
    strcpy(ret, strtok(cpy, "%"));
    
    
    while ((tmp = strtok(NULL, "%"))) {
        i = 1;
        tok[0] = '%';
        while (*tmp) {
            tok[i++] = *tmp;
            if (isalpha(tok[i-1])) {
                tok[i] = 0;
                break;
            }
            tmp++;
        }
        if (tok[i-1] == 'P') {
            ret = realloc(ret, strlen(ret) + strlen(tmp) + 2);
            strcat(ret, "%");
            strcat(ret, ++tmp);
            continue;
        }
        
        key[0] = tok[i-1], key[1] = 0;
        func = (fmtfunc_t)dictobj(deflt, key);
        
        switch (tok[i-1]) {
            case 'f':
                val.dval = va_arg(lst, double);
                dat = func(&(val.dval), tok);
                break;
                
            case 'd':
                val.ival = va_arg(lst, int);
                dat = func(&(val.ival), tok);
                break;

            default:
                val.pval = va_arg(lst, void *);
                dat = func(val.pval, tok);
                break;
        }
        
        ret = realloc(ret, strlen(ret) + strlen(dat) + strlen(tmp) + 1);
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
