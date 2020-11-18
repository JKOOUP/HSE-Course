#pragma once
#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf {
private:
    typedef typename TList::tail tail;
    const static int tmp_pos = IndexOf<tail, TargetType>::pos; 

public:
    const static int pos = (tmp_pos == -1) ? -1 : tmp_pos + 1; 
};

template<typename TList>
struct IndexOf <TList, typename TList::head> { 
public:
    const static int pos = 0;
};

template<typename TargetType>
struct IndexOf<NullType, TargetType> {
public:
    const static int pos = -1;
};