1a) 0x80000000
1b) R1
1c) N=1, N = negative, V=1, V = overflow

2a) 0x00000000
2b) N=0, V=0, This is not a negative value and it is not overflow.  
    But it is carry over, so C=1, and it is zero, so Z=1.

3a) 0x80000000
3b) N=1, V=1, it passes 0x7FFFFFFF and Negative flag is set and overflow is set.

4a) 0x00000000
4b) N=0, V=0, this is not a negative value and it is not overflow.
    But it is carry over, so C=1, and it is zero, so Z=1

5a) globle variable
5b) NO
5c) Memory window
5d) 0x20000000

6a) 4
6b) The p_int pointer referencing 0x2000000 address, it increments 3 times at that address and then the counter increments 1.
    so total is 4.

7a) 0x2000000
7b) RAM
7c) 4


