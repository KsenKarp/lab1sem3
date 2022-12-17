#include "Isorter.h"
using namespace std;

template <class T>
Sequence<T>* Isorter<T>::quick_sort(Sequence<T>* seq, bool (*cmp)(const T&, const T&), float& time) {
	Sequence<T>* seq_q_sorted = seq->quick_sort((*cmp), time);
	return seq_q_sorted;
}

template <class T>
Sequence<T>* Isorter<T>::merge_sort(Sequence<T>* seq, bool (*cmp)(const T&, const T&), float& time) {
	Sequence<T>* seq_m_sorted = seq->merge_sort((*cmp), time);
	return seq_m_sorted;
}

template <class T>
Sequence<T>* Isorter<T>::bubble_sort(Sequence<T>* seq, bool (*cmp)(const T&, const T&), float& time) {
	Sequence<T>* seq_b_sorted = seq->bubble_sort((*cmp), time);
	return seq_b_sorted;
}