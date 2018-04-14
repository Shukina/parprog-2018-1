#include <iostream>
#include <cstdio> 
#include <random>
#include <omp.h>

using namespace std;

int separation(double arr[], int first, int last, double pivot) { //���������� �� ������ ��������, ����� ����� ��� �������� < pivot
	int j = first - 1;
	for (int i = first; i <= last; ++i) {
		if (arr[i] < pivot) {
			std::swap(arr[++j], arr[i]);
		}
	}
	return j; //������� pivot
}

int separation_index(double arr[], int first, int last, int index) { //���������� �� �������
	std::swap(arr[index], arr[last]);
	int i = 1 + separation(arr, first, last, arr[last]);
	std::swap(arr[i], arr[last]);
	return i; //������� �� ������� ����� ������� ������� ����� �� ������� index
}

void Select(double arr[], int first, int last, int index) { //����� ������� �������
	int i = separation_index(arr, first, last, (first + last) / 2); //�������� ����� ������� �������
	if (i > index) { //���� ����� ������� ������� ������ �������
		Select(arr, first, i - 1, index); //�� �������� ����� ����� �� ������ �������
	}
	else if (i < index) {
		Select(arr, i + 1, last, index); //�������� ������ ����� ����� ������ �������
	}
}

int BinSearch(double arr[], int first, int last, double x) { //�������� ������, ���������� ������, ��� �������� ������������ �������, ������� ������ �

	double max = 0;
	int max_ind;
	for (int i = first; i <= last; i++)
	{
		if (arr[i] > max && arr[i] < x)
		{
			max = arr[i];
			max_ind = i;
		}
	}
	return max_ind;
}

double BinSearch3(double arr[], int first, int last, double x) { //����� ������������� ��������, ������� ������ �, ���������� ���
																 //���� ����� ��������� �� ���������� ���������� 0
	if (first == last - 1)
	{
		if (arr[first] <= arr[last])
		{
			if (arr[last] < x)
				return arr[last];
			else if (arr[first] < x)
				return arr[first];
			else return 0;
		}
		else //(items[first] > items[last])
		{
			if (arr[first] < x)
				return arr[first];
			else if (arr[last] < x)
				return arr[last];
			else return 0;
		}

	}
	int mid = (first + last) / 2;

	double m1 = BinSearch3(arr, first, mid, x);
	double m2 = BinSearch3(arr, mid, last, x);

	if (m1 > m2)
		return m1;
	else
		return m2;
}

void quicksort(double *array, int size)
{
	int l = 0;
	int r = size - 1;
	double temp = array[size / 2];

	do
	{
		while (array[l] < temp)
			l++;
		while (array[r] > temp)
			r--;

		if (l <= r)
		{
			double tmp = array[l];
			array[l] = array[r];
			array[r] = tmp;
			l++;
			r--;
		}
	} while (l <= r);

	if (r > 0)
		quicksort(array, r + 1);
	if (l < size)
		quicksort(&array[l], size - l);
}

void quicksort(double arr[], int first, int last) { //������� ����������� ����������
	int i = separation_index(arr, first, last, (first + last) / 2);
	if (i - 1 > first) {
		quicksort(arr, first, i - 1);
	}
	if (i + 1 < last) {
		quicksort(arr, i + 1, last);
	}
}

void quicksort_omp(double items[], int first, int last, int deep, int maxDeep) { //0, 8
	if (deep >= maxDeep) { //���� ������� ������� ������ ������������
		quicksort(items, first, last); //������ ��������� ����������
	}
	else {
		int i = (first + last) / 2; //����� �� �������� ���������� �������
		Select(items, first, last, i); //� ��������� �������

#pragma omp parallel
		{
#pragma omp sections nowait
			{
#pragma omp section
				if (i - 1 > first) {
					quicksort_omp(items, first, i - 1, deep + 1, maxDeep);
				}
#pragma omp section
				if (i + 1 < last) {
					quicksort_omp(items, i + 1, last, deep + 1, maxDeep);
				}
			}
		}
	}
}

void quicksort_omp(double arr[], int first, int last) {
	int maxDeep = (int)(ceil(log((double)omp_get_num_procs()) / log(2.0))); //������������ ������� ��������� ���� 8 ������� �� 3
	quicksort_omp(arr, first, last, 0, maxDeep);
}


void printArray(double* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}


