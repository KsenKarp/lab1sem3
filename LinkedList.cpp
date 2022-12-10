#include "LinkedList.h"
#include <iostream>
using namespace std;

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& old) : length(old.length) { //копирование
	first = new Node(old.first->data);
	Node* tmp_new = first;
	Node* tmp_old = old.first->next;
	while(tmp_old) {
		Node* add = new Node(tmp_old->data);
		tmp_new->next = add;
		tmp_new = tmp_new->next;
		tmp_old = tmp_old->next;
	}
}

template <class T>
LinkedList<T> ::LinkedList(LinkedList<T>* old) : length(old->length) {
	first = new Node(old->first->data);
	Node* tmp_new = first;
	Node* tmp_old = old->first->next;
	while (tmp_old) {
		Node* add = new Node(tmp_old->data);
		tmp_new->next = add;
		tmp_new = tmp_new->next;
		tmp_old = tmp_old->next;
	}
}

template <class T>
LinkedList<T> ::LinkedList(int _size, T* data) : length(_size) { //по размеру и массиву
	if (length != 0) {
		first = new Node(data[0]);
		Node* tmp = first;
		for (int i = 1; i < length; i++) {
			Node* add = new Node(data[i]);
			tmp->next = add;
			tmp = tmp->next;
		}
		//tmp->next = nullptr;
	}
	else
		first = nullptr;
}

template <class T>
LinkedList<T> ::LinkedList() : first(nullptr), length(0) {};

template <class T>
LinkedList<T> :: ~LinkedList() {
	for (int i = 0; i < length; i++) {
		Node* _head = first;
		first = first->next;
		delete _head;
	}
}

//template <class T>
//LinkedList<T>::Iterator::Iterator() : ptr(new Node<T>(nullptr)) {};

//template <class T>
//LinkedList<T>::Iterator::Iterator(Node* new_iter) : ptr(new_iter) {};

