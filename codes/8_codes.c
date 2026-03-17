/*编写一个程序，定义两个类型和长度都相同的数组，将其中一个数组的所有元素拷贝给另一个。
既然数组不能直接赋值，想想应该怎么实现。*/
#include <stdio.h>
int main(void)
{
	int a[10], b[10];
    for(int i=0;i<10;i++) b[i] = a [i];
	return 0;
}
