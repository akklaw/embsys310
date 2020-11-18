#include <assert.h>

// function prototype
void swap_pointer(int **x, int **y);

// swap pointer x and y
void swap_pointer(int **x, int **y)
{
    int* temp = *x;
    *x = *y;
    *y = temp;
    
    assert(**x == 1000000);
    assert(**y == 2000000);
    // if passing the assert, then the pointer are swapped.
}

int main()
{
  int x = 2000000;
  int y = 1000000;

  int* px = &x;
  int* py = &y;
  
  swap_pointer(&px, &py);
  assert(px == &y);
  assert(py == &x);    
  assert(x == 2000000);
  assert(y == 1000000);
  // swapped the pointers variables
  
  return 0;
}
