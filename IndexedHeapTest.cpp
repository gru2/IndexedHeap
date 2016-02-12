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
		printf("operator < %d, %d\n", lhs.getData(), rhs.getData());
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
	printf("(0) next is ih.push(TestItem(1))\n");
	ih.push(TestItem(1));
	ih.push(TestItem(6));
	ih.push(TestItem(5));
	printf("(1) next is ih.push(TestItem(3))\n");
	ih.push(TestItem(7));
	ih.push(TestItem(3));
	printf("(2)\n");
	ih.push(TestItem(2));
	ih.push(TestItem(4));
	printf("(3)\n");
	const TestItem &ti1 = ih.front();
	printf("(4)\n");
	check(ti1.getData() == 7);
	ih.pop();
	check(ih.front().getData() == 6);
	ih.pop();
	check(ih.front().getData() == 5);
	ih.pop();
	check(ih.front().getData() == 4);
	ih.pop();
	check(ih.front().getData() == 3);
	ih.pop();
	ih.push(TestItem(5));
	ih.push(TestItem(0));
	ih.push(TestItem(6));
	ih.push(TestItem(3));
	check(ih.front().getData() == 6);
	ih.pop();
	check(ih.front().getData() == 5);
	ih.pop();
	check(ih.front().getData() == 3);
	ih.pop();
	check(ih.front().getData() == 2);
	ih.pop();
	check(ih.front().getData() == 1);
	ih.pop();
	check(ih.front().getData() == 0);
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

