#include "BasicMessage.h"
#include "HasBasicMessageOperator.h"
#include "iostream"
#include <cassert>

int main(int argc, char** argv) {
    BasicMessage* basicMessage = new BasicMessage('<', '>', 12);
    bool has_operator = has_cast_operator<BasicMessage>::value;
    assert(has_operator == true);
    return 0;
}