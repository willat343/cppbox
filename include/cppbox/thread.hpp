#ifndef CPPBOX_THREAD_HPP
#define CPPBOX_THREAD_HPP

#include <atomic>
#include <functional>

#include "cppbox/time.hpp"

namespace cppbox {

template<IsDuration Duration>
void wait_for_trigger(const std::atomic_bool& trigger, const Duration wait_period);

template<IsDuration Duration>
void wait_for_trigger(const std::function<bool()>& trigger, const Duration wait_period);

}

#include "cppbox/impl/thread.hpp"

#endif
