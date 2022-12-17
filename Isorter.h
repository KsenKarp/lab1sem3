#pragma once
#ifndef SORTER
#define SORTER
#include "Sequence_types.h"

template <class T>
class Isorter {
public:
	Sequence<T>* quick_sort(Sequence<T>* seq, bool (*compare)(const T&, const T&), float& time);
	Sequence<T>* merge_sort(Sequence<T>* seq, bool (*compare)(const T&, const T&), float& time);
	Sequence<T>* bubble_sort(Sequence<T>* seq, bool (*compare)(const T&, const T&), float& time);
};

#endif