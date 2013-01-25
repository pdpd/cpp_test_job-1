#if !defined(__COMMON__H)

#define __COMMON__H
#ifdef PORT
#undef PORT
#endif
#define PORT 5000

typedef struct  {
    int id;
    char str[690];
} Data;

#endif
