#ifndef __SHAREDPTR_H__
#define __SHAREDPTR_H__

#include <cstdio>
#include <iostream>

struct Person
{
    void speak() {std::cout<<"person speak"<<std::endl;}
};

struct Student:public Person
{
    char student;
};

template <typename T>
class SmartPtr
{
public:
    explicit SmartPtr(T* ptr = NULL) : m_ptr(ptr) {}
    SmartPtr(const SmartPtr<T>& other) {m_ptr=other.m_ptr;}
	~SmartPtr() {delete m_ptr;}

    T* operator->() {return m_ptr;}
    T& operator*() {return *m_ptr;}

private:
    T* m_ptr;
};

template <typename T>
class UniquePtr : public SmartPtr<T>
{
public:
    UniquePtr(T* ptr = NULL) : SmartPtr<T>(ptr) {}

private:
    UniquePtr(const UniquePtr& other) {}
    UniquePtr& operator=(const UniquePtr& other) {return *this; }
};

template <typename  T>
class SharedPtr
{
public:
    explicit SharedPtr(T* ptr);
    SharedPtr(const SharedPtr<T>&);
    SharedPtr& operator=(const SharedPtr<T>& other);
    template <typename U>
    SharedPtr& operator=(const SharedPtr<U>& other);
    ~SharedPtr();

    T* operator->() {return m_ptr;}
    T& operator*() {return *m_ptr;}
    operator bool() const;

    T* getPointer() const;
    size_t* getCount() const;

private:
    T* m_ptr;
    size_t* m_count;

    void Dec_count();
    void Iec_count();
    bool BiggerOfOne();
    void FreeIfLastPointer();
};

template <typename T, typename U> bool operator==(const SharedPtr<T>& first_ptr, const SharedPtr<U>& second_ptr);
template<typename T> bool operator==(const SharedPtr<T>& first_ptr, const SharedPtr<T>& second_ptr);
template<typename T> bool operator!=(const SharedPtr<T>& first_ptr, const SharedPtr<T>& second_ptr);

template <typename  T>
inline SharedPtr<T>::operator bool() const
{
    return m_ptr!=NULL;
}


template <typename  T>
inline void SharedPtr<T>::FreeIfLastPointer()
{
    if (BiggerOfOne())
    {
        Dec_count();
    }
    else
    {
        delete m_count;
        delete m_ptr;
    }
}

template <typename  T>
inline void SharedPtr<T>::Dec_count()
{
    (*m_count)--;
}

template <typename  T>
inline void SharedPtr<T>::Iec_count()
{
    (*m_count)++;
}

template <typename  T>
inline bool SharedPtr<T>::BiggerOfOne()
{
    return *m_count > 1;
}

template <typename  T>
inline T* SharedPtr<T>::getPointer() const
{
    return m_ptr;
}

template <typename  T>
inline size_t* SharedPtr<T>::getCount() const
{
    return m_count;
}

template <typename  T>
inline SharedPtr<T>::~SharedPtr() {

    FreeIfLastPointer();
}

template<typename T>
inline SharedPtr<T>::SharedPtr(T *ptr) : m_ptr(ptr), m_count(new size_t(1)) {}

template<typename T>
inline SharedPtr<T>::SharedPtr(const SharedPtr<T> & other) {
    m_ptr = other.m_ptr;
    m_count = other.m_count;
    Iec_count();
}

template<typename T>
inline SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
    if(m_ptr != other.m_ptr)
    {
        FreeIfLastPointer();

        Iec_count();
        m_count = other.m_count;
        m_ptr=other.m_ptr;
    }
    return *this;
}

template<typename T>
template<typename U>
inline SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<U>& other) {
	if(*this != other)
	{
        FreeIfLastPointer();
        Iec_count();
        m_count = other.getCount();
        m_ptr = other.getPointer();
	}
    return *this;
}

template <typename T, typename U>
inline bool operator==(const SharedPtr<T>& first_ptr, const SharedPtr<U>& second_ptr) {
    return first_ptr.getPointer() == (T*)second_ptr.getPointer();
}

template<typename T>
inline bool operator==(const SharedPtr<T>& first_ptr, const SharedPtr<T>& second_ptr)
{
    return first_ptr.getPointer() == second_ptr.getPointer();
}

template<typename T>
inline bool operator!=(const SharedPtr<T>& first_ptr, const SharedPtr<T>& second_ptr)
{
    return first_ptr.getPointer() != second_ptr.getPointer();
}


#endif //__SHAREDPTR_H__
