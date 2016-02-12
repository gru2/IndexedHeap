#ifndef __INDEXED_HEAP_H
#define __INDEXED_HEAP_H

#include <vector>
#include <algorithm>
#include <functional>
#include <stdio.h>

template <typename T, typename Compare>
class CompareEntries
{
public:
	CompareEntries<T, Compare>(const std::vector<T> &x) : entries(x) { }
	bool operator()(int x, int y) const
	{
		Compare compare;
		printf("entries = [ ");
		for (int i = 0; i < entries.size(); i++)
		{
			printf("%d ", entries[i].getData());
		}
		printf("]\n");
		printf("CompareEntries::operator()(%d, %d)\n", x, y);
		return compare(entries[x], entries[y]);
	}
	const std::vector<T> &entries;
};

template <typename T, typename Compare = std::less<T> >
class IndexedHeap
{
public:
	IndexedHeap<T, Compare>() : freeEntry(-1) { }

	const T &front() const {
		int index = indices.front();
		printf("(front) index = %d\n", index);
		printf("(front) entries[%d] = %d\n", index, entries[index].getData());
		return entries[index]; }
	void pop();
	void push(const T &x);
	size_t size() const { return indices.size(); }
	bool empty() const { return indices.empty(); }
	void clear() {
		indices.clear();
		entries.clear();
		freeEntry = -1;
	}

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
	CompareEntries<T, Compare> compareEntries(entries);
	std::pop_heap(indices.begin(), indices.end(), compareEntries);
	indices.pop_back();
	printf("(pop) indices = [ ");
	for (int i = 0; i < indices.size(); i++)
	{
		printf("%d ", indices[i]);
	}
	printf("]\n");
	printf("(pop) entries = [ ");
	for (int i = 0; i < entries.size(); i++)
	{
		printf("%d ", entries[i].getData());
	}
	printf("]\n");
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
	T &entry = entries[freeEntry];
	freeEntry = entry.getData();
	entry = x;

	CompareEntries<T, Compare> compareEntries(entries);
	std::push_heap(indices.begin(), indices.end(), compareEntries);
	printf("(push) indices = [ ");
	for (int i = 0; i < indices.size(); i++)
	{
		printf("%d ", indices[i]);
	}
	printf("]\n");
	printf("(push) entries = [ ");
	for (int i = 0; i < entries.size(); i++)
	{
		printf("%d ", entries[i].getData());
	}
	printf("]\n");
}

#endif

