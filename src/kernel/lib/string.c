#include "string.h"

int strlen(char *s){
    int len = 0;
    while(*(s++)) len++;
    return len;
}

int strcmp(char *s1, char *s2){
    while(*s1 && (*s1 == *s2)) {s1++; s2++;}
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

void strcpy(char *dest, char *src){
    while(*src){
        *(dest++) = *(src++);
    }
    *dest = '\0';
}
