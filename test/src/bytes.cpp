#include "cppbox/bytes.hpp"

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

TEST(bytes_encoder, write_and_size) {
    cppbox::BytesEncoder encoder;
    EXPECT_TRUE(encoder.empty());
    encoder.write(static_cast<std::int32_t>(42));
    encoder.write(std::string("hi"));
    EXPECT_FALSE(encoder.empty());
    EXPECT_EQ(encoder.size(), sizeof(std::int32_t) + 2);
}

TEST(bytes_decoder, read_trivial_and_string) {
    cppbox::BytesEncoder encoder;
    encoder.write(static_cast<std::int32_t>(42));
    encoder.write(std::string("hi"));
    cppbox::BytesDecoder decoder(encoder.bytes(), encoder.size());
    EXPECT_EQ(decoder.read<std::int32_t>(), 42);
    EXPECT_EQ(decoder.read<std::string>(2), "hi");
    EXPECT_TRUE(decoder.is_finished());
}

TEST(bytes_decoder, peak_does_not_advance_offset) {
    cppbox::BytesEncoder encoder;
    encoder.write(static_cast<std::int32_t>(7));
    cppbox::BytesDecoder decoder(encoder.bytes(), encoder.size());
    EXPECT_EQ(decoder.peak<std::int32_t>(), 7);
    EXPECT_EQ(decoder.offset(), 0u);
    EXPECT_EQ(decoder.read<std::int32_t>(), 7);
    EXPECT_EQ(decoder.offset(), sizeof(std::int32_t));
}

TEST(bytes_decoder, ignore_and_bytes_remaining) {
    cppbox::BytesEncoder encoder;
    encoder.write(static_cast<std::int32_t>(1));
    encoder.write(static_cast<std::int32_t>(2));
    cppbox::BytesDecoder decoder(encoder.bytes(), encoder.size());
    EXPECT_EQ(decoder.bytes_remaining(), encoder.size());
    decoder.ignore<std::int32_t>();
    EXPECT_EQ(decoder.read<std::int32_t>(), 2);
    EXPECT_TRUE(decoder.is_finished());
}

TEST(bytes_decoder, insufficient_bytes_throws) {
    cppbox::BytesEncoder encoder;
    encoder.write(static_cast<std::int32_t>(1));
    cppbox::BytesDecoder decoder(encoder.bytes(), encoder.size());
    EXPECT_ANY_THROW(decoder.read<std::int64_t>());
}

TEST(bytes_decoder, internal_decoder_advances_parent_offset) {
    cppbox::BytesEncoder encoder;
    encoder.write(static_cast<std::int32_t>(1));
    encoder.write(static_cast<std::int32_t>(2));
    cppbox::BytesDecoder decoder(encoder.bytes(), encoder.size());
    cppbox::BytesDecoder internal = decoder.create_internal_decoder(sizeof(std::int32_t));
    EXPECT_TRUE(internal.is_internal_decoder());
    EXPECT_FALSE(decoder.is_internal_decoder());
    EXPECT_EQ(internal.read<std::int32_t>(), 1);
    EXPECT_EQ(decoder.offset(), sizeof(std::int32_t));
    EXPECT_EQ(decoder.read<std::int32_t>(), 2);
}

TEST(bytes_decoder, to_hex_string) {
    cppbox::BytesEncoder encoder;
    encoder.write(static_cast<std::uint8_t>(0xAB));
    cppbox::BytesDecoder decoder(encoder.bytes(), encoder.size());
    EXPECT_EQ(decoder.to_hex_string(1), "0xab");
}
