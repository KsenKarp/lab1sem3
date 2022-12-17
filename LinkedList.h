#pragma once
#include <iostream>
#include <chrono>
using namespace std;
#ifndef LIST
#define LIST

template <class T>
class LinkedList {
	struct Node {
		Node* next;
		T data;
		Node() : next(nullptr), data(T()) {};
		Node(T _data) : next(nullptr), data(_data) {};
	};
	Node* first;
	int length;

public:
	class Iterator {
		friend class LinkedList;
		Node* ptr;
		Iterator() : ptr(nullptr) {};
		Iterator(Node* new_iter) : ptr(new_iter) {};

	public:
		Iterator& operator ++();
		Iterator operator ++(int);
		Iterator& operator --();
		Iterator operator --(int);
		bool operator ==(Iterator it);
		bool operator !=(Iterator it);
		const T& operator *();
	};

private:
	auto get_tail(Node* cur);
	auto quick_sort_(Node* head, Node* tail, bool (*compare)(const T&, const T&));
	auto partition(Node** new_head, Node** new_tail, Node* head, Node* tail, bool(*compare)(const T&, const T&));
	void quick_sort_res(Node** res_head, bool(*compare)(const T&, const T&));
	Iterator merge(Iterator l1, Iterator l2, bool (*compare)(const T&, const T&));
	void split(Iterator head, Iterator& left, Iterator& right);
	void merge_sort_(Iterator& res_head, bool (*compare)(const T&, const T&));
	void bubble_sort(bool (*cmp)(const T&, const T&));

public:

	LinkedList(const LinkedList<T>& old);
	LinkedList(LinkedList<T>* old);
	LinkedList(int _size, T* data);
	LinkedList();
	~LinkedList();
	const T& get_i(int index);
	int get_length() const;
	void insert_at(int index, T item);
	void set_i(int index, T item);
	LinkedList<T>* get_sublist(int start, int end);
	void delete_last();
	void print_backwards();
	void print_back(Node* node);

	Iterator begin();
	Iterator end();
	Iterator advance_forward(int amount);
	Iterator advance_back(int amount);
	int real_index(Iterator it);

	LinkedList<T>* quick_sort(bool (*cmp)(const T&, const T&), float& time);
	LinkedList<T>* merge_sort(bool (*cmp)(const T&, const T&), float& time);
	LinkedList<T>* bubble_sort(bool (*cmp)(const T&, const T&), float& time);
	/*Node* reverse(Node* head) {
		if (head == nullptr || head->next == nullptr) return head;
		Node* rest = reverse(head->next);
		head->next->next = head;
		head->next = nullptr;
		return rest;
	}
	void reverse() {
		first = reverse(first);
		return;
	}*/
};

#endif