#ifndef __INDEXED_HEAP_H
#define __INDEXED_HEAP_H

#include <vector>
#include <algorithm>
#include <functional>

template <typename T, typename Compare>
class CompareEntries
{
public:
	CompareEntries<T, Compare>(const std::vector<T> &x) : entries(x) { }
	bool operator()(int x, int y) const
	{
		Compare compare;
		return compare(entries[x], entries[y]);
	}
	const std::vector<T> &entries;
};

template <typename T, typename Compare = std::less<T> >
class IndexedHeap
{
public:
	IndexedHeap<T, Compare>() : freeEntry(-1) { }

	const T &front() const { return entries[indices.front()]; }
	void pop();
	void push(const T &x);

protected:
	int freeEntry;
	std::vector<T> entries;
	std::vector<int> indices;
};

template <typename T, typename Compare>
void IndexedHeap<T, Compare>::pop()
{
	int i = indices.front();
	entries[i].setData(freeEntry);
	freeEntry = i;
}

template <typename T, typename Compare>
void IndexedHeap<T, Compare>::push(const T &x)
{
	if (freeEntry < 0)
	{
		int n = (int)entries.size();
		int m = n << 1;
		if (m < 2)
			m = 2;
		entries.resize(m);
		freeEntry = n;
		for (int i = n; i < m - 1; i++)
			entries[i].setData(i + 1);
		entries[m - 1].setData(-1);
	}
	indices.push_back(freeEntry);
	CompareEntries<T, Compare> compareEntries(entries);
	std::push_heap(indices.begin(), indices.end(), compareEntries);
	T &entry = entries[freeEntry];
	freeEntry = entry.getData();
	entry = x;
}

#endif

