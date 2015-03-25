#include "Mergesort.h"
#include "gtest/gtest.h"
#include <vector>
#include <iostream>

using namespace std;

// The fixture for testing class.
class MergeTest: public ::testing::Test
{
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	MergeTest()
	{
		// You can do set-up work for each test here.
	}

	virtual ~MergeTest()
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

TEST_F (MergeTest, BasicCase) {
  vector<int> v;
  v.push_back(1);
  v.push_back(5);
  v.push_back(3);
  v.push_back(2);
  v.push_back(4);
  vector<int> v_sorted = MergeSort::sort(v);
  for(unsigned int i = 0; i < v.size(); i++) {
    EXPECT_EQ(v_sorted.at(i), i + 1);
  }
}

TEST_F (MergeTest, CheckDuplicatedLeftRight) {
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  vector<int> v_sorted = MergeSort::sort(v);
  for(unsigned int i = 0; i < 2; i++) {
  	EXPECT_EQ(v_sorted.at(i), 1);
  }
  for(unsigned int i = 2; i < 4; i++) {
  	EXPECT_EQ(v_sorted.at(i), 2);
  }
  for(unsigned int i = 4; i < 6; i++) {
  	EXPECT_EQ(v_sorted.at(i), 3);
  }
  for(unsigned int i = 6; i < 8; i++) {
  	EXPECT_EQ(v_sorted.at(i), 4);
  }
}

TEST_F (MergeTest, CheckEmptyList) {
  vector<int> v;
  vector<int> v_sorted = MergeSort::sort(v);
  EXPECT_EQ(v_sorted.size(), 0);
}

TEST_F (MergeTest, CheckReverseList) {
  vector<int> v;
  v.push_back(5);
  v.push_back(4);
  v.push_back(3);
  v.push_back(2);
  v.push_back(1);
  vector<int> v_sorted = MergeSort::sort(v);
  for(unsigned int i = 0; i < v.size(); i++) {
    EXPECT_EQ(v_sorted.at(i), i + 1);
  }
}

TEST_F (MergeTest, CheckSameElement) {
  vector<int> v;
  v.push_back(1);
  v.push_back(1);
  v.push_back(1);
  v.push_back(1);
  v.push_back(1);
  vector<int> v_sorted = MergeSort::sort(v);
  for(unsigned int i = 0; i < v.size(); i++) {
    EXPECT_EQ(v_sorted.at(i), 1);
  }
}

//put the rest of your test cases here!


