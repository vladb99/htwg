int function(int param);

int global = 1; // 3

int main(void)
{
    int local = 1 ;

    local = function(local);    // local wird 4
    local = function(global);  // local wird 7

    return 0;
}

int function(int param)
{
    static int private_global = 1;
    int local = param + 1; // 4
    private_global++; // 3
    global = param + 2; // 5
    return local + private_global; //4 + 3 = 7
}
