#include "IndexedHeap.h"
#include <stdio.h>
#include <stdlib.h>
#include <set>

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
	int moreData[200];
};

class CompareItems
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
	IndexedHeap<TestItem, CompareItems> ih;
	ih.push(TestItem(4));
	check(ih.front().getData() == 4);
	ih.pop();
}

void test02()
{
	IndexedHeap<TestItem, CompareItems> ih;
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

void test03()
{
	const int n = 1000;
	IndexedHeap<TestItem, CompareItems> ih;
	std::multiset<int,std::greater<int> > s;
	for (int i = 0; i < n; i++)
	{
		int m = (int)randi();
		if (ih.size() < 100)
		{
			ih.push(m);
			s.insert(m);
			continue;
		}
		if (ih.size() > 200)
		{
			ih.pop();
			s.erase(s.begin());
			continue;
		}
		if (m > 0)
		{
			ih.push(m);
			s.insert(m);
		}
		else
		{
			int x = ih.front().getData();
			int y = *(s.begin());
			printf("(i=%d) x = %d  y = %d\n", i, x, y);
			check(x == y);
			ih.pop();
			s.erase(s.begin());
		}
	}
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	test01();
	test02();
	test03();

	printf("PASSED\n");
	return 0;
}

