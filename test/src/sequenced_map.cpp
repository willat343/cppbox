#include "cppbox/sequenced_map.hpp"

#include <gtest/gtest.h>

#include <string>
#include <vector>

TEST(sequenced_map, emplace_back_preserves_order) {
    cppbox::SequencedMap<std::string, int> map;
    EXPECT_TRUE(map.empty());
    map.emplace_back("a", 1);
    map.emplace_back("b", 2);
    map.emplace_back("c", 3);
    EXPECT_EQ(map.size(), 3u);
    std::vector<std::string> keys;
    for (const auto& [key, value] : map) {
        keys.push_back(key);
    }
    EXPECT_EQ(keys, (std::vector<std::string>{"a", "b", "c"}));
}

TEST(sequenced_map, lookup) {
    cppbox::SequencedMap<std::string, int> map;
    map.emplace_back("a", 1);
    map.emplace_back("b", 2);
    EXPECT_TRUE(map.contains("a"));
    EXPECT_FALSE(map.contains("z"));
    EXPECT_EQ(map.at("a"), 1);
    EXPECT_EQ(map.find("b")->second, 2);
    EXPECT_EQ(map.find("missing"), map.end());
}

TEST(sequenced_map, emplace_rejects_duplicates) {
    cppbox::SequencedMap<std::string, int> map;
    const auto [it1, inserted1] = map.emplace_back("a", 1);
    EXPECT_TRUE(inserted1);
    const auto [it2, inserted2] = map.emplace_back("a", 2);
    EXPECT_FALSE(inserted2);
    EXPECT_EQ(it2->second, 1);
    EXPECT_EQ(map.size(), 1u);
}

TEST(sequenced_map, erase_by_key_and_iterator) {
    cppbox::SequencedMap<std::string, int> map;
    map.emplace_back("a", 1);
    map.emplace_back("b", 2);
    map.emplace_back("c", 3);
    EXPECT_EQ(map.erase("b"), 1u);
    EXPECT_FALSE(map.contains("b"));
    EXPECT_EQ(map.size(), 2u);
    map.erase(map.begin());
    EXPECT_FALSE(map.contains("a"));
    EXPECT_EQ(map.size(), 1u);
}

TEST(sequenced_map, front_and_back) {
    cppbox::SequencedMap<std::string, int> map;
    map.emplace_back("a", 1);
    map.emplace_back("b", 2);
    EXPECT_EQ(map.front().first, "a");
    EXPECT_EQ(map.back().first, "b");
}

TEST(sequenced_map, insert_or_assign_back) {
    cppbox::SequencedMap<std::string, int> map;
    map.emplace_back("a", 1);
    map.insert_or_assign_back("a", 5);
    EXPECT_EQ(map.at("a"), 5);
    EXPECT_EQ(map.size(), 1u);
    map.insert_or_assign_back("b", 2);
    EXPECT_EQ(map.size(), 2u);
}

TEST(sequenced_map, pop_back_and_pop_front) {
    cppbox::SequencedMap<std::string, int> map;
    map.emplace_back("a", 1);
    map.emplace_back("b", 2);
    map.pop_front();
    EXPECT_FALSE(map.contains("a"));
    map.pop_back();
    EXPECT_FALSE(map.contains("b"));
    EXPECT_TRUE(map.empty());
}

TEST(sequenced_map, try_emplace_back) {
    cppbox::SequencedMap<std::string, int> map;
    map.try_emplace_back("a", 1);
    map.try_emplace_back("a", 2);
    EXPECT_EQ(map.at("a"), 1);
}

TEST(sequenced_map, clear) {
    cppbox::SequencedMap<std::string, int> map;
    map.emplace_back("a", 1);
    map.clear();
    EXPECT_TRUE(map.empty());
    EXPECT_EQ(map.size(), 0u);
}
