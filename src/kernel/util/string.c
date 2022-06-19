#include "string.h"

int strlen(char *s){
    int len = 0;
    while(*(s++)) len++;
    return len;
}
