#pragma once

#ifndef DYNARR
#define DYNARR

#include <iostream>
#include <chrono>
using namespace std;

template <class T>
class DynamicArray {
public:
	class Iterator {
		friend class DynamicArray;
		T* ptr;
		Iterator();
		Iterator(T* new_iter);

	public:
		Iterator& operator ++();
		Iterator operator ++(int);
		Iterator& operator --();
		Iterator operator --(int);
		bool operator ==(Iterator it);
		bool operator !=(Iterator it);
		bool operator <(Iterator it);
		bool operator <=(Iterator it);
		bool operator >(Iterator it);
		bool operator >=(Iterator it);
		const T& operator *();
	};

private:
	T* data;
	int size;
	int capacity;
	void quick_sort_(bool (*compare)(const T&, const T&), Iterator left, Iterator right);
	Iterator partition(bool (*compare)(const T&, const T&), Iterator left, Iterator right);
	void merge(Iterator left, Iterator& middle, Iterator right, bool (*compare)(const T&, const T&));
	void MergeSort_(Iterator left, Iterator right, bool (*compare)(const T&, const T&));
	void bubble_sort(bool (*cmp)(const T&, const T&));

public:
	
	DynamicArray(const DynamicArray <T>& old);
	DynamicArray(DynamicArray<T>* old);
	DynamicArray(int _size);
	DynamicArray(int _size, T* _data);
	~DynamicArray();
	const T& get_i(int index);
	void set_i(int i, T item);
	int get_size() const;
	int get_capacity() const;
	void insert_at(int index, T item);
	void delete_last();
	void resize();
	DynamicArray<T>* get_subarray(int start, int end);
	T& operator[] (int index);

	Iterator begin();
	Iterator end();
	Iterator advance_forward(int amount);
	Iterator advance_back(int amount);
	int real_index(Iterator it);
	
	DynamicArray<T>* quick_sort(bool (*cmp)(const T&, const T&), float& time);
	DynamicArray<T>* merge_sort(bool (*cmp)(const T&, const T&), float& time);
	DynamicArray<T>* bubble_sort(bool (*cmp)(const T&, const T&), float& time);
};


#endif