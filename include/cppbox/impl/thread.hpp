#ifndef CPPBOX_IMPL_THREAD_HPP
#define CPPBOX_IMPL_THREAD_HPP

#include <thread>

#include "cppbox/thread.hpp"

namespace cppbox {

template<IsDuration Duration>
void wait_for_trigger(const std::atomic_bool& trigger, const Duration wait_period) {
    while (!trigger) {
        std::this_thread::sleep_for(wait_period);
    }
}

template<IsDuration Duration>
void wait_for_trigger(const std::function<bool()>& trigger, const Duration wait_period) {
    while (!trigger()) {
        std::this_thread::sleep_for(wait_period);
    }
}

}

#endif
