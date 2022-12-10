#pragma once
#ifndef SEQ
#define SEQ

#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
using namespace std;

template <class T>
class Sequence {
public:
	virtual const T& get_first() = 0;
	virtual const T& get_last() = 0;
	virtual const T& get_i(int index) = 0;
	virtual Sequence<T>* get_subsequence(int start, int end) = 0;
	virtual int get_length() const = 0;
	virtual void insert_at(int index, T item) = 0;
	virtual void prepend(T item) = 0;
	virtual void append(T item) = 0;
	virtual void set_i(int index, T item) = 0;
	virtual void delete_last() = 0;
	virtual Sequence<T>* copy() = 0;
	virtual Sequence<T>* quick_sort(bool (*compare)(const T&, const T&), float& time) = 0;
	virtual Sequence<T>* merge_sort(bool (*compare)(const T&, const T&), float& time) = 0;
	virtual Sequence<T>* bubble_sort(bool (*compare)(const T&, const T&), float& time) = 0;
};

template <class T>
class ArraySequence : public Sequence<T> {
	DynamicArray<T>* items;
	int length;

	ArraySequence(DynamicArray<T>* arr);
public:
	ArraySequence();
	ArraySequence(int size);
	ArraySequence(int size, T* data);
	ArraySequence(const ArraySequence<T>& old);
	~ArraySequence();
	virtual const T& get_first() override;
	virtual const T& get_last() override;
	virtual const T& get_i(int index) override;
	Sequence<T>* get_subsequence(int start, int end) override;
	virtual int get_length() const override;
	virtual void insert_at(int index, T item) override;
	virtual void prepend(T item) override;
	virtual void append(T item) override;
	virtual void set_i(int index, T item) override;
	virtual void delete_last() override;
	virtual Sequence<T>* copy() override;
	virtual Sequence<T>* quick_sort(bool (*compare)(const T&, const T&), float& time) override;
	virtual Sequence<T>* merge_sort(bool (*compare)(const T&, const T&), float& time) override;
	virtual Sequence<T>* bubble_sort(bool (*compare)(const T&, const T&), float& time) override;
};

template <class T>
class ListSequence : public Sequence<T> {
	LinkedList<T>* items;
	int length;
public:
	ListSequence();
	//ListSequence(int size);
	ListSequence(int size, T* data);
	ListSequence(const ListSequence<T>& old);
	ListSequence(ListSequence<T>* old);
	ListSequence(LinkedList<T>* list);
	~ListSequence();
	virtual const T& get_first() override;
	virtual const T& get_last() override;
	virtual const T& get_i(int index) override;
	Sequence<T>* get_subsequence(int start, int end) override;
	virtual int get_length() const override;
	virtual void insert_at(int index, T item) override;
	virtual void prepend(T item) override;
	virtual void append(T item) override;
	virtual void set_i(int index, T item) override;
	virtual void delete_last() override;
	virtual Sequence<T>* copy() override;
	virtual Sequence<T>* quick_sort(bool (*compare)(const T&, const T&), float& time) override;
	virtual Sequence<T>* merge_sort(bool (*compare)(const T&, const T&), float& time) override;
	virtual Sequence<T>* bubble_sort(bool (*compare)(const T&, const T&), float& time) override;
};
#endif