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
inline bool Tracking<Element_, Time_>::empty() const {
    return tracking_.size() == 0;
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::at(const Time time) const -> const Element& {
    return tracking_.element(get_index(time));
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::at(const Time time, Time& update_time) const -> const Element& {
    const int index = get_index(time);
    update_time = tracking_.time(index);
    return tracking_.element(index);
}

template<typename Element_, IsTimePoint Time_>
auto Tracking<Element_, Time_>::at(const Time time, TimeInterval<Time>& update_times) const -> const Element& {
    const int index = get_index(time);
    const Element& element_ = tracking_.element(index);
    const Time update_time_ = tracking_.time(index);
    if (index > 0 && tracking_.element(index - 1) == element_) {
        update_times.start() = tracking_.time(index - 1);
    } else {
        update_times.start() = update_time_;
    }
    if (index + 1 < static_cast<int>(tracking_.size()) && tracking_.element(index + 1) == element_) {
        update_times.end() = tracking_.time(index + 1);
    } else {
        update_times.end() = update_time_;
    }
    return element_;
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::at_time(const Time time) const -> Time {
    return tracking_.time(get_index(time));
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::at_time_interval(const Time time) const -> TimeInterval<Time> {
    TimeInterval<Time> time_interval_;
    at(time, time_interval_);
    return time_interval_;
}

template<typename Element_, IsTimePoint Time_>
inline bool Tracking<Element_, Time_>::changed_last() const {
    return last_time() == equal_since_time();
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::equal_since_time() const -> Time {
    throw_if(tracking_.empty(), "No tracking available.");
    for (std::size_t i = tracking_.size() - 1; i > 0; --i) {
        if (tracking_.element(i - 1) != tracking_.element_back()) {
            return tracking_.time(i);
        }
    }
    return tracking_.time(0);
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::first() const -> const Element& {
    throw_if(tracking_.empty(), "No tracking available.");
    return tracking_.element(0);
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::first(Time& update_time) const -> const Element& {
    throw_if(tracking_.empty(), "No tracking available.");
    update_time = tracking_.time(0);
    return tracking_.element(0);
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::first_time() const -> Time {
    throw_if(tracking_.empty(), "No tracking available.");
    return tracking_.time(0);
}

template<typename Element_, IsTimePoint Time_>
inline bool Tracking<Element_, Time_>::has_tracking_at(const Time time) const {
    return !tracking_.empty() && tracking_.start_time() <= time;
}

template<typename Element_, IsTimePoint Time_>
inline bool Tracking<Element_, Time_>::is_updated_once() const {
    return tracking_.size() == 1;
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::last() const -> const Element& {
    throw_if(tracking_.empty(), "No tracking available.");
    return tracking_.element_back();
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::last_time() const -> Time {
    throw_if(tracking_.empty(), "No tracking available.");
    return tracking_.end_time();
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::last_or(const Element& default_value) const -> Element {
    return tracking_.empty() ? default_value : tracking_.element_back();
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::next(const Time time) const -> const Element& {
    return tracking_.element(get_index(time) + 1);
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::next(const Time time, Time& update_time) const -> const Element& {
    const int index = get_index(time) + 1;
    update_time = tracking_.time(index);
    return tracking_.element(index);
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::next_time(const Time time) const -> Time {
    return tracking_.time(get_index(time) + 1);
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::previous() const -> const Element& {
    throw_if(tracking_.size() <= 1, "Not enough tracking available.");
    return tracking_.element(tracking_.size() - 2);
}

template<typename Element_, IsTimePoint Time_>
inline auto Tracking<Element_, Time_>::previous_time() const -> Time {
    throw_if(tracking_.size() <= 1, "Not enough tracking available.");
    return tracking_.time(tracking_.size() - 2);
}

template<typename Element_, IsTimePoint Time_>
inline void Tracking<Element_, Time_>::update(const Time update_time, const Element& element) {
    if (tracking_.empty()) {
        tracking_.emplace_back(update_time, element);
    } else if (update_time < tracking_.end_time()) {
        throw_here("Tracking update time (" + cppbox::to_string(update_time) + ") precedes last update time (" +
                   cppbox::to_string(tracking_.end_time()) + ").");
    } else if (tracking_.size() >= 2 && tracking_.element(tracking_.size() - 1) == element &&
               tracking_.element(tracking_.size() - 2) == element) {
        // Update end time when tracking does not change for last two elements
        tracking_.change_end_time(update_time);
    } else {
        // Add new tracking element
        tracking_.emplace_back(update_time, element);
    }
}

template<typename Element_, IsTimePoint Time_>
inline int Tracking<Element_, Time_>::get_index(const Time time) const {
    const int index = tracking_.time_keeper().find_index(time);
    throw_if(index < 0, "No tracking before query time " + cppbox::to_string(time) + ".");
    return index;
}

template<typename Element_, IsTimePoint Time_>
inline MultiTracking<Element_, Time_>::MultiTracking() : is_synchronised_(true) {}

template<typename Element_, IsTimePoint Time_>
inline bool MultiTracking<Element_, Time_>::empty() const {
    return size() == 0;
}

template<typename Element_, IsTimePoint Time_>
inline std::size_t MultiTracking<Element_, Time_>::size() const {
    return trackings().size();
}

template<typename Element_, IsTimePoint Time_>
inline bool MultiTracking<Element_, Time_>::has_tracking(const std::string& key) const {
    return trackings().contains(key);
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
void MultiTracking<Element_, Time_>::update(const Time update_time, const Element& element) {
    for (auto& tracking_ : trackings_ | std::views::values) {
        tracking_.update(update_time, element);
    }
    is_synchronised_ = true;
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
auto MultiTracking<Element_, Time_>::last_synchronised() const -> std::unordered_map<std::string, Element> {
    throw_if(!is_synchronised() || trackings().empty(), "Last synchronised tracking does not exist.");
    std::unordered_map<std::string, Element> last_synchronised_;
    for (const auto& [key, tracking_] : trackings()) {
        last_synchronised_.emplace(key, tracking_.last());
    }
    return last_synchronised_;
}

template<typename Element_, IsTimePoint Time_>
inline auto MultiTracking<Element_, Time_>::synchronisation_time() const -> Time {
    throw_if(!is_synchronised() || trackings().empty(), "Synchronisation time does not exist.");
    return trackings().cbegin()->second.last_time();
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
