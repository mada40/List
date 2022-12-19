#include "tlist.h"
#include <gtest.h>
#include <queue>

TEST(TDynamicList, can_create)
{
	ASSERT_NO_THROW(TDynamicList<int> list);
}

TEST(TDynamicList, can_assign)
{
	TDynamicList<int> list;
	list.push_front(58);
	list.push_front(85);
	TDynamicList<int> tmp;
	ASSERT_NO_THROW(tmp = list);
}

TEST(TDynamicList, can_assign_himself)
{
	TDynamicList<int> list;
	list.push_front(58);
	list.push_front(85);
	ASSERT_NO_THROW(list = list);
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
	ASSERT_NO_THROW(list.insert_after(list.begin(), 78));
}

TEST(TDynamicList, can_return_front)
{
	TDynamicList<int> list;
	list.push_back(5);
	list.push_back(7);
	EXPECT_EQ(*list.begin(), 5);
}

TEST(TDynamicList, can_return_back)
{
	TDynamicList<int> list;
	list.push_back(5);
	list.push_back(7);
	EXPECT_EQ(*list.back(), 7);
}


TEST(TDynamicList, can_erase_after_first)
{
	TDynamicList<int> list;
	list.push_back(5);
	list.push_back(15);
	ASSERT_NO_THROW(list.erase_after(list.begin()));
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

	for (auto el : list)
	{
		EXPECT_EQ(el, control.front());
		control.pop();
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

	for (auto el : list)
	{
		EXPECT_EQ(el, control.front());
		control.pop();
	}

}

TEST(TDynamicList, can_pop_front)
{
	TDynamicList<int> list;
	list.push_back(5);
	ASSERT_NO_THROW(list.pop_front());
}

class FixtureForCreateLoop : public ::testing::Test
{
	public:
		TDynamicList<int> list;
		TDynamicList<int>::iterator begin_loop;
		TDynamicList<int>::iterator next_after_begin_loop;
		FixtureForCreateLoop()
		{
			const int N = 100;
			for (int i = 0; i < N; i++)
			{
				list.push_back(i * i - 2287);
				if (i == 78)
					begin_loop = list.back();
				if (i == 79)
					next_after_begin_loop = list.back();
			}

			begin_loop.node->next = list.begin().node;
		}

		bool haveLoop()
		{
			auto ptr1 = list.begin();
			auto ptr2 = list.begin();
			auto end = list.end();
			++ptr2; ++ptr2;
			while (ptr1 != end && ptr2 != end && ptr1 != ptr2)
			{
				++ptr1;
				++ptr2; ++ptr2;
			}
			return ptr1 == ptr2;
		}

		void TearDown() override {
			begin_loop.node->next = next_after_begin_loop.node;
		}
};

TEST_F(FixtureForCreateLoop, search_loop1)
{
	EXPECT_EQ(haveLoop(), true);
}

TEST_F(FixtureForCreateLoop, search_loop2)
{
	begin_loop.node->next = next_after_begin_loop.node;
	EXPECT_EQ(haveLoop(), false);
}
