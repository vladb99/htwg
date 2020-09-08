# 1 "function.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 361 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "function.c" 2
# 10 "function.c"
# 1 "./function.h" 1
# 13 "./function.h"
int function(int param);
# 11 "function.c" 2
# 1 "./global.h" 1
# 13 "./global.h"
extern int global;
# 12 "function.c" 2

int function(int param)
{
    static int private_global = 1;
    int local = param + 1;
    private_global++;
    global = param + 2;
    return local + private_global;
}
