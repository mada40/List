#include "tlist.h"
#include <gtest.h>
#include <queue>

TEST(TDynamicList, can_create)
{
	ASSERT_NO_THROW(List<int> list);
}

TEST(TDynamicList, can_assign)
{
	List<int> list;
	list.push_front(58);
	list.push_front(85);
	List<int> tmp;
	ASSERT_NO_THROW(tmp = list);
}

TEST(TDynamicList, can_assign_himself)
{
	List<int> list;
	list.push_front(58);
	list.push_front(85);
	ASSERT_NO_THROW(list = list);
}


TEST(TDynamicList, can_check_empty)
{
	List<int> list;
	EXPECT_EQ(list.empty(), true);
}

TEST(TDynamicList, can_create_copy)
{
	List<int> list;
	ASSERT_NO_THROW(List<int> list2(list));
}

TEST(TDynamicList, can_push_front)
{
	List<int> list;
	ASSERT_NO_THROW(list.push_front(5));
}

TEST(TDynamicList, can_push_back)
{
	List<int> list;
	ASSERT_NO_THROW(list.push_back(5));
}

TEST(TDynamicList, can_insert_after_first)
{
	List<int> list;
	list.push_back(5);
	ASSERT_NO_THROW(list.insert_after(list.begin(), 78));
}

TEST(TDynamicList, can_return_front)
{
	List<int> list;
	list.push_back(5);
	list.push_back(7);
	EXPECT_EQ(list.front(), 5);
}

TEST(TDynamicList, can_return_back)
{
	List<int> list;
	list.push_back(5);
	list.push_back(7);
	EXPECT_EQ(list.back(), 7);
}


TEST(TDynamicList, can_erase_after_first)
{
	List<int> list;
	list.push_back(5);
	list.push_back(15);
	ASSERT_NO_THROW(list.erase_after(list.begin()));
}

TEST(TDynamicList, can_resize1)
{
	List<int> list;
	list.push_back(5);
	list.push_back(15);
	auto b = list.begin();
	ASSERT_NO_THROW(list.resize(5));
}

TEST(TDynamicList, can_resize2)
{
	List<int> list;
	list.push_back(5);
	list.push_back(15);
	list.push_back(15);
	list.push_back(115);
	list.push_back(25);
	list.push_back(215);
	ASSERT_NO_THROW(list.resize(3));
}

TEST(TDynamicList, can_remove)
{
	List<int> list;
	list.push_back(5);
	list.push_back(15);
	list.push_back(15);
	list.push_back(5);
	list.push_back(25);
	list.push_back(5);
	ASSERT_NO_THROW(list.remove(5));
}

TEST(TDynamicList, can_reverse)
{
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	list.reverse();
	int cnt = 5;

	for (auto x : list)
	{
		EXPECT_EQ(x, cnt);
		cnt--;
	}
}

TEST(TDynamicList, can_move)
{
	List<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	list.reverse();
	EXPECT_NO_THROW(auto tmp = std::move(list));
}


TEST(TDynamicList, can_erase_after_node)
{
	List<int> list;
	list.push_back(5);
	list.push_back(15);
	auto tmp = list.begin();
	list.push_front(35);
	list.push_front(85);
	ASSERT_NO_THROW(list.erase_after(tmp));
}

TEST(TDynamicList, can_insert_after_node)
{
	List<int> list;
	list.push_back(5);
	list.push_back(15);
	auto tmp = list.begin();
	list.push_front(35);
	list.push_front(85);
	ASSERT_NO_THROW(list.insert_after(tmp, 666));
}

TEST(TDynamicList, erase_after_node_deletes_node)
{
	List<int> list;
	list.push_back(5);//5
	list.push_back(15);//5 15
	list.push_back(25);//5 15 25
	auto tmp = list.begin();
	list.push_front(35);// 35 5 15 25
	list.push_front(85);//85 35 5 15 25
	list.erase_after(tmp);//delete 15 : 85 35 5 25

	std::queue<int> control;
	control.push(85);
	control.push(35);
	control.push(5);
	control.push(25);

	for (auto el : list)
	{
		int y = control.front();
		EXPECT_EQ(el, y);
		control.pop();
	}

}


TEST(TDynamicList, insert_after_node_adds_node)
{
	List<int> list;
	list.push_back(5);//5
	list.push_back(15);//5 15
	list.push_back(25);//5 15 25
	auto tmp = list.begin();
	list.push_front(35);// 35 5 15 25
	list.push_front(85);//85 35 5 15 25
	list.insert_after(tmp, 666); // 85 35 5 666 15 25

	std::queue<int> control;
	control.push(85);
	control.push(35);
	control.push(5);
	control.push(666);
	control.push(15);
	control.push(25);

	for (auto el : list)
	{
		EXPECT_EQ(el, control.front());
		control.pop();
	}

}

TEST(TDynamicList, can_pop_front)
{
	List<int> list;
	list.push_back(5);
	ASSERT_NO_THROW(list.pop_front());
}

