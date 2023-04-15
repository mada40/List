#include "tlist.h"
#include <gtest.h>
#include <forward_list>

class Fixture : public ::testing::Test
{
public:
	List<int> list;
	List<int>::iterator center;

	std::forward_list<int> control;

	std::forward_list<int>::iterator center_control;
	const int REMOVE_EL = 5;

	Fixture() :list(List<int>()), control(std::forward_list<int>())
	{
		list.push_back(5);
		list.push_back(15);
		list.push_back(25);
		list.push_back(5);

		center = list.begin();

		list.push_front(35);
		list.push_front(85);
		list.push_front(5);

		control.push_front(5);
		control.push_front(15);
		control.push_front(25);
		control.push_front(5);

		control.reverse();
		center_control = control.begin();

		control.push_front(35);
		control.push_front(85);
		control.push_front(5);
	}

	bool compare_with_control(List<int> lt)
	{
		while (!control.empty() && !lt.empty())
		{
			int x = lt.front(); lt.pop_front();
			int y = control.front(); control.pop_front();
			if (x != y)
				return false;
		}

		return control.empty() && lt.empty();
	}
};


TEST(TDynamicList, can_create)
{
	ASSERT_NO_THROW(List<int> list);
}

TEST_F(Fixture, can_clear)
{
	ASSERT_NO_THROW(list.clear());
}


TEST_F(Fixture, can_assign)
{
	List<int> tmp;
	ASSERT_NO_THROW(tmp = list);
}

TEST_F(Fixture, size_of_assigned_list_equl_size_of_init_list)
{
	List<int> tmp;
	tmp = list;
	EXPECT_EQ(list.size(), tmp.size());
	
}

TEST_F(Fixture, can_assign_himself)
{
	List<int> list;
	ASSERT_NO_THROW(list = list);
}

TEST(TDynamicList, can_check_empty)
{
	List<int> list;
	EXPECT_EQ(list.empty(), true);
}

TEST_F(Fixture, can_create_copy)
{
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

TEST_F(Fixture, can_resize1)
{
	ASSERT_NO_THROW(list.resize(50));
}

TEST_F(Fixture, can_resize2)
{
	ASSERT_NO_THROW(list.resize(1));
}

TEST_F(Fixture, can_remove)
{
	ASSERT_NO_THROW(list.remove(REMOVE_EL));
}

TEST_F(Fixture, correct_remove)
{
	list.remove(REMOVE_EL);
	control.remove(REMOVE_EL);
	EXPECT_TRUE(compare_with_control(list));
}

TEST_F(Fixture, correct_reverse)
{
	list.reverse();
	control.reverse();
	EXPECT_TRUE(compare_with_control(list));
}

TEST_F(Fixture, move_constructor_no_throw)
{
	EXPECT_NO_THROW(auto tmp = std::move(list));
}

TEST_F(Fixture, move_assigment_no_throw)
{
	List<int> tmp;
	tmp.push_back(5);
	EXPECT_NO_THROW(tmp = std::move(list));
}

TEST_F(Fixture, correct_move_constructor)
{
	EXPECT_NO_THROW(compare_with_control(std::move(list)));
}

TEST_F(Fixture, correct_move_assigmaent)
{
	List<int> tmp;
	tmp = std::move(list);
	EXPECT_NO_THROW(compare_with_control(tmp));
}


TEST_F(Fixture, can_erase_after)
{
	ASSERT_NO_THROW(list.erase_after(center));
}

TEST_F(Fixture, can_insert_after)
{
	ASSERT_NO_THROW(list.insert_after(center, 666));
}

TEST_F(Fixture, correct_erase_after)
{
	list.erase_after(center);
	control.erase_after(center_control);
	EXPECT_TRUE(compare_with_control(list));

}

TEST_F(Fixture, correct_insert_after)
{

	list.insert_after(center, 666);
	control.insert_after(center_control, 666);
	EXPECT_TRUE(compare_with_control(list));
}

TEST(TDynamicList, can_pop_front)
{
	List<int> list;
	list.push_back(5);
	ASSERT_NO_THROW(list.pop_front());
}

