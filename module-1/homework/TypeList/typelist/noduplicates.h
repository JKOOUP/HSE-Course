#pragma once

#include "erase.h"
#include "typelist.h"

template<typename T1, typename T2>
struct is_equal {
public:
    const static bool val = false;
};

template<typename T>
struct is_equal<T, T> {
public:
    const static bool val = true;
};

template<typename TList, typename T>
struct EraseDuplicates {
private:
    typedef typename TList::head head;
    typedef typename TList::tail tail;

public:
    typedef TypeList<head, typename EraseDuplicates<tail, head>::NewTypeList> NewTypeList;
};

template<typename TList>
struct EraseDuplicates<TList, typename TList::head> {
private:
    typedef typename TList::head head;
    typedef typename TList::tail tail;

public:
    typedef typename EraseDuplicates<tail, head>::NewTypeList NewTypeList;
};

template<typename T>
struct EraseDuplicates<NullType, T> {
public:
    typedef NullType NewTypeList;
};

template<typename TList>
struct NoDuplicates {
private:
    typedef typename TList::head head;
    typedef typename TList::tail tail;

public:
    typedef TypeList<head, typename EraseDuplicates<tail, head>::NewTypeList> NewTypeList;
};