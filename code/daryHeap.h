/*
	d-ary heap implementation based on binary heaps.

	GitHub: @Inmapg
*/
#ifndef daryHeap_h
#define daryHeap_h

#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

// Comparator used to establish the priority
template <typename T = int, typename Comparator = std::less<T>>
class daryHeap {

	// Contais the data
	std::vector<T> array;

	int numChildren;

	// Object that decides which element of the comparison is firstly leaving the heap.
	Comparator before;

public:
	daryHeap(int numCh = 1, Comparator c = Comparator()) : array(0), numChildren(numCh), before(c) {}

	daryHeap(daryHeap<T, Comparator> const&) = default;

	daryHeap<T, Comparator> & operator=(daryHeap<T, Comparator> const&) = default;

	~daryHeap() = default;

	// Inserts the element x (which includes its priority).
	void push(T const& x) {
		array.push_back(x);
		shiftUp(size() - 1);
	}

	// Returns the heap's size
	int size() const { return array.size(); }

	// Returns if the heap has no elements
	bool empty() const { return size() == 0; }

	// Returns the element with the major priority if the heap is not empty
	T const& top()  const {
		if (empty()) throw std::domain_error("The heap is empty.");
		else return array[0];
	}

	// Removes from the heap the element with the major priority if the heap is not empty
	void pop() {
		T e = deleteAt(0);
	}

	// Returns and removes from the heap the element at the index 'ind' if the heap is not empty
	T deleteAt(int ind) {
		if (empty())
			throw std::domain_error("You can't remove any element due to the heap is empty.");
		else if (ind >= size()) {
			throw std::domain_error("Position out of range");
		}
		else {
			T elem = array[ind];
			array[ind] = array[array.size() - 1];
			array.pop_back();
			if (!empty() && ind < size()) shiftDown(ind);
			return elem;
		}
	}

	// Prints the current state of the heap (just for debugging)
	void print(std::ostream & o) const {
		if (!empty()) {
			o << array[0];
			for (auto i = 1; i < size(); ++i)
				o << " | " << array[i];
			o << '\n';
		}
	}

	// Clears the heap (just for debugging)
	void clear() {
		array.clear();
	}

private:

	// Shifts up the element located on the position 'i' of the heap
	void shiftUp(int i) {
		T elem = array[i];
		int place = i;
		while (place > 0 && before(elem, array[parent(place)])) {
			array[place] = array[parent(place)];
			place = parent(place);
		}
		array[place] = elem;
	}

	// Shifts down the element located on the position 'i' of the heap
	void shiftDown(int i) {
		T elem = array[i];
		int place = i;
		int child; // left one
		bool end = false;
		while (getIndexK(place, 1) <= size() && !end) {
			child = mostPriorityPosition(place);
			// change child
			if (child < size() && before(array[child + 1], array[child]))
				++child;
			// shift up the child if it goes before the element that is shifting down
			if (before(array[child], elem)) {
				array[place] = array[child];
				place = child;
			}
			else end = true;
		}
		array[place] = elem;
	}

	int mostPriorityPosition(int i) {
		int result = getIndexK(i, 1);
		int k = 2;
		int pos = getIndexK(i, k);
		while (k <= numChildren && pos < size()) {
			if (before(array[pos], array[result])) {
				result = pos;
			}
			pos = getIndexK(i, k++);
		}
		return result;
	}

	// Returns the k th child
	int getIndexK(int child, int k) {
		return numChildren * child + k;
	}

	int parent(int child) {
		return (child - 1) / numChildren;
	}
};

template <typename T, typename Comparator>
inline std::ostream& operator<<(std::ostream & o, daryHeap<T, Comparator> const& a) {
	a.print(o);
	return o;
}
#endif
