#ifndef __MEMORTEXCPLICIT_H__
#define __MEMORTEXCPLICIT_H__

#include <iostream>
#include <cstring>//for strcpy in constructor of person

class FatherOfPerson{
public:
    FatherOfPerson();

private:
    FatherOfPerson(FatherOfPerson&);
    FatherOfPerson operator=(FatherOfPerson&);

    void* operator new[] (std::size_t size);
    void operator delete[] (void* ptr);
};

class Person:private FatherOfPerson
{
public:
	Person();
    Person(const char* fullname, unsigned int id, unsigned char age);

    void* operator new (std::size_t size);//The function throw bad alloc
    void* operator new (std::size_t size, const std::nothrow_t& nothrow_value);//if don't have a place the function return NULL
    void operator delete (void* ptr);
    char * getFullName();

private:
    char m_fullname[32];
    unsigned int m_id;
    unsigned char m_age;
    static void* const s_pool;
    static void* s_firstFree;
};

inline FatherOfPerson::FatherOfPerson(){}

inline Person::Person(const char* fullname, unsigned int id, unsigned char age):FatherOfPerson(), m_id(id), m_age(age)
{
    strcpy(m_fullname, fullname);
}

/***************************HELP FUNCTION***************************/
inline char * Person::getFullName()
{
    return m_fullname;
}

inline size_t max()
{
    return (sizeof(Person)>= sizeof(Person *))? sizeof(Person): sizeof(Person *);
}
/*******************************************************************/
#endif
