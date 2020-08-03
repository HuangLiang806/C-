#include<iostream>
#include<cstdio>
#include<stdlib.h>
#include <algorithm>  

#define LOCAL

using namespace std;



int get_piv(int a[], int l, int r)
{
	int mid = (l + r) / 2;
	if(a[l] > a[mid]) swap(a[l], a[mid]);
	if(a[l] > a[r]) swap(a[l], a[r]);
	if(a[mid] > a[r]) swap(a[mid], a[r]);

	swap(a[mid], a[r-1]);
	return a[r-1];
}

/*
void q_sort(int a[], int l, int r)
{
	if(l >= r) return ;

	int pivot = a[l], i = l, j = r;
	while(i < j)
	{
		while(i < j && a[j] >= pivot) j--;
		if(i < j) a[i++] = a[j];
		while(i < j && a[i] < pivot) i++;
		if(i < j) a[j--] = a[i];
	}
	a[i] = pivot;
	//for(int i=0; i<11; i++) printf(" %d", a[i]); printf("\n");
	q_sort(a, l, i-1);
	q_sort(a, i+1, r);	

}


void quick_sort(int a[], int n)
{
	q_sort(a, 0, n-1);
}*/

/*
void bubble_sort(int a[], int n)
{
	for(int i=0; i<n; i++)
		for(int j=1; j<n-i; j++)
			if(a[j-1] > a[j]) swap(a[j-1], a[j]);
}


void insert_sort(int a[], int n)
{
	for(int i=1; i<n; i++)
	{
		int curr = a[i], j;
		for(j=i; j>=0 && a[j-1]>curr; j--) a[j] = a[j-1];
		
		a[j] = curr;
	}
}*/

void print(int a[], int n){
	if(n >= 1) printf("%d", a[0]);
	for(int i=1; i<n; i++) printf(" %d", a[i]);
	printf("\n");
}

/*-------------------------bubble_sort------------------------------*/
void bubble_sort(int a[], int n){
	for(int i=0; i<n-1; i++){
		for(int j=0; j<n-i-1; j++){
			if(a[j] > a[j+1]) swap(a[j], a[j+1]);
		}
	}
}

/*-------------------------choose_sort------------------------------*/
void choose_sort(int a[], int n){
	for(int i=0; i<n; i++){
		int min_index = i;
		for(int j=i+1; j<n; j++){
			if(a[j] < a[min_index]) min_index = j;		
		}
		swap(a[min_index], a[i]);
	}
}

/*-------------------------insert_sort------------------------------*/
void insert_sort(int a[], int n){
	for(int i = 1; i < n; i++){
		int j, curr = a[i];
		for(j = i - 1; j >=0 && a[j] > curr; j--){
			a[j + 1] = a[j];
		}
		a[j + 1] = curr; 
	}
}

/*-------------------------shell_sort------------------------------*/
void shell_sort(int a[], int n){
	for(int gap = n / 2; gap > 0; gap /= 2){
		for(int i = gap; i < n; i++){
			int curr = a[i], j;
			for(j = i - gap; j >= 0 && a[j] > curr; j -= gap){
				a[j + gap] = a[j];
			}
			a[j + gap] = curr;
		}
	}
}


/*-------------------------merge_sort------------------------------*/
void m_sort(int a[], int l, int r, int help_mem[]);
void merge_order_seq(int arr[], int l, int r, int end, int help_mem[]);

void merge_sort(int a[], int n){
	int *help_mem = (int*)malloc(n * sizeof(int));
	if(help_mem){
		m_sort(a, 0, n-1, help_mem);
		free(help_mem);
	}
	else{
		printf("内存分配失败\n");
	}
}

void m_sort(int a[], int l, int r, int help_mem[]){
	if(l >= r) return;

	int mid = (l + r) / 2;
	m_sort(a, l, mid, help_mem);
	m_sort(a, mid+1, r, help_mem);
	merge_order_seq(a, l, mid+1, r, help_mem);
	// print(a, 13);
}

