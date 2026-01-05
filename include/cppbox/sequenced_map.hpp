#ifndef CPPBOX_SEQUENCED_MAP_HPP
#define CPPBOX_SEQUENCED_MAP_HPP

#include <list>
#include <unordered_map>

namespace cppbox {

/**
 * @brief A SequencedMap is a data structure whose key-value pairs are ordered sequentially (i.e. through insertion,
 * emplacement, etc.) while facilitating lookup by key. It can be a drop-in replacement for `std::unordered_map<Key,
 * Value>` when a sequential ordering is also required.
 *
 * @tparam Key
 * @tparam Value
 */
template<typename Key, typename Value>
class SequencedMap {
public:
    using List = std::list<std::pair<Key, Value>>;
    using Iterator = typename List::iterator;
    using ConstIterator = typename List::const_iterator;
    using Map = std::unordered_map<Key, Iterator>;

    /* Iterators */

    Iterator begin() {
        return list_.begin();
    }

    ConstIterator begin() const {
        return list_.begin();
    }

    ConstIterator cbegin() const {
        return list_.cbegin();
    }

    ConstIterator cend() const {
        return list_.cend();
    }

    Iterator end() {
        return list_.end();
    }

    ConstIterator end() const {
        return list_.end();
    }

    /* Capacity */

    bool empty() const noexcept {
        return map_.empty();
    }

    std::size_t size() const noexcept {
        return map_.size();
    }

    std::size_t max_size() const noexcept {
        // conservative: limited by both containers
        return std::min(list_.max_size(), map_.max_size());
    }

    /* Modifiers */

    void clear() noexcept {
        list_.clear();
        map_.clear();
    }

    template<typename K, typename... Args>
    std::pair<Iterator, bool> emplace(Iterator pos, K&& key, Args&&... args) {
        // Check if key already exists
        auto it = map_.find(key);
        if (it != map_.end()) {
            return {it->second, false};  // reject duplicates
        }

        // Construct in-place at position pos
        auto lit = list_.emplace(pos, std::piecewise_construct, std::forward_as_tuple(std::forward<K>(key)),
                std::forward_as_tuple(std::forward<Args>(args)...));

        // Update map
        map_.emplace(lit->first, lit);
        return {lit, true};
    }

    template<typename K, typename... Args>
    std::pair<Iterator, bool> emplace_back(K&& key, Args&&... args) {
        return emplace(list_.end(), std::forward<K>(key), std::forward<Args>(args)...);
    }

    template<typename K, typename... Args>
    std::pair<Iterator, bool> emplace_front(K&& key, Args&&... args) {
        return emplace(list_.begin(), std::forward<K>(key), std::forward<Args>(args)...);
    }

    std::size_t erase(const Key& key) {
        auto it = map_.find(key);
        if (it == map_.end()) {
            return 0;
        }

        list_.erase(it->second);
        map_.erase(it);
        return 1;
    }

    Iterator erase(Iterator pos) {
        map_.erase(pos->first);   // remove key from map
        return list_.erase(pos);  // erase from list and return next Iterator
    }

    Iterator erase(Iterator first, Iterator last) {
        for (auto it = first; it != last; ++it) {
            map_.erase(it->first);  // remove each key from map
        }
        return list_.erase(first, last);  // erase from list and return next Iterator
    }

    Iterator insert(Iterator pos, const std::pair<Key, Value>& value) {
        return emplace(pos, value.first, value.second).first;
    }

    Iterator insert(Iterator pos, std::pair<Key, Value>&& value) {
        return emplace(pos, std::move(value.first), std::move(value.second)).first;
    }

    Iterator insert_back(const std::pair<Key, Value>& value) {
        return insert(list_.end(), value);
    }

    Iterator insert_back(std::pair<Key, Value>&& value) {
        return insert(list_.end(), std::move(value));
    }

    Iterator insert_front(const std::pair<Key, Value>& value) {
        return insert(list_.begin(), value);
    }

    Iterator insert_front(std::pair<Key, Value>&& value) {
        return insert(list_.begin(), std::move(value));
    }

    template<typename K, typename V>
    std::pair<Iterator, bool> insert_or_assign(Iterator pos, K&& key, V&& value) {
        auto it = map_.find(key);
        if (it != map_.end()) {
            // Key exists: overwrite value, Iterator stays in place
            it->second->second = std::forward<V>(value);
            return {it->second, false};
        }

        // Key does not exist: insert at pos
        return emplace(pos, std::forward<K>(key), std::forward<V>(value));
    }

    template<typename K, typename V>
    std::pair<Iterator, bool> insert_or_assign_back(K&& key, V&& value) {
        return insert_or_assign(list_.end(), std::forward<K>(key), std::forward<V>(value));
    }

    template<typename K, typename V>
    std::pair<Iterator, bool> insert_or_assign_front(K&& key, V&& value) {
        return insert_or_assign(list_.begin(), std::forward<K>(key), std::forward<V>(value));
    }

    void pop_back() {
        auto& back = list_.back();
        map_.erase(back.first);
        list_.pop_back();
    }

    void pop_front() {
        auto& front = list_.front();
        map_.erase(front.first);
        list_.pop_front();
    }

    template<typename K, typename... Args>
    std::pair<Iterator, bool> try_emplace(Iterator pos, K&& key, Args&&... args) {
        auto it = map_.find(key);
        if (it != map_.end()) {
            return {it->second, false};  // key exists, do nothing
        }

        return emplace(pos, std::forward<K>(key), std::forward<Args>(args)...);
    }

    template<typename K, typename... Args>
    std::pair<Iterator, bool> try_emplace_back(K&& key, Args&&... args) {
        return try_emplace(list_.end(), std::forward<K>(key), std::forward<Args>(args)...);
    }

    template<typename K, typename... Args>
    std::pair<Iterator, bool> try_emplace_front(K&& key, Args&&... args) {
        return try_emplace(list_.begin(), std::forward<K>(key), std::forward<Args>(args)...);
    }

    /* Lookup */

    const Value& at(const Key& k) const {
        return map_.at(k)->second;
    }

    Value& at(const Key& k) {
        return map_.at(k)->second;
    }

    std::pair<Key, Value>& back() {
        return list_.back();
    }

    const std::pair<Key, Value>& back() const {
        return list_.back();
    }

    bool contains(const Key& k) const {
        return map_.find(k) != map_.end();
    }

    Iterator find(const Key& key) {
        auto it = map_.find(key);
        return it == map_.end() ? list_.end() : it->second;
    }

    ConstIterator find(const Key& key) const {
        auto it = map_.find(key);
        return it == map_.end() ? list_.end() : it->second;
    }

    std::pair<Key, Value>& front() {
        return list_.front();
    }

    const std::pair<Key, Value>& front() const {
        return list_.front();
    }

private:
    List list_;
    Map map_;
};

}

#endif
