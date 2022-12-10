#pragma once
#ifndef HEAP
#define HEAP

#include <iostream>
#include "Sequence_types.h"
using namespace std;

template <class T, class Use = ArraySequence<T>>
class Heap {
	Sequence<T>* heap;
	bool (*compare)(const T&, const T&);
	Heap(); //чтобы нельзя было его использовать!

public:
	Heap(bool (*_compare)(const T&, const T&)) : compare((*_compare)), heap(new Use()) {}; //true - i1>i2
	Heap(bool (*_compare)(const T&, const T&), T* arr, int size);
	~Heap();
	T pop_first();
	T peek_first();
	void insert(const T& item);
	void heapify(int idx);
	bool empty();
};

#endif