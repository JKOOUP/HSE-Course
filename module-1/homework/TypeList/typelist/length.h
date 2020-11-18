#pragma once
#include "typelist.h"

template<typename Tlist> 
struct Length {
private:
    typedef typename Tlist::tail tail;

public:
    const static std::size_t length = 1 + Length<tail>::length;
};

template<>
struct Length<NullType> {
public:
    const static std::size_t length = 0;
};