#include "IndexedHeap.h"
#include <stdio.h>
#include <stdlib.h>

void fail()
{
	printf("FAILED\n");
	exit(1);
}

void check(bool x)
{
	if (!x)
		fail();
}

class TestItem
{
public:
	TestItem() { }
	TestItem(int x) : data(x) { }
	int getData() const { return data; }
	void setData(int x) { data = x; }
protected:
	int data;
};

class compareItems
{
public:
	bool operator ()(const TestItem &lhs, const TestItem &rhs) const
	{
		return lhs.getData() < rhs.getData();
	}
};

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	IndexedHeap<TestItem, compareItems> ih;
	ih.push(TestItem(4));
	check(ih.front().getData() == 4);
	ih.pop();

	printf("PASSED\n");
	return 0;
}

