// Sort.cpp : Defines the entry point for the console application.
// 常见的排序算法

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;
const static int LEN = 10;
void print(int arr[], int len) {
	for (int i = 0; i < len; i++) {
		cout << arr[i] << "    ";
	}
	cout << endl;
}

//交换
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

//1
//直接插入排序   n2    稳定  n小 效果好  空间1
//整个序列分为有序区和无序区，取第一个元素作为初始有序区，
//然后第二个开始，依次插入到有序区的合适位置，直到排好序
void InsertSort(int arr[], int len) {
	for (int i = 1; i < len; i++) {
		for (int j = i; j > 0; --j) {
			//向前比较
			if (arr[j] < arr[j - 1]) {
				swap(arr[j], arr[j - 1]);
			}
		}
	}
}

//2
//冒泡排序  n2   稳定  空间1
//比较相邻的元素，如果反序则交换，过程也是分为有序区和无序区，初始时有序区为空，
//所有元素都在无序区，经过第一趟后就能找出最大的元素，然后重复便可
void BubbleSort(int arr[], int len) {
	//用来标志是否发生了交换
	bool flag = false;

	for (int i = 0; i < len; i++) {
		flag = false;
		//每次排序都会选择出一个最大的元素排在末尾
		//之前循环排在末尾的元素无需再一次比较，因此j < len - 1 - i
		for (int j = 0; j < len - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				flag = true;
			}
		}
		//如果没有发生交换  则说明序列已经有序
		if (!flag) {
			break;
		}
	}
}
//优化
void BubbleSort2(int arr[], int len) {
	//标记上一次比较结束的位置  用作内循环的结束标志
	int flag = len;
	int stop_flag = len - 1;

	for (int i = 0; i < len; i++) {
		stop_flag = flag - 1;
		flag = 0;
		//每次排序都会选择出一个最大的元素排在末尾
		//记录下交换的结束位置   此位置后的元素已经有序，无需再遍历
		for (int j = 0; j < stop_flag; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				//记录下交换结束的位置
				flag = j + 1;
			}
		}
		//没有发生交换
		if (flag == 0) {
			break;
		}
	}
}


//3
//选择排序   稳定   时间 n2 空间 1
//每一次从后面选择出一个最小的值（swap_pos），替换到前面来(i)。
void SelectSort(int arr[], int len) {
	//外循环  找到第几个位置的元素
	for (int i = 0; i < len - 1; i++) {
		int swap_pos = i;
		//内循环 找到最小元素的下标
		for (int j = i + 1; j < len; j++) {
			if (arr[j] < arr[swap_pos]) {
				swap_pos = j;
			}
		}
		if (swap_pos != i) {
			swap(arr[swap_pos], arr[i]);
		}
	}
}


//4
//快速排序   nlogn  不稳定  空间 logn 递归栈需要的空间
//算法导论中的快排
int partition(int a[], int left, int right) {
	int x = a[right];

	//i+1为枢轴的位置
	int i = left - 1;
	for (int j = left; j <= right - 1; j++) {
		if (a[j] <= x) {
			i = i + 1;
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1], a[right]);
	return i + 1;
}

//原始的快排划分算法
int hoare_partition(int a[], int left, int right) {
	//如果需要随机选择枢轴，请把随机选出的枢轴与第一个元素交换
	int x = a[left];
	int i = left;
	int j = right;
	while (i<j) {
		while (i<j&&a[j] >= x) --j;
		a[i] = a[j];  //避免了数据的交换操作
		while (i<j&&a[i] <= x) ++i;
		a[j] = a[i];
	}
	a[i] = x;
	return i;

}
void QuickSort(int arr[], int left, int right) {
	if (left < right) {
		//找出枢轴
		int q = hoare_partition(arr, left, right);
		//int q = partition(arr, left, right);
		cout << q << endl;
		print(arr, LEN);
		QuickSort(arr, left, q - 1);
		QuickSort(arr, q + 1, right);
	}
}
//自带的快排方法  <cstdlib>  qsort
//数组元素为int
int comp_int(const void * a, const void * b)
{
	return *(int *)a - *(int *)b;
}
void quicksort(int arr[], int len) {
	//qsort(arr, 100，sizeof(arr[0]), comp);
	qsort(arr, len, sizeof(int), comp_int);
}


//5
//归并排序  稳定排序  nlogn   空间复杂度 O(N)
vector<int> merge(vector<int>& a, int left, int right) {
	//递归结束条件  长度为1
	if (left == right) return vector<int>(1, a[left]);
	//划分为两半
	int mid = (right - left) / 2 + left;
	vector<int> l = merge(a, left, mid);
	vector<int> r = merge(a, mid + 1, right);
	//合并
	vector<int> ret;
	int size = right - left + 1;
	ret.reserve(size);
	int ll = 0, rr = 0;
	while (ll < l.size() && rr < r.size()) {
		if (l[ll] <= r[rr])
			ret.push_back(l[ll++]);
		else
			ret.push_back(r[rr++]);
	}
	//加入余下的部分
	while (ll < l.size())
		ret.push_back(l[ll++]);
	while (rr < r.size())
		ret.push_back(r[rr++]);
	return ret;
}
void MergeSort(vector<int>& a) {
	a = merge(a, 0, a.size() - 1);
}


//6
//堆排序  时间复杂度 nlogn  空间复杂度 1  不稳定
void make_heap(vector<int>& a, int size) {
	for (int i = size - 1; i > 0; i--) {
		if (i % 2 && a[i] > a[(i - 1) / 2])  //处理奇数下标
			swap(a[i], a[(i - 1) / 2]);
		else if (i % 2 == 0 && a[i] > a[(i - 2) / 2])  //处理偶数下标
			swap(a[i], a[(i - 2) / 2]);
	}
}
void HeapSort(vector<int>& a) {
	int n = a.size();
	while (n) {
		make_heap(a, n);   //每次把新的最大元素移动到堆顶，也就是a[0]
		n--;
		swap(a[0], a[n]);//然后把当前最大移动到后面来作为排好序的元素
	}
	
}



int main()
{
	int arr[LEN] = { 5,1,5,2,3,8,0,6,5,4 };
	//InsertSort(arr, LEN);

	//BubbleSort(arr, LEN);

	//SelectSort(arr, LEN);

	QuickSort(arr, 0,LEN-1);
	//quicksort(arr, LEN);

	//vector<int> arrV{ 5,1,7,2,3,8,0,6,9,4 };
	////归并排序
	////MergeSort(arrV);

	//HeapSort(arrV);
	//for (int i : arrV) {
	//	cout << i << "   ";
	//}
	//cout << endl;

	print(arr, LEN);

	system("pause");
	return 0;
}


