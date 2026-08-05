#include "cppbox/thread.hpp"

#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <thread>

TEST(thread, wait_for_trigger_atomic_bool) {
    std::atomic_bool trigger{false};
    std::thread setter([&trigger]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        trigger = true;
    });
    cppbox::wait_for_trigger(trigger, std::chrono::milliseconds(1));
    EXPECT_TRUE(trigger.load());
    setter.join();
}

TEST(thread, wait_for_trigger_function) {
    std::atomic_bool ready{false};
    std::thread setter([&ready]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        ready = true;
    });
    const std::function<bool()> predicate = [&ready]() { return ready.load(); };
    cppbox::wait_for_trigger(predicate, std::chrono::milliseconds(1));
    EXPECT_TRUE(ready.load());
    setter.join();
}