template <class T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator ++() {
	ptr = ptr->next;
	return (*this);
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator ++(int) {
	Iterator result = *this;
	++(*this);
	return result;
}

template <class T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator --() {
	Node* tmp = first;
	while (tmp->next != ptr) tmp = tmp->next;
	ptr = tmp;
	//ptr = ptr->previous
	return (*this);
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator --(int) {
	Iterator result = *this;
	--(*this);
	return result;
}

template <class T>
bool LinkedList<T>::Iterator::operator ==(Iterator it) {
	return (this->ptr == it.ptr);
}

template <class T>
bool LinkedList<T>::Iterator::operator !=(Iterator it) {
	return (this->ptr != it.ptr);
}

template <class T>
const T& LinkedList<T>::Iterator::operator *() {
	return this->ptr->data;
}

template <class T>
int LinkedList<T> ::get_length() const {
	return length;
}

template <class T>
const T& LinkedList<T> ::get_i(int index) {
	if ((index > length) || (index < 0)) {
		printf("Index out of range");       //throw exception, в динмассиве тоже кстати
		return first->data;
	}
	else {
		Node* tmp = first;
		for (int i = 0; i < index; i++) tmp = tmp->next;
		return tmp->data;
	}
}

template <class T>
auto LinkedList<T>:: get_tail(Node* cur) {
	while (cur->next != nullptr) cur = cur->next;
	return cur;
}

template <class T>
void LinkedList<T> ::insert_at(int index, T value) {
	if (!first && index==0) {
		first = new Node(value);
		length++;
		return;
	}
	else {
		if (index < 0 || index > length) {
			cout << "Index out of range\n";       //throw exception, в динмассиве тоже кстати
			return;
		}
		else {
			Node* add = new Node(value);
			if (index == 0) {
				add->next = first;
				first = add;
			}
			else {
				Node* tmp = first;
				for (int i = 1; i < index; i++) tmp = tmp->next;
				if (index < length) {
					Node* tmp_next = tmp->next;
					tmp->next = add;
					add->next = tmp_next;
				}
				else {
					tmp->next = add;
				}
			}
			length++;
			return;
		}
	}
}

template <class T>
void LinkedList<T>::set_i(int index, T item) {
	if ((index >= length) || (index < 0)) {
		printf("Index out of range");       //throw exception, в динмассиве тоже кстати
		return;
	}
	else {
		Node* tmp = first;
		for (int i = 0; i < index; i++) tmp = tmp->next;
		tmp->data = item;
	}
	return;
}

template <class T>
LinkedList<T>* LinkedList<T> ::get_sublist(int start, int end) {
	LinkedList<T>* res = new LinkedList<T>();
	Node* tmp = first;
	for (int i = 0; i < start; i++) tmp = tmp->next;
	res->first = new Node(tmp->data);
	res->length = 1;
	tmp = tmp->next;
	for (int i = start + 1; i <= end; i++) {
		res->insert_at(res->length, tmp->data);
		tmp = tmp->next;
	}
	return res;
}

template <class T>
void LinkedList<T>::delete_last() {
	if (length == 1) {
		delete first;
		length--;
		return;
	}
	Node* tmp = first->next;
	Node* tmp_prev = first;
	while (tmp->next) {
		tmp_prev = tmp_prev->next;
		tmp = tmp->next;
	}
	Node* to_del = tmp;
	tmp_prev = nullptr;
	delete to_del;
	length--;
	return;
}

template <class T>
void LinkedList<T>:: print_back(Node* node) {
	if (!node) return;
	else print_back(node->next);
	cout << node->data << " ";
	return;
}

template <class T>
void LinkedList<T>:: print_backwards() {
	print_back(first);
	return;
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() {
	Iterator it(this->first);
	return it;
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::end() {
	Node* tmp = first;
	while (tmp->next) tmp = tmp->next;
	return Iterator(tmp);
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::advance_forward(int index) {
	Iterator res = *this;
	for (int i = 0; i < index; i++) {
		++(*this);
	}
	return res;
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::advance_back(int index) {
	Iterator res = *this;
	for (int i = 0; i < index; i++) {
		--(*this);
	}
	return res;
}

template <class T>
int LinkedList<T>::real_index(Iterator it) {
	Iterator tmp = first;
	for (int i = 0; i < length; i++) {
		if (it == tmp)
			return i;
		++tmp;
	}
	return -1;
}

template <class T>
LinkedList<T>* LinkedList<T> ::quick_sort(bool (*cmp)(const T&, const T&), float& time) {
	LinkedList<T>* res = this->get_sublist(0, this->length - 1);
	auto begin = std::chrono::high_resolution_clock::now();
	res->quick_sort_res(&res->first, (*cmp));
	auto finish = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - begin);
	time = elapsed.count() * 1e-6;
	return res;
}

template <class T>
void LinkedList<T>::quick_sort_res(Node** res_head, bool(*compare)(const T&, const T&)) {
	(*res_head)	= quick_sort_(*res_head, get_tail(*res_head), (*compare));
	return;
}

template <class T>
auto LinkedList<T> :: quick_sort_(Node* head, Node* tail, bool (*compare)(const T&, const T&)) {
	if (!head || head == tail) return head;
	Node* new_head = nullptr;
	Node* new_tail = nullptr;
	Node* pivot = this->partition(&new_head, &new_tail, head, tail, (*compare));
	// If pivot is the smallest element - no need to recur the left part, else do it
	if (new_head != pivot) {
		Node* tmp = new_head;
		while (tmp->next != pivot) tmp = tmp->next;
		tmp->next = nullptr;

		new_head = this->quick_sort_(new_head, tmp, (*compare));
		// Change next of last node of the left half to pivot
		tmp = get_tail(new_head); 
		tmp->next = pivot;
	}
	// Recur for the list after the pivot element
	pivot->next = this->quick_sort_(pivot->next, new_tail, (*compare));

	return new_head;
}

template <class T>
auto LinkedList<T> :: partition(Node** new_head, Node** new_tail, Node* head, Node* tail, bool(*compare)(const T&, const T&)) {
	Node* pivot = tail;
	Node* prev = nullptr;
	Node* cur = head;
	Node* end = pivot;
	while (cur != pivot) {
		if (compare( pivot->data, cur->data)) {
			if ((*new_head) == nullptr) (*new_head) = cur;
			prev = cur;
			cur = cur->next;
		}
		else {
			if (prev) prev->next = cur->next;
			Node* tmp = cur->next;
			cur->next = nullptr;
			end->next = cur;
			end = cur;
			cur = tmp;
		}
	}

	if ((*new_head) == nullptr) (*new_head) = pivot;
	(*new_tail) = end; // Update newEnd to the current last node

	return pivot;
}

template <class T>
void LinkedList<T>::split(Iterator head, Iterator& left, Iterator& right) {
	Iterator fast = head;
	++fast;
	Iterator slow = head;
	while (fast != nullptr) {
		++fast;
		if (fast != nullptr) {
			++slow;
			++fast;
		}
	}
	Iterator slow_next = slow;
	++slow_next;
	left = head;
	right = slow_next;
	slow.ptr->next = nullptr;
	return;
}

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::merge(Iterator l1, Iterator l2, bool (*compare)(const T&, const T&)) {
	Iterator result = nullptr;
	if (l1 == nullptr) {
		return l2;
	}
	if (l2 == nullptr) {
		return l1;
	}
	if (compare(l2.operator*(), l1.operator*())) {
		result = l1;
		++l1;
	}
	else {
		result = l2;
		++l2;
	}
	Iterator tmp = result;
	while (l1 != nullptr && l2 != nullptr) {
		if (compare(l2.operator*(), l1.operator*())) {
			tmp.ptr->next = l1.ptr;
			++l1;
		}
		else {
			tmp.ptr->next = l2.ptr;
			++l2;
		}
		++tmp;
	}
	if (l1 != nullptr) {
		/*while (l1) {
			result->next = l1;
			result = result->next;
			l1 = l1->next;
		}*/
		tmp.ptr->next = l1.ptr;
	}
	if (l2 != nullptr) {
		/*while (l2) {
			result->next = l2;
			result = result->next;
			l2 = l2->next;
		}*/
		tmp.ptr->next = l2.ptr;
	}
	return result;
}

template <class T>
void LinkedList<T>::merge_sort_(Iterator& res_head, bool (*compare)(const T&, const T&)) {
	Iterator head = res_head;
	Iterator tmp = res_head;
	++tmp;
	Iterator left, right;
	if ((head == nullptr) || (tmp == nullptr)) return;
	split(head, left, right);
	merge_sort_(left, (*compare));
	merge_sort_(right, (*compare));
	res_head = merge(left, right, (*compare));
}

template <class T>
LinkedList<T>* LinkedList<T>::merge_sort(bool (*compare)(const T&, const T&), float& time) {
	LinkedList<T>* res = this->get_sublist(0, length - 1);
	auto begin = std::chrono::high_resolution_clock::now();
	Iterator res_head = res->begin();
	merge_sort_(res_head, (*compare));
	auto finish = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - begin);
	time = elapsed.count() * 1e-6;  //*1e-9 -- seconds => 1e-6 ..?
	return res;
}

template <class T>
void LinkedList<T>::bubble_sort(bool (*cmp)(const T&, const T&)) {
	Node* icurr = this->first;
	Node* jcurr = this->first;
	while (icurr) {
		jcurr = icurr;
		while (jcurr) {
			if (!cmp(jcurr->data, icurr->data)) {
				T tmp = icurr->data;
				icurr->data = jcurr->data;
				jcurr->data = tmp;
			}
			jcurr = jcurr->next;
		}
		icurr = icurr->next;
	}
}

template <class T>
LinkedList<T>* LinkedList<T>::bubble_sort(bool (*cmp)(const T&, const T&), float& time) {
	LinkedList<T>* res = this->get_sublist(0, length - 1);
	auto begin = std::chrono::high_resolution_clock::now();
	res->bubble_sort(( * cmp));
	auto finish = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - begin);
	time = elapsed.count() * 1e-6;  //*1e-9 -- seconds => 1e-6 ..?
	return res;
}