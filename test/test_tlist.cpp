#include "tlist.h"
#include <gtest.h>
#include <queue>

TEST(TDynamicList, can_create)
{
	ASSERT_NO_THROW(TDynamicList<int> list);
}

TEST(TDynamicList, can_check_empty)
{
	TDynamicList<int> list;
	EXPECT_EQ(list.empty(), true);
}

TEST(TDynamicList, can_create_copy)
{
	TDynamicList<int> list;
	ASSERT_NO_THROW(TDynamicList<int> list2(list));
}

TEST(TDynamicList, can_push_front)
{
	TDynamicList<int> list;
	ASSERT_NO_THROW(list.push_front(5));
}

TEST(TDynamicList, can_push_back)
{
	TDynamicList<int> list;
	ASSERT_NO_THROW(list.push_back(5));
}

TEST(TDynamicList, can_insert_after_first)
{
	TDynamicList<int> list;
	list.push_back(5);
	ASSERT_NO_THROW(list.insert_after(list.front(), 78));
}

TEST(TDynamicList, can_erase_after_first)
{
	TDynamicList<int> list;
	list.push_back(5);
	list.push_back(15);
	ASSERT_NO_THROW(list.erase_after(list.front()));
}