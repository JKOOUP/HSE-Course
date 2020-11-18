#pragma once

#include "typelist.h"

template<typename TList, typename OldType, typename NewType> 
struct Replace {
private:
    typedef typename TList::head head;
    typedef typename TList::tail tail;

public:
    typedef TypeList<head, typename Replace<tail, OldType, NewType>::NewTypeList> NewTypeList;
};

template<typename TList, typename NewType>
struct Replace<TList, typename TList::head, NewType> {
private:
    typedef typename TList::head head;
    typedef typename TList::tail tail;

public:
    typedef TypeList<NewType, typename Replace<tail, head, NewType>::NewTypeList> NewTypeList;
};

template<typename OldType, typename NewType>
struct Replace<NullType, OldType, NewType> {
public:
    typedef NullType NewTypeList;
};