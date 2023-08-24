#include "Log.h"
#include <mqtt/async_client.h>
#include "HasBasicMessageOperator.h"
#include "BasicMessageTrait.h"
#include "Log.h"
#include <stdexcept>
#include <mutex>
#include "thread"

#ifndef RECEIVER_INCLUDE_H
#define RECEIVER_INCLUDE_H

template<typename MessageType>
class Receiver {

};

#endif