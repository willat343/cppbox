#ifndef CPPBOX_IMPL_TRACKING_HPP
#define CPPBOX_IMPL_TRACKING_HPP

#include <algorithm>

#include "cppbox/exceptions.hpp"
#include "cppbox/time.hpp"
#include "cppbox/tracking.hpp"

namespace cppbox {

template<typename Element_, IsTimePoint Time_>
inline Tracking<Element_, Time_>::Tracking(const Time update_time, const Element& element) {
    update(update_time, element);
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::at(const Time time) const -> const Element& {
    return tracking.element(get_index(time));
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::at(const Time time, Time& update_time) const -> const Element& {
    const int index = get_index(time);
    update_time = tracking.time(index);
    return tracking.element(index);
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::at_time(const Time time) const -> Time {
    return tracking.time(get_index(time));
}

template<typename Element_, IsTimePoint Time_>
inline bool Tracking<Element_, Time_>::has_tracking_at(const Time time) const {
    return !tracking.empty() && tracking.start_time() <= time;
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::last() const -> const Element& {
    throw_if(tracking.empty(), "No tracking available.");
    return tracking.element_back();
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::last_time() const -> Time {
    throw_if(tracking.empty(), "No tracking available.");
    return tracking.end_time();
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::equal_since_time() const -> Time {
    throw_if(tracking.empty(), "No tracking available.");
    for (std::size_t i = tracking.size() - 1; i > 0; --i) {
        if (tracking.element(i - 1) != tracking.element_back()) {
            return tracking.time(i);
        }
    }
    return tracking.time(0);
}

template<typename Element_, IsTimePoint Time_>
inline void Tracking<Element_, Time_>::update(const Time update_time, const Element& element) {
    if (tracking.empty()) {
        tracking.emplace_back(update_time, element);
    } else if (update_time < tracking.end_time()) {
        throw_here("Tracking update time (" + cppbox::to_string(update_time) + ") precedes last update time (" +
                   cppbox::to_string(tracking.end_time()) + ").");
    } else if (tracking.element_back() == element &&
               (tracking.size() >= 2 && tracking.element(tracking.size() - 2) == element)) {
        // Update end time when tracking does not change for last two elements
        tracking.change_end_time(update_time);
    } else {
        // Add new tracking element
        tracking.emplace_back(update_time, element);
    }
}

template<typename Element_, IsTimePoint Time_>
inline int Tracking<Element_, Time_>::get_index(const Time time) const {
    const int index = tracking.time_keeper().find_index(time);
    throw_if(index < 0, "No tracking before query time " + cppbox::to_string(time) + ".");
    return index;
}

template<typename Element_, IsTimePoint Time_>
inline MultiTracking<Element_, Time_>::MultiTracking() : is_synchronised_(true) {}

template<typename Element_, IsTimePoint Time_>
inline bool MultiTracking<Element_, Time_>::has_tracking(const std::string& key) const {
    return trackings().contains(key);
}

template<typename Element_, IsTimePoint Time_>
inline bool MultiTracking<Element_, Time_>::is_synchronised() const {
    return is_synchronised_;
}

template<typename Element_, IsTimePoint Time_>
inline bool MultiTracking<Element_, Time_>::is_synchronised_to(const Time time) const {
    return is_synchronised() && !trackings().empty() && trackings().cbegin()->second.last_time() == time;
}

template<typename Element_, IsTimePoint Time_>
inline auto MultiTracking<Element_, Time_>::synchronisation_time() const -> Time {
    throw_if(!is_synchronised() || trackings().empty(), "Synchronisation time does not exist.");
    return trackings().cbegin()->second.last_time();
}

template<typename Element_, IsTimePoint Time_>
inline auto MultiTracking<Element_, Time_>::trackings() const
        -> const std::unordered_map<std::string, Tracking<Element, Time>>& {
    return trackings_;
}

template<typename Element_, IsTimePoint Time_>
inline auto MultiTracking<Element_, Time_>::tracking(const std::string& key) const -> const Tracking<Element, Time>& {
    return trackings().at(key);
}

template<typename Element_, IsTimePoint Time_>
void MultiTracking<Element_, Time_>::update(const Time update_time,
        const std::unordered_map<std::string, Element>& elements) {
    for (const auto& [key, element] : elements) {
        create_or_update(update_time, key, element);
    }
    is_synchronised_ = trackings().size() == elements.size() || check_if_synchronised_to(update_time);
}

template<typename Element_, IsTimePoint Time_>
void MultiTracking<Element_, Time_>::update(const Time update_time, const std::string& key, const Element& element) {
    create_or_update(update_time, key, element);
    is_synchronised_ = trackings().size() == 1 || check_if_synchronised_to(update_time);
}

template<typename Element_, IsTimePoint Time_>
void MultiTracking<Element_, Time_>::create_or_update(const Time update_time, const std::string& key,
        const Element& element) {
    auto tracking_it = trackings_.find(key);
    if (tracking_it == trackings_.end()) {
        trackings_.try_emplace(key, update_time, element);
    } else {
        tracking_it->second.update(update_time, element);
    }
}

template<typename Element_, IsTimePoint Time_>
bool MultiTracking<Element_, Time_>::check_if_synchronised_to(const Time time) const {
    return std::all_of(trackings().cbegin(), trackings().cend(),
            [time](const auto& key_tracking) { return key_tracking.second.last_time() == time; });
}

}

#endif
