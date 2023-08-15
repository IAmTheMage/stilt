#include "BasicMessage.h"


#ifndef MESSAGE_TRAIT_H
#define MESSAGE_TRAIT_H
template<typename T>
struct InheritsFromBasicMessage {
private:
    typedef char YesType[1];
    typedef char NoType[2];

    template<typename C>
    static YesType& test(BasicMessage*);
    
    template<typename C>
    static NoType& test(...);

public:
    static constexpr bool value = sizeof(test<T>(nullptr)) == sizeof(YesType);
};

#endif