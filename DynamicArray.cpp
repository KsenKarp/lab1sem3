#include "DynamicArray.h"
#include <iostream>
using namespace std;

template <class T>
DynamicArray<T> :: DynamicArray(const DynamicArray <T>& old) : size(old.size), capacity(old.capacity) { //копирование
	data = new T[old.size];
	for (int i = 0; i < old.capacity; i++) {
		data[i] = old.data[i];
	}
}

template <class T>
DynamicArray<T> ::DynamicArray(DynamicArray<T>* old) : size(old->size), capacity(old->capacity) {
	data = new T[old->size];
	for (int i = 0; i < old->capacity; i++) {
		data[i] = old->data[i];
	}
}

template <class T>
DynamicArray<T> :: DynamicArray(int _size) : size(_size), capacity(0) { //по размеру
	if (size != 0) {
		data = new T[size];
	}
	else
		data = nullptr;
}

template <class T>
DynamicArray<T> :: DynamicArray(int _size, T* _data) : size(_size * 2), capacity(_size) { //по размеру и массиву
	if (size != 0) {
		data = new T[size];
		for (int i = 0; i < _size; i++) {
			data[i] = _data[i];
		}
	}
	else
		data = nullptr;
}

template <class T>
DynamicArray<T> :: ~DynamicArray() {
	if (data) delete[] data;
}

template <class T>
DynamicArray<T>::Iterator::Iterator() : ptr(nullptr) {};

template <class T>
DynamicArray<T>::Iterator::Iterator(T* new_iter) : ptr(new_iter) {};

template <class T>
typename DynamicArray<T>::Iterator& DynamicArray<T>::Iterator::operator ++() {
	++ptr;
	return (*this);
}

template <class T>
typename DynamicArray<T>::Iterator DynamicArray<T>::Iterator::operator ++(int) {
	Iterator result = *this;
	++(*this);
	return result;
}

template <class T>
typename DynamicArray<T>::Iterator& DynamicArray<T>::Iterator::operator --() {
	--ptr;
	return (*this);
}

template <class T>
typename DynamicArray<T>::Iterator DynamicArray<T>::Iterator::operator --(int) {
	Iterator result = *this;
	--(*this);
	return result;
}

template <class T>
bool DynamicArray<T>::Iterator::operator ==(Iterator it) {
	return (this->ptr == it.ptr);
}

template <class T>
bool DynamicArray<T>::Iterator::operator !=(Iterator it) {
	return (this->ptr != it.ptr);
}

template <class T>
bool DynamicArray<T>::Iterator::operator <(Iterator it) {
	return (this->ptr < it.ptr);
}

template <class T>
bool DynamicArray<T>::Iterator::operator <=(Iterator it) {
	return (this->ptr <= it.ptr);
}

template <class T>
bool DynamicArray<T>::Iterator::operator >(Iterator it) {
	return (this->ptr > it.ptr);
}

template <class T>
bool DynamicArray<T>::Iterator::operator >=(Iterator it) {
	return (this->ptr >= it.ptr);
}

template <class T>
const T& DynamicArray<T>::Iterator::operator *() {
	return *(ptr);
}

template <class T>
int DynamicArray<T> :: get_size() const {
	return size;
}

template <class T>
int DynamicArray<T> :: get_capacity() const {
	return capacity;
}

template <class T>
const T& DynamicArray<T> ::get_i(int index) {
	if ((index > capacity) || (index < 0)) {
		printf("Index out of range");
		return data[0];
	}
	else {
		return data[index];
	}
}

template <class T>
void DynamicArray<T>::set_i(int i, T item) {
	data[i] = item;
	return;
}

template <class T>
void DynamicArray<T> :: insert_at(int index, T value) {
	if (data == nullptr) {
		data = new T[2];
		size = 2;
	}
	if (capacity + 1 < size) {
		if (index == capacity) {
			data[index] = value;
			capacity++;
			return;
		}
		for (int i = capacity-1; i >= index; i--) {
			data[i + 1] = data[i];
		}
		data[index] = value;
		capacity = capacity + 1;
	}
	else {
		resize();
		if (index == capacity) {
			data[index] = value;
			capacity++;
			return;
		}
		for (int i = capacity; i >= index; i--) {
			data[i + 1] = data[i];
		}
		data[index] = value;
		capacity = capacity + 1;
	}
	return;
}

template <class T>
void DynamicArray<T> :: resize() {
	size = size * 2;
	T* copy_data = new T[size];
	for (int i = 0; i < capacity; i++) {
		copy_data[i] = data[i];
	}
	delete [] this->data;
	data = copy_data;
	return;
}

template <class T>
void DynamicArray<T>::delete_last() {
	this->capacity--;
	return;
}

template <class T>
T& DynamicArray<T> :: operator[] (int index) {
	return data[index];
}

template <class T>
typename DynamicArray<T>::Iterator DynamicArray<T>:: begin() {
	Iterator res(this->data);
	return res;
}

template <class T>
typename DynamicArray<T>::Iterator DynamicArray<T>::end() {
	return Iterator(this->data + capacity - 1);
}

template <class T>
typename DynamicArray<T>::Iterator DynamicArray<T>::advance_forward(int index) {
	Iterator res = *this;
	for (int i = 0; i < index; i++) {
		++(*this);
	}
	return res;
}

template <class T>
typename DynamicArray<T>::Iterator DynamicArray<T>::advance_back(int index) {
	Iterator res = *this;
	for (int i = 0; i < index; i++) {
		--(*this);
	}
	return res;
}

template <class T>
int DynamicArray<T>:: real_index(Iterator it) {
	Iterator tmp = data;
	for (int i = 0; i < capacity; i++) {
		if (it == tmp) 
			return i;
		++tmp;
	}
	return -1;
}

