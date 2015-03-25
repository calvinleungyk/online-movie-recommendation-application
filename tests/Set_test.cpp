#include "Set.h"
#include "gtest/gtest.h"
#include <vector>
#include <iostream>

using namespace std;

// The fixture for testing class.
class SetTest: public ::testing::Test
{
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	SetTest()
	{
		// You can do set-up work for each test here.
	}

	virtual ~SetTest()
	{
		// You can do clean-up work that doesn't throw exceptions here.		
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	virtual void SetUp()
	{
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown()
	{
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
};

/*TEST_F(ArrayTest, BasicCase)
{
	for(int i = 0; i < s; ++i) EXPECT_EQ(i, a->get(i));
}*/

TEST_F (SetTest, BasicCase_Union) {
  Set<int> a;
  a.add(1);
  a.add(2);
  a.add(3);
  a.add(4);
  a.add(5);
  Set<int> b;
  b.add(1);
  b.add(3);
  b.add(5);
  b.add(7);
  b.add(9);
  Set<int> c = b.setUnion(a);
  Set<int>::Iterator si = c.begin();
  for(unsigned int i = 0; i < 5; i++) {
    EXPECT_EQ(*si, i + 1);
    ++si;
  }
  EXPECT_EQ(*si, 7);
  ++si;
  EXPECT_EQ(*si, 9);
}

//put the rest of your test cases here!

TEST_F (SetTest, SameTestCase_Union) {
  Set<int> a;
  a.add(1);
  a.add(2);
  a.add(3);
  a.add(4);
  a.add(5);
  Set<int> b;
  b.add(1);
  b.add(2);
  b.add(3);
  b.add(4);
  b.add(5);
  b.setUnion(a);
  Set<int> c = b.setUnion(a);
  Set<int>::Iterator si = c.begin();
  for(unsigned int i = 0; i < 5; i++) {
    EXPECT_EQ(*si, i+1);
    ++si;
  }
}

TEST_F (SetTest, NoOverlapCase_Union)
{
  Set<int> a;
  a.add(1);
  a.add(3);
  a.add(5);
  a.add(7);
  a.add(9);
  Set<int> b;
  b.add(2);
  b.add(4);
  b.add(6);
  b.add(8);
  b.add(10);
  Set<int> c = b.setUnion(a);
  Set<int>::Iterator si = c.begin();
  for (int i = 0; i < 10; i ++)
  {
    EXPECT_EQ(*si, i+1);
    ++si;
  }
}

TEST_F (SetTest, BasicCase_Intersect) {
  Set<int> a;
  a.add(1);
  a.add(2);
  a.add(3);
  a.add(4);
  a.add(5);
  Set<int> b;
  b.add(1);
  b.add(3);
  b.add(5);
  b.add(7);
  b.add(9);
  Set<int> c = b.setIntersection(a);
  Set<int>::Iterator si = c.begin();
  EXPECT_EQ(*si, 1);
  ++si;
  EXPECT_EQ(*si, 3);
  ++si;
  EXPECT_EQ(*si, 5);
  ++si;
}

//put the rest of your test cases here!

TEST_F (SetTest, SameTestCase_Intersect) {
  Set<int> a;
  a.add(1);
  a.add(2);
  a.add(3);
  a.add(4);
  a.add(5);
  Set<int> b;
  b.add(1);
  b.add(2);
  b.add(3);
  b.add(4);
  b.add(5);
  b.setUnion(a);
  Set<int> c = b.setIntersection(a);
  Set<int>::Iterator si = c.begin();
  for(unsigned int i = 0; i < 5; i++) {
    EXPECT_EQ(*si, i+1);
    ++si;
  }
}

TEST_F (SetTest, NoOverlapCase_Intersect)
{
  Set<int> a;
  a.add(1);
  a.add(3);
  a.add(5);
  a.add(7);
  a.add(9);
  Set<int> b;
  b.add(2);
  b.add(4);
  b.add(6);
  b.add(8);
  b.add(10);
  Set<int> c = b.setIntersection(a);
  EXPECT_EQ( c.size(), 0);
}