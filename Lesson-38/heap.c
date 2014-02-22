#include <stdio.h>
#include <math.h>

int parent(int);
int left(int);
int right(int);
void Max_Heapify(int [], int, int);
void Build_Max_Heap(int [], int);
void print(int [], int);
void HeapSort(int [], int);
 
/*父結點*/
int parent(int i)
{
    return (int)floor((i - 1) / 2);
}
 
/*左子結點*/
int left(int i)
{
    return (2 * i + 1);
}
 
/*右子結點*/
int right(int i)
{
    return (2 * i + 2);
}
 
/*單一子結點最大堆積樹調整*/
void Max_Heapify(int A[], int i, int heap_size)
{
    int l = left(i);
    int r = right(i);
    int largest;
    int temp;
    if(l < heap_size && A[l] > A[i])
    {
        largest = l;
    }
    else
    {
        largest = i;
    }
    if(r < heap_size && A[r] > A[largest])
    {
        largest = r;
    }
    if(largest != i)
    {
        temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        Max_Heapify(A, largest, heap_size);
    }
}

void Build_Max_Heap(int A[], int heap_size)
{
    for(int i = (heap_size-2)/2; i >= 0; i--)
    {
        printf("i = %d\n", i);
        Max_Heapify(A, i, heap_size);
        print(A, heap_size);
    }
}
 
/*印出樹狀結構*/
void print(int A[], int heap_size)
{
    for(int i = 0; i < heap_size;i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void HeapSort(int A[], int heap_size)
{
    Build_Max_Heap(A, heap_size);
    print(A, heap_size);
    int temp;
    for(int i = heap_size - 1; i >= 0; i--)
    {
        temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        Max_Heapify(A, 0, i);
       print(A, heap_size);
    }
    print(A, heap_size);
}
 
/*輸入資料並做堆積排序*/
int main(int argc, char* argv[])
{
    const int heap_size = 13;
    int A[] = {19, 1, 10, 14, 16, 4, 7, 9, 3, 2, 8, 5, 11};
//    const int heap_size = 5;
//    int A[] = {19, 1, 10, 14, 16};
    HeapSort(A, heap_size);
    //system("pause");
    return 0;
}
