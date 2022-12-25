#ifndef __TEMPLATE__
#define __TEMPLATE__

#define CAT(a, b) a##b
#define CCAT(a, b) CAT(a, b)
#define $T(T, name) CCAT(T, CCAT(_, name))

#endif
