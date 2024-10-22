#pragma once

template<typename T, typename U>
class Priority_Queue {
public:
	Priority_Queue();
	//~Priority_Queue();

	// public getter methods
	T GetKey(int i);
	U GetValue(int i);
	int GetSize();

	void Push(T k, U v);
	T Pop();
private:
	static const int MAX_SIZE = 100;
	T keys[MAX_SIZE];
	U values[MAX_SIZE];

	int size = 0;

	// private getter helper methods
	int GetParent(int i);
	int GetLeftChild(int i);
	int GetRightChild(int i);

	void HeapifyUp(int i);
	void HeapifyDn(int i);
	void swap(int i, int j);
};

// constructor
template<typename T, typename U>
inline Priority_Queue<T, U>::Priority_Queue() {

}

// destructor
/*template<typename T, typename U>
inline Priority_Queue<T, U>::~Priority_Queue() {

}*/

// getter methods
template<typename T, typename U>
inline T Priority_Queue<T, U>::GetKey(int i) { return keys[i]; }

template<typename T, typename U>
inline U Priority_Queue<T, U>::GetValue(int i) { return values[i]; }

template<typename T, typename U>
inline int Priority_Queue<T, U>::GetSize() { return size; }

template<typename T, typename U>
inline int Priority_Queue<T, U>::GetParent(int i) { return (i - 1) / 2; }

template<typename T, typename U>
inline int Priority_Queue<T, U>::GetLeftChild(int i) { return 2 * i + 1; }

template<typename T, typename U>
inline int Priority_Queue<T, U>::GetRightChild(int i) { return 2 * i + 2; }

template<typename T, typename U>
inline void Priority_Queue<T, U>::Push(T k, U v) {
	keys[size] = k;
	values[size] = v;
	++size;
	HeapifyUp(size - 1);
}

template<typename T, typename U>
inline T Priority_Queue<T, U>::Pop() {
	T temp = keys[0];

	keys[0] = keys[size - 1];
	keys[size - 1] = NULL;
	values[0] = values[size - 1];
	values[size - 1] = values[size - 2];
	--size;

	HeapifyDn(0);

	return temp;
}

template<typename T, typename U>
inline void Priority_Queue<T, U>::HeapifyUp(int i) {
	if (i <= 0) return;

	int j = GetParent(i);

	if (keys[i] < keys[j]) swap(i, j);

	HeapifyUp(j);
}

template<typename T, typename U>
inline void Priority_Queue<T, U>::HeapifyDn(int i) {
	int j;

	// if no children
	if (GetLeftChild(i) > size - 1) return;

	// if no right child, but there is left child
	if (GetRightChild(i) > size - 1) j = GetLeftChild(i);
	// if there is left AND right child, select the lesser child
	else j = keys[GetLeftChild(i)] < keys[GetRightChild(i)] ? GetLeftChild(i) : GetRightChild(i);

	if (keys[i] > keys[j]) swap(i, j);

	HeapifyDn(j);
}

template<typename T, typename U>
inline void Priority_Queue<T, U>::swap(int i, int j)
{
	T tempKey = keys[i];
	keys[i] = keys[j];
	keys[j] = tempKey;

	U tempValue = values[i];
	values[i] = values[j];
	values[j] = tempValue;
}
