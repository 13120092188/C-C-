/*¿ìËÙÅÅĞò*/
#include<iostream>
#include<Windows.h>
using namespace std;

int Partition1(int *arr, int first, int last) {
	int key = arr[first];
	while (first < last)
	{
		while (first < last && arr[last] >= key)
		{
			last--;
		}
		arr[first] = arr[last];

		while (first < last && arr[first] <= key)
		{
			first++;
		}
		arr[last] = arr[first];
	}
	arr[first] = key;
	return first;
}

int Partition2(int * arr, int first, int last) {
	int key = arr[first];
	int i = first;
	for (int j = first + 1; j <= last; j++) {
		if (arr[j] <= key) {
			i++;
			swap<int>(arr[i], arr[j]);
		}
	}
	swap<int>(arr[i], arr[first]);
	return i;
}

int QuickSort(int * arr, int low, int high) {
	if (low >= high) return -1;

	int r = Partition2(arr, low, high);
	QuickSort(arr, low, r - 1);
	QuickSort(arr, r + 1, high);
}

int main() {
	int arr[] = { 3,5,9,7,4,1,2 };
	DWORD start, stop;
	//unsigned int t = 0;
	start = GetTickCount();
	QuickSort(arr, 0, 6);
	//while (t++ < 10e+6);
	stop = GetTickCount();
	cout << stop - start << endl;
	for (int i = 0; i < 7; i++)
		cout << arr[i] << endl;

	system("pause");
	return 0;
}