#include <gtest/gtest.h>

#include "memoryExplicit.h"


int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(memoyExplicit, init)
{

    Person p1("Shoshana Fridman", 207775008, 20);
    ASSERT_EQ(strcmp(p1.getFullName(), "Shoshana Fridman"), 0);
}

TEST(PersonBasicTests, createPersonOnHeap)
{
    Person* p1 = (Person*) new Person("Shoshana Fridman", 207775008, 20);
    ASSERT_EQ(strcmp((*p1).getFullName(), "Shoshana Fridman"), 0);
    Person* p2 = new Person("Mor", 2, 30);
    ASSERT_EQ(strcmp((*p2).getFullName(),"Mor"), 0);
    ASSERT_EQ(strcmp((*p1).getFullName(), "Shoshana Fridman"), 0);
    delete p1;
    delete p2;
}

