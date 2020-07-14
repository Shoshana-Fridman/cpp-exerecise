//
// Created by Shoshi on 07/07/2020.
//
#include "SharedPtr.h"

#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Ptr, SharedPtr)
{
    SharedPtr<Person> sp1(new Person);
    SharedPtr<Person> sp2(sp1);
	(sp1 == sp2) ? std::cout<<"equal"<<std::endl : std::cout<<"not equal"<<std::endl;
	(sp1 != sp2) ? std::cout<<"not equal"<<std::endl : std::cout<<"equal"<<std::endl;
    sp1 ? std::cout<<"legal pointer"<<std::endl : std::cout<<"NULL"<<std::endl;
    SharedPtr<Person> sp3(NULL);
    sp3 ? std::cout<<"legal pointer"<<std::endl : std::cout<<"NULL"<<std::endl;
    SharedPtr<Student> sp4(new Student);
    (sp3 == sp4) ? std::cout<<"equal"<<std::endl : std::cout<<"not equal"<<std::endl;
    sp3 = sp4;
    (sp3 == sp4) ? std::cout<<"equal!!!!!!"<<std::endl : std::cout<<"not equal!!!!!"<<std::endl;
    sp1->speak();
    sp2->speak();
}

TEST(Ptr, UniquePtr)
{
    UniquePtr<Person> sp(new Person);
	sp->speak();
//don't work because the pointer is unique 
//    UniquePtr<Person> sp2(sp);
}

TEST(Ptr, SmartPtr)
{
    SmartPtr<Person> sp1(new Person);
	SmartPtr<Person> sp2(sp1);
	sp2->speak();
}