void merge_order_seq(int arr[], int l, int r, int end, int help_mem[]){
	// 合并两段有序序列[l, r-1] [r, end]，然后复制回原数组
	int a = l, a_end = r - 1, b = r, b_end = end, i = l;
	while(a <= a_end && b <= b_end){
		if(arr[a] <= arr[b]){
			help_mem[i++] = arr[a++]; 
		}else{
			help_mem[i++] = arr[b++]; 
		}
	}

	while(a <= a_end) help_mem[i++] = arr[a++];
	while(b <= b_end) help_mem[i++] = arr[b++];

	//复制回原数组
	while(l <= end) {
		arr[l] = help_mem[l]; l++;
	}

}


/*-------------------------quick_sort------------------------------*/
void q_sort(int a[], int l, int r);
int paritition(int a[], int low, int high);

void quick_sort(int a[], int n){
	q_sort(a, 0, n-1);
}


void q_sort(int a[], int low, int high)
{
	if(low < high){
		int pivot = paritition(a, low, high);
		q_sort(a, low, pivot - 1);
		q_sort(a, pivot + 1, high);
	}

}

int paritition(int a[], int low, int high){
	int pivot = a[low];
	while(low < high){
		while(low < high && a[high] >= pivot) high--;
		a[low] = a[high];

		while(low < high && a[low] <= pivot) low++;
		a[high] = a[low];
	}

	a[low] = pivot;
	return low;
}

///////////////////////////////////////////
 //标准分割函数
 int Paritition1(int A[], int low, int high) {
   int pivot = A[low];
   while (low < high) {

     while (low < high && A[high] >= pivot) --high;
     A[low] = A[high];

     while (low < high && A[low] <= pivot)  ++low;
     A[high] = A[low];
   }

   A[low] = pivot;
   return low;
 }

 void QuickSort(int A[], int low, int high) //快排母函数
 {
   if (low < high) {
     int pivot = Paritition1(A, low, high); 
     QuickSort(A, low, pivot - 1);
     QuickSort(A, pivot + 1, high);
   }
 }


/*-------------------------heap_sort------------------------------*/
void perc_down(int a[], int top, int n);

void heap_sort(int a[], int n){
	// 建最大堆
	for(int i=n/2-1; i>=0; i--) {perc_down(a, i, n);} // i初始化为堆的最后一个有儿子的父节点

	// 取出堆顶元素与堆最后元素交换，并使堆的size--
	for(int i=n-1; i>=0; i--){
		swap(a[0], a[i]);
		perc_down(a, 0, i);
	}
}

void perc_down(int a[], int top, int n){ // /* 将n个元素的数组中以a[top]为根的子堆调整为最大堆 */ 且其子堆为最大堆
	int parent, child, x = a[top];
	for(parent=top; parent*2+1 < n; parent=child){
		child = parent * 2 + 1;
		if(child != n-1 && a[child+1]>a[child]) child++;

		if(a[child] <= x) break;
		else a[parent] = a[child];
	}
	a[parent] = x;
}



/*-------------------------counting_sort------------------------------*/
void counting_sort(int a[], int n){
	// 计数排序
}


/*-------------------------bucket_sort------------------------------*/
void bucket_sort(int a[], int n){
	// 桶排序
}


/*-------------------------radix_sort------------------------------*/
void radix_sort(int a[], int n){
	// 基数排序，是一种非比较型整数排序算法
	// LSD次位优先，MSD主位优先
}





//-------------------------main------------------------------*/
int main()
{
	#ifdef LOCAL
	freopen("input.data", "r", stdin);
	#endif

	// 输入
	int n;
	scanf("%d", &n);
	int a[n];
	for(int i=0; i<n; i++) scanf("%d", &a[i]);

	//冒泡ok、选择ok、插入ok、希尔ok、归并ok、快速ok、堆ok、 // 计数、桶、基数

	heap_sort(a, n);

	// 输出
	print(a, n);

	return 0;
}
