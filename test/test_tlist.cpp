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

TEST(TDynamicList, can_return_front)
{
	TDynamicList<int> list;
	list.push_back(5);
	list.push_back(7);
	EXPECT_EQ(list.front()->value, 5);
}

TEST(TDynamicList, can_return_back)
{
	TDynamicList<int> list;
	list.push_back(5);
	list.push_back(7);
	EXPECT_EQ(list.back()->value, 7);
}


TEST(TDynamicList, can_erase_after_first)
{
	TDynamicList<int> list;
	list.push_back(5);
	list.push_back(15);
	ASSERT_NO_THROW(list.erase_after(list.front()));
}

TEST(TDynamicList, can_erase_after_node)
{
	TDynamicList<int> list;
	list.push_back(5);
	list.push_back(15);
	auto tmp = list.back();
	list.push_back(35);
	list.push_back(85);
	ASSERT_NO_THROW(list.erase_after(tmp));
}

TEST(TDynamicList, can_insert_after_node)
{
	TDynamicList<int> list;
	list.push_back(5);
	list.push_back(15);
	auto tmp = list.back();
	list.push_back(35);
	list.push_back(85);
	ASSERT_NO_THROW(list.insert_after(tmp, 666));
}

TEST(TDynamicList, erase_after_node_deletes_node)
{
	TDynamicList<int> list;
	list.push_back(5);
	list.push_back(15);
	auto tmp = list.back();
	list.push_back(35);
	list.push_back(85);
	list.erase_after(tmp);

	std::queue<int> control;
	control.push(5);
	control.push(15);
	control.push(85);

	auto first = list.front();
	while (first)
	{
		EXPECT_EQ(first->value, control.front());
		control.pop();
		first = first->next;
	}
}


TEST(TDynamicList, insert_after_node_adds_node)
{
	TDynamicList<int> list;
	list.push_back(5);
	list.push_back(15);
	auto tmp = list.back();
	list.push_back(35);
	list.push_back(85);
	list.insert_after(tmp, 666);

	std::queue<int> control;
	control.push(5);
	control.push(15);
	control.push(666);
	control.push(35);
	control.push(85);

	auto first = list.front();
	while (first)
	{
		EXPECT_EQ(first->value, control.front());
		control.pop();
		first = first->next;
	}
}

TEST(TDynamicList, can_pop_front)
{
	TDynamicList<int> list;
	list.push_back(5);
	ASSERT_NO_THROW(list.pop_front());
}