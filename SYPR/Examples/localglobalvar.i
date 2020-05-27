# 1 "localglobalvar.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 361 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "localglobalvar.c" 2
# 10 "localglobalvar.c"
# 1 "./function.h" 1
# 13 "./function.h"
int function(int param);
# 11 "localglobalvar.c" 2
# 1 "./global.h" 1
# 13 "./global.h"
extern int global;
# 12 "localglobalvar.c" 2

int main(void)
{
    int local = 1 ;

    local = function(local);
    local = function(global );

    return 0;
}
