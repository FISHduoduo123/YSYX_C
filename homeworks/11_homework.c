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
