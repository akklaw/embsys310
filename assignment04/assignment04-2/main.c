#include <stdio.h>

int func1(int var1, int var2, int var3, int var4, int var5)
{
    int lvar1;
    int lvar2;
    int lvar3;
    int lvar4;
    int lvar5;
    
    int sum;
    
    lvar1 = var1;
    lvar2 = var2;
    lvar3 = var3;
    lvar4 = var4;
    lvar5 = var5;
    
    sum = lvar1 + lvar2 + lvar3 + lvar4 + lvar5;
    
    return sum;
}

int func2()
{
    int ret = func1(1,2,3,4,5);
    return ret;
}

int main()
{
  printf("%d\n", func2());
  
  return 0;
}
