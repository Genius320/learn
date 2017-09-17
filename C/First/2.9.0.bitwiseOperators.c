#include <stdio.h>
#include <stdlib.h>

unsigned getbits(unsigned x, int p, int n);

int main()
{
  int a = 9, b = 5;
  int c, d, e;
  c = a & b;
  d = a | b;
  e = a ^ b;
  printf("a = %d, b = %d, c = %d\n", a, b);
  printf("a & b = %d, a | b = %d, a ^ b = %d\n", c, d, e);

  printf("getbits(10, 4, 3) = %u\n", getbits(18, 4, 3));

  system("pause");
  return 0;
}

/*
    返回x中从右边数第p位开始向右数n位的字段
    getbits(10, 4, 3) = 2
10  0000 0000 0000 1010 |
>>p 0000 0000 0000 0000 | 1010
>>1 0000 0000 0000 0000 | 0101 0
<<n 0000 0000 0000 0010 | 10

~0  1111 1111 1111 1111 |
<<n 1111 1111 1111 1000 |
~   0000 0000 0000 0111 |

&   0000 0000 0000 0010 -> 2
*/


unsigned getbits(unsigned x, int p, int n)
{
  return (x >> (p + 1 - n)) & ~(~0 << n);
}

/*
1.and & 都为真才为真

  0110 -> 6
& 1011 -> 10
  0010 -> 2

  x and 1

  ---- -> x
& 0001 -> 1 
如果末位为0则为0，末位为1则为1，即偶数为0，奇数为1
效率高于x % 2

2.or | 只要一个为真就为真

  0110 -> 6
| 1011 -> 10
  1111 -> 15

  x | 1
  ---- -> x
  0001 -> 1
  ---1 ->将末位强行变成1，再减一强行变成最接近的偶数

3.xor ^ 不同为真，相同为假，是否不相同

  0110 -> 6
^ 1011 -> 10
  1101 -> 13
^ 1011 -> 10
  0110 -> 6

  (x ^ y) ^ y = x

    int a, b;
    a = a + b;  a:a+b b:b
    b = a - b;  a:a+b b:a+b-b=a
    a = a - b;  a:a+b-a=b b:a
    不需要临时变量的swap

    xor 的逆运算是它本身
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;

4.not ~ 取反
  如果 ~ 的对象是无符号整数，得到的值就是它与该类型上界的差

5.a << b 把 a 左移 b 位，空位补零
等价于 a 乘以 2 的 b 次方，运行效率更高，因此程序中乘以 2 的 n 次方 的操作尽量用左移运算符来代替

6.a >> b 把 a 右移 b 位，空位补零
等价于 a 除以 2 的 b 次方，运行效率高，使用能大大提高效率
*/

/*
int a = 132;
int b = 077; -> 0011 1111(2)
int c = 0177 -> 0111 1111(2)
int c = 0xab -> 171

1010 1111 1000
     0111 1111
0000 0111 1000

#define SET_ON 0177
*/