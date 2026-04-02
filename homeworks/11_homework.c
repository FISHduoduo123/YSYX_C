//请补完partition函数，这个函数有多种写法，请选择时间常数尽可能小的实现方法。想想快速排序在最好和最坏情况下的时间复杂度是多少？
//快速排序在最好情况下的时间复杂度为 O(n log n)，在最坏情况下的时间复杂度为 O(n²)
#include <stdio.h>
void swap(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int* partition(int *start, int *end) 
{
    int pivot = *start;
    int *l = start + 1;
    int *r = end;

    while (l <= r) {
        while (l <= r && *l <= pivot) l++;
        while (l <= r && *r > pivot) r--;
        if (l < r) {
            swap(l, r);
            l++;
            r--;
        }
    }
    swap(start, r);
    return r;
}
void quicksort(int *start, int *end) {
    if (start < end) {
        int *mid = partition(start, end);
        quicksort(start, mid - 1);
        quicksort(mid + 1, end);
    }
}

int main(void) {
    int a[5] = {1, 4, 3, 2, 5};
    quicksort(&a[0], &a[4]);    
    for (int i = 0; i < 5; i++) printf("%d,", a[i]);
    return 0;
}

//实现一个算法，在一组随机排列的数中找出最小的一个
int find_min(int *arr, int len) {
    int min = arr[0];
    for (int i = 1; i < len; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}
//2、在一组随机排列的数中找出第二小的，这个问题比上一个稍复杂，你能不能想出Θ(n)的算法？
int find_second_min(int *arr, int len) {
    if (len < 2) return 0;          
    int min1 = arr[0];                    
    int min2 = 0;                   
    for (int i = 1; i < len; ++i) 
    {
        if (arr[i] < min1) 
        {              
            min2 = min1;                  
            min1 = arr[i];
        } 
        else if (arr[i] < min2 && arr[i] != min1) 
        {  
            min2 = arr[i];
        }
    }
    return min2;                          
}
/*进一步泛化，在一组随机排列的数中找出第k小的，这个元素称为k-th Order Statistic。能想到的最直观的算法肯定是先把这些数排序然后取第k个，时间复杂度和排序算法相同，可以是Θ(nlgn)。这个问题虽然比前两个问题复杂，但它也有平均情况下时间复杂度是Θ(n)的算法，将上一节习题1的快速排序算法稍加修改就可以解决这个问题：
 从start到end之间找出第k小的元素 
int order_statistic(int start, int end, int k)
{
	用partition函数把序列分成两半，中间的pivot元素是序列中的第i个;
	if (k == i)
		返回找到的元素;
	else if (k > i)
		从后半部分找出第k-i小的元素并返回;
	else
		从前半部分找出第k小的元素并返回;
}
请编程实现这个算法。*/
#include <stdio.h>
#include <stdlib.h>

// 全局数组（也可以作为参数传递，为简化使用全局）
int a[100];

// 交换两个整数
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// 划分函数：将 a[start..end] 以 a[start] 为基准进行划分
// 返回基准元素最终所在的位置（索引）
int partition(int start, int end) {
    int pivot = a[start];   // 选取第一个元素作为基准
    int i = start + 1;      // 左指针，从 start+1 开始
    int j = end;            // 右指针

    while (i <= j) {
        // 左指针向右找第一个大于 pivot 的元素
        while (i <= j && a[i] <= pivot) i++;
        // 右指针向左找第一个小于等于 pivot 的元素
        while (i <= j && a[j] > pivot) j--;
        if (i < j) {
            swap(&a[i], &a[j]);
            i++;
            j--;
        }
    }
    // 将基准元素放到正确位置（即 j 指向的位置）
    swap(&a[start], &a[j]);
    return j;   // 返回基准元素的新位置
}

// 找出第 k 小的元素（k 从 1 开始计数）
int order_statistic(int start, int end, int k) {
    if (start == end) return a[start];   // 只有一个元素

    int pivot_index = partition(start, end);
    int left_count = pivot_index - start + 1;   // 左半部分（含 pivot）的元素个数

    if (k == left_count) {
        return a[pivot_index];          // 正好是基准元素
    } else if (k < left_count) {
        return order_statistic(start, pivot_index - 1, k);   // 在左半部分找第 k 小
    } else {
        // 在右半部分找第 (k - left_count) 小
        return order_statistic(pivot_index + 1, end, k - left_count);
    }
}
/*如果待查找的元素在数组中有多个则返回其中任意一个，以本节定义的数组int a[8] = { 1, 2, 2, 2, 5, 6, 8, 9 };为例，
	如果调用binarysearch(2)则返回3，即a[3]，而有些场合下要求这样的查找返回a[1]，
	也就是说，如果待查找的元素在数组中有多个则返回第一个。请修改折半查找算法实现这一特性。
*/
#include <stdio.h>

#define LEN 8
int a[LEN] = { 1, 2, 2, 2, 5, 6, 8, 9 };

int binarysearch(int number)
{
	int mid, start = 0, end = LEN - 1;

	while (start <= end) {
		mid = (start + end) / 2;
		if (a[mid] < number)
			start = mid + 1;
		else if (a[mid] > number)
			end = mid - 1;
		else
        {
            // 返回数组索引
            for (;a[mid-1]==number;mid--);
            return mid;
        }
			
	}
	return -1;
}

int main(void)
{
	printf("%d\n", binarysearch(2));
	return 0;
}