template <class T>
DynamicArray<T>* DynamicArray<T> :: get_subarray(int start, int end) {
	DynamicArray<T>* res = new DynamicArray<T>((end - start) * 2);
	int j = 0;
	for (int i = start; i <= end; i++) {
		res->insert_at(j, data[i]);
		j++;
	}
	return res;
}

template <class T>
DynamicArray<T>* DynamicArray<T> ::quick_sort(bool (*cmp)(const T&, const T&), float& time) {
	DynamicArray<T>* res = this->get_subarray(0, this->capacity - 1);
	auto begin = std::chrono::high_resolution_clock::now();
	res->quick_sort_((*cmp), res->begin(), res->end());
	auto finish = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - begin);
	time = elapsed.count() * 1e-6;
	return res;
}

template <class T>
void DynamicArray<T> ::quick_sort_(bool (*compare)(const T&, const T&), Iterator left, Iterator right) {
	if (left < right) {
		Iterator mid_index = partition((*compare), left, right);
		Iterator mid_index_next = mid_index;
		Iterator mid_index_prev = mid_index;
		++mid_index_next;
		--mid_index_prev;
		quick_sort_((*compare), left, mid_index_prev);
		quick_sort_((*compare), mid_index_next, right);
	}
	return;
}

template <class T>
typename DynamicArray<T>::Iterator DynamicArray<T> ::partition(bool (*compare)(const T&, const T&), Iterator left, Iterator right) {
	T pivot = right.operator*();
	Iterator i = left;
	--i;
	while (left < right) {
		if (compare(pivot, left.operator*())) {
			++i;
			T swp = i.operator*();
			*(i.ptr) = left.operator*();
			*(left.ptr) = swp;
		}
		++left;
	}
	Iterator i_next = i;
	++i_next;
	T tmp = i_next.operator*();
	*(i_next.ptr) = pivot;
	*(right.ptr) = tmp;
	return i_next;
}

template <class T>
void DynamicArray<T>:: merge(Iterator left, Iterator& middle, Iterator right, bool (*compare)(const T&, const T&)) {
	Iterator middle_next = middle;
	int real_mid = real_index(middle);
	++middle_next;
	Iterator end_first_subarray = middle;
	Iterator end_second_subarray = right;
	Iterator index_first_subarray = left;
	Iterator index_second_subarray = middle_next;
	int index_of_merged_array = 0;
	T* merged = new T[real_index(right) + 1];
	while ((index_first_subarray <= end_first_subarray) && (index_second_subarray <= end_second_subarray)) {
		if (compare(index_first_subarray.operator*(), index_second_subarray.operator*())) {
			*(merged + index_of_merged_array) = index_second_subarray.operator*();
			++index_second_subarray;
		}
		else {
			*(merged + index_of_merged_array) = index_first_subarray.operator*();
			++index_first_subarray;
		}
		++index_of_merged_array;
	}
	while (index_first_subarray <= end_first_subarray) {
		*(merged + index_of_merged_array) = index_first_subarray.operator*();
		++index_first_subarray;
		++index_of_merged_array;
	}
	while (index_second_subarray <= end_second_subarray) {
		*(merged + index_of_merged_array) = index_second_subarray.operator*();
		++index_second_subarray;
		++index_of_merged_array;
	}
	int counter = 0;
	for (Iterator tmp = left; tmp <= right; ++tmp) {
		*(tmp.ptr) = *(merged + counter);
		++counter;
	}
}

template <class T>
void DynamicArray<T>:: MergeSort_(Iterator left, Iterator right, bool (*compare)(const T&, const T&)) {
	if (left < right) {

		Iterator fast = left;
		++fast;
		Iterator slow = left;
		if (left == nullptr) slow = nullptr;
		else {
			if (left == right) slow = right;
			else {
				while (fast != right) {
					++fast;
					if (fast != right) {
						++slow;
						++fast;
					}
					else ++slow;
				}
			}
		}
		Iterator middle = slow;
		Iterator tmp = middle;
		++tmp;
		MergeSort_(left, middle, (*compare));
		MergeSort_(tmp, right, (*compare));
		merge(left, middle, right, (*compare));
	}
}

template <class T>
DynamicArray<T>* DynamicArray<T>:: merge_sort(bool (*compare)(const T&, const T&), float& time) {
	DynamicArray<T>* res = new DynamicArray<T>(this);
	auto begin = std::chrono::high_resolution_clock::now();
	res->MergeSort_(res->begin(), res->end(), (*compare));
	auto finish = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - begin);
	time = elapsed.count() * 1e-6;
	//printf("Time elapsed for merge sort by dynamic array: %.5f milliseconds.\n", elapsed.count() * 1e-6);
	return res;
}

template <class T>
void DynamicArray<T>::bubble_sort(bool (*cmp)(const T&, const T&)) {
	for (int i = 0; i <= capacity - 1  ; i++) {
		for (int j = i; j <= capacity - 1 ; j++) {
			if (cmp(this->data[j], this->data[i]) == false) {
				T tmp = this->data[i];
				this->data[i] = this->data[j];
				this->data[j] = tmp;
			}
		}
	}
}

template <class T>
DynamicArray<T>* DynamicArray<T>::bubble_sort(bool (*cmp)(const T&, const T&), float& time) {
	DynamicArray<T>* res = new DynamicArray<T>(this);
	auto begin = std::chrono::high_resolution_clock::now();
	res->bubble_sort((*cmp));
	auto finish = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - begin);
	time = elapsed.count() * 1e-6;
	//printf("Time elapsed for bubble sort by dynamic array: %.5f milliseconds.\n", elapsed.count() * 1e-6);
	return res;
}