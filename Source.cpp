#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include "DynamicArray.cpp"
#include "LinkedList.cpp"
#include "Sequence_types.cpp"
#include "Isorter.cpp"
#include <SDL.h>
#include <vector>

int main(int argc, char* argv[]) {

	random_integer_sequence(2000, "lab1file.txt");
	draw_arr_seq(2000, "lab1file.txt", (*a_greater_b));
	//draw_list_seq(2000, "lab1file.txt", (*a_greater_b));
	Isorter<int> sorter;
	int arr2[5] = { -1, 8, 2, 0, 0 };
	DynamicArray<int> dynarr(5, arr2);

	ArraySequence<int> arr(5, arr2);
	float time00;
	Sequence<int>* arr_q_sorted = sorter.quick_sort(&arr, (*a_greater_b), time00);
	cout << "Quick sort array sequence: ";
	for (int i = 0; i < arr_q_sorted->get_length(); i++) {
		cout << arr_q_sorted->get_i(i) << " ";
	}
	cout << endl;
	cout << "Time elapsed for quick sort by dynamic array: " << time00 << " milliseconds\n";

	float msort_array_time;
	Sequence<int>* arr_m_sorted = sorter.merge_sort(&arr, (*a_greater_b), msort_array_time);
	cout << "Merge sort array sequence: ";
	for (int i = 0; i < 5; i++) {
		cout << arr_m_sorted->get_i(i) << " ";
	}
	cout << endl;
	cout << "Time elapsed for merge sort by dynamic array: " << msort_array_time << " milliseconds\n";

	float bsort_array_time;
	Sequence<int>* arr_b_sorted = sorter.bubble_sort(&arr, (*a_greater_b), bsort_array_time);
	cout << "Bubble sort array sequence: ";
	for (int i = 0; i < 5; i++) {
		cout << arr_b_sorted->get_i(i) << " ";
	}
	cout << endl;
	cout << "Time elapsed for bubble sort by dynamic array: " << bsort_array_time << " milliseconds\n";

	ListSequence<int> lseq(5, arr2);
	float qsort_list_time;
	Sequence<int>* lseq_q_sorted = sorter.quick_sort(&arr, (*a_greater_b), qsort_list_time);
	cout << "Quick sort list sequence: ";
	for (int i = 0; i < 5; i++) {
		cout << lseq_q_sorted->get_i(i) << " ";
	}
	cout << endl;
	cout << "Time elapsed for quick sort by linked list: " << qsort_list_time << " milliseconds\n";

	float msort_list_time;
	Sequence<int>* lseq_m_sorted = sorter.merge_sort(&arr, (*a_greater_b), msort_list_time);
	cout << "Merge sort list sequence: ";
	for (int i = 0; i < lseq_m_sorted->get_length(); i++) {
		cout << lseq_m_sorted->get_i(i) << " ";
	}
	cout << endl;
	cout << "Time elapsed for merge sort by linked list: " << msort_list_time << " milliseconds\n";

	float bsort_list_time;
	Sequence<int>* lseq_b_sorted = sorter.bubble_sort(&arr, (*a_greater_b), bsort_list_time);
	cout << "Bubble sort list sequence: ";
	for (int i = 0; i < lseq_b_sorted->get_length(); i++) {
		cout << lseq_b_sorted->get_i(i) << " ";
	}
	cout << endl;
	cout << "Time elapsed for bubble sort by linked list: " << bsort_list_time << " milliseconds\n";
	
	return 0;
}
