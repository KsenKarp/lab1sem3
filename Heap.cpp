#include "Heap.h"

template <class T, class Use>
Heap<T, Use>:: Heap(bool (*_compare)(const T&, const T&), T* arr, int size) : compare((*_compare)) {
	heap = new Use();
	for (int i = 0; i < size; i++) {
		this->insert(arr[i]);
	}
}

template <class T, class Use>
Heap<T, Use>:: ~Heap() {
	if (heap) delete heap;
}

template <class T, class Use>
bool Heap<T, Use>::empty() {
	if (heap->get_length() == 0) return false;
	else return true;
}

template <class T, class Use>
T Heap<T, Use>::pop_first() {
	T res = heap->get_i(0);
	heap->set_i(0, heap->get_last());
	heap->delete_last();
	this->heapify(0);
	return res;
}

template <class T, class Use>
T Heap<T, Use>::peek_first() {
	return heap->get_i(0);
}

template <class T, class Use>
void Heap<T, Use>::insert(const T& item) {
	int add_idx = heap->get_length();
	heap->append(item);
	int parent_idx = (add_idx - 1) / 2;
	while (parent_idx >= 0 && add_idx > 0) {
		if (heap->get_i(add_idx) < heap->get_i(parent_idx)) {   //comparator
			T tmp = heap->get_i(add_idx);
			heap->set_i(add_idx, heap->get_i(parent_idx));
			heap->set_i(parent_idx, tmp);
		}
		add_idx = parent_idx;
		parent_idx = (add_idx - 1) / 2;
	}
}

template <class T, class Use>
void Heap<T, Use>::heapify(int idx) {
	int left = 2*idx + 1;
	int right = 2* idx + 2;
	T tmp;
	if (left < heap->get_length()) {
		if (heap->get_i(idx) > heap->get_i(left)) {  //comparator
			tmp = heap->get_i(idx);
			heap->set_i(idx, heap->get_i(left));
			heap->set_i(left, tmp);
			this->heapify(left);
		}
	}
	if (right < heap->get_length()) {
		if (heap->get_i(idx) > heap->get_i(right)) {   //comparator
			tmp = heap->get_i(idx);
			heap->set_i(idx, heap->get_i(right));
			heap->set_i(right, tmp);
			this->heapify(right);
		}
	}
}