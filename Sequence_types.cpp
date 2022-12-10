#include "Sequence_types.h"

template <class T>
const T& ArraySequence<T>::get_first() {
	return items->get_i(0);
}

template <class T>
ArraySequence<T> ::ArraySequence() : items(new DynamicArray<T>(1)), length(0) {};

template <class T>
ArraySequence<T>::ArraySequence(int size) : items(new DynamicArray<T>(size)), length(0) {};

template <class T>
ArraySequence<T>::ArraySequence(int size, T* data) : items(new DynamicArray<T>(size, data)), length(items->get_capacity()) {};

template <class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& old) : items(new DynamicArray<T>(&old.items)), length(old.length) {};

template <class T>
ArraySequence<T>::ArraySequence(DynamicArray<T>* arr) : items(new DynamicArray<T>(arr)), length(arr->get_capacity()) {};

template <class T> 
ArraySequence<T>::~ArraySequence() {
	if (items) {
		items->~DynamicArray();
		length = 0;
	}
}

template <class T>
const T& ArraySequence<T>::get_last() {
	return items->get_i(length);
}

template <class T>
const T& ArraySequence<T>::get_i(int index) {
	return items->get_i(index);
}

template <class T>
Sequence<T>* ArraySequence<T>::get_subsequence(int start, int end) {
	ArraySequence<T>* res = new ArraySequence<T>(items->get_subarray(start, end));
	return static_cast<Sequence<T>*> (res);
}

template <class T>
int ArraySequence<T>::get_length() const {
	return items->get_capacity();
}

template <class T>
void ArraySequence<T>::insert_at(int index, T item) {
	items->insert_at(index, item);
	length++;
	return;
}

template <class T>
void ArraySequence<T>::set_i(int index, T item) {
	items->set_i(index, item);
	return;
}

template <class T>
void ArraySequence<T>::delete_last() {
	items->delete_last();
	length--;
	return;
}

template <class T>
void ArraySequence<T>::prepend(T item) {
	items->insert_at(0, item);
	length++;
	return;
}

template <class T>
void ArraySequence<T>::append(T item) {
	items->insert_at(items->get_capacity(), item);
	length++;
	return;
}

template <class T>
Sequence<T>* ArraySequence<T>::copy() {
	return this->get_subsequence(0, length);
}

template <class T>
Sequence<T>* ArraySequence<T>::quick_sort(bool (*cmp)(const T&, const T&), float& time) {
	ArraySequence<T>* res = new ArraySequence<T>(items->get_capacity());
	res->items = items->quick_sort((*cmp), time);
	return res;
}

template <class T>
Sequence<T>* ArraySequence<T>::merge_sort(bool (*cmp)(const T&, const T&), float& time) {
	ArraySequence<T>* res = new ArraySequence<T>(items->get_capacity());
	res->items = items->merge_sort((*cmp), time);
	return res;
}

template <class T>
Sequence<T>* ArraySequence<T>::bubble_sort(bool (*cmp)(const T&, const T&), float& time) {
	ArraySequence<T>* res = new ArraySequence<T>(items->get_capacity());
	res->items = items->bubble_sort((*cmp), time);
	return res;
}

template <class T>
ListSequence<T>::ListSequence() : items(new LinkedList<T>()), length(0) {};

template <class T>
ListSequence<T>::ListSequence(int size, T* data) : items(new LinkedList<T>(size, data)), length(size) {};

template <class T>
ListSequence<T>::ListSequence(const ListSequence<T>& old) : items(new LinkedList<T>(old.items)), length(old.get_length()) {};

template <class T>
ListSequence<T>::ListSequence(ListSequence<T>* old) : items(new LinkedList<T>(old->items)), length(old->get_length()) {};

template <class T>
ListSequence<T>::ListSequence(LinkedList<T>* list) : items(new LinkedList<T>(list)), length(list->get_length()) {};

template <class T>
ListSequence<T>::~ListSequence() {
	items->~LinkedList();
	length = 0;
}

template <class T>
const T& ListSequence<T>::get_i(int index) {
	return items->get_i(index);
}

template <class T>
const T& ListSequence<T>::get_first() {
	return items->get_i(0);
}

template <class T>
const T& ListSequence<T>::get_last() {
	return items->get_i(length-1);
}

template <class T>
Sequence<T>* ListSequence<T>::get_subsequence(int start, int end) {
	ListSequence<T>* res = new ListSequence<T>(items->get_sublist(start, end));
	return static_cast<Sequence<T>*> (res);
}

template <class T>
int ListSequence<T>::get_length() const {
	return length;
}

template <class T>
void ListSequence<T>::prepend(T item) {
	items->insert_at(0, item);
	length++;
	return;
}

template <class T>
void ListSequence<T>::append(T item) {
	items->insert_at(length, item);
	length++;
	return;
}

template <class T>
void ListSequence<T>::insert_at(int index, T item) {
	items->insert_at(index, item);
	length++;
	return;
}

template <class T>
void ListSequence<T>::set_i(int index, T item) {
	items->set_i(index, item);
	return;
}

template <class T>
void ListSequence<T>::delete_last() {
	if (length == 1) {
		cout << "Nope\n";
		return;
	}
	items->delete_last();
	length--;
	return;
}

template <class T>
Sequence<T>* ListSequence<T>::copy() {
	return this->get_subsequence(0, length);
}

template <class T>
Sequence<T>* ListSequence<T>::quick_sort(bool (*cmp)(const T&, const T&), float& time) {
	ListSequence<T>* res = new ListSequence<T>(items->quick_sort(*cmp, time));
	return res;
}

template <class T>
Sequence<T>* ListSequence<T>::merge_sort(bool (*cmp)(const T&, const T&), float& time) {
	ListSequence<T>* res = new ListSequence<T>(items->merge_sort(*cmp, time));
	return res;
}

template <class T>
Sequence<T>* ListSequence<T>::bubble_sort(bool (*cmp)(const T&, const T&), float& time) {
	ListSequence<T>* res = new ListSequence<T>(items->bubble_sort(*cmp, time));
	return res;
}