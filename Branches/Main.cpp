#include <iostream>
#include "Tree.h"

void print(int *array, int size) {

	for (int i = 0; i < size; ++i) {

		std::cout << array[i] << std::endl;


	}


}

void merge(int*array, int begin,int mid,  int end) {





}
void bubblesort(int* array, int size) {



	for (int i = 0; i < size - 1; ++i) {
		for (int n = 0; n < size - 1; ++n) {
			if (array[n] > array[n + 1]) {
				int x = array[n];
				array[n] = array[n + 1];
				array[n + 1] = x;

			}
		}



	}
}

void  mergesort(int* array, int begin, int end) {


	if (begin < end) {


		int mid = (begin + end) / 2;
		mergesort(array, begin, mid);
		mergesort(array, mid + 1, end);
		merge(array, begin, mid, end);

	}


}
void swap(int start, int finish)
{
	int t = start;
	start = finish;
	finish = t;
}

int partition(int* array, int begin, int end) {
	int pivot = array[end];
	int p = (begin - 1);
	for (int i = begin; i <= end; ++i) {
	if (array[i] <= pivot) {
	i++;
	swap(array[p], array[i]);
	}
	}
return (p+1);





	

}
void quicksort(int *array, int begin, int end) {

	if (begin < end) {
		int PivotIndex = partition(array, begin, end);
		quicksort(array, begin, PivotIndex - 1);
		quicksort(array, PivotIndex + 1, end);



	}


}



int main() {

	int v[10] = { 9,2,8,1,7,3,6,4,5,0 };
	/*std::cout << "----------NOT SORTED-------------" << std::endl;
	print(v, 10);
	mergesort(v, 0, 9);
	std::cout << "----------MERGESORT-------------" << std::endl;
	print(v, 10);
	bubblesort(v, 10);
	std::cout << "--------BUBBLESORT---------------" << std::endl;
	print(v, 10);*/
	quicksort(v, 0, 9);
	std::cout << "--------QUICKSORT---------------" << std::endl;
	print(v, 10);

	





	system("pause");
	return 0;
}