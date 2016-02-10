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

unsigned seed = 123456789;

unsigned randi()
{
	const unsigned a = 1103515245;
	const unsigned c = 12345;
	seed = a * seed + c;
	return seed;
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

void test01()
{
	IndexedHeap<TestItem, compareItems> ih;
	ih.push(TestItem(4));
	check(ih.front().getData() == 4);
	ih.pop();
}

void test02()
{
	IndexedHeap<TestItem, compareItems> ih;
	ih.push(TestItem(1));
	ih.push(TestItem(3));
	ih.push(TestItem(2));
	check(ih.front().getData() == 3);
	ih.pop();
	check(ih.front().getData() == 2);
	ih.pop();
	check(ih.front().getData() == 1);
	ih.pop();
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	test01();
	test02();

	printf("PASSED\n");
	return 0;
}

