#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct EraseAll {
private:
    typedef typename TList::head head;
    typedef typename TList::tail tail;
    
public:
    typedef TypeList<head, typename Erase<tail, TargetType>::NewTypeList> NewTypeList;
};

template<typename TList>
struct EraseAll<TList, typename TList::head> {
private:
    typedef typename TList::head head;
    typedef typename TList::tail tail;
    
public:
    typedef typename Erase<tail, head>::NewTypeList NewTypeList;
};

template<typename TargetType>
struct EraseAll <NullType, TargetType> {
public:
    typedef NullType NewTypeList;
};