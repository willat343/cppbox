#ifndef CPPBOX_IMPL_BYTES_HPP
#define CPPBOX_IMPL_BYTES_HPP

#include <cassert>
#include <cstring>
#include <stdexcept>
#include <utility>

#include "cppbox/bytes.hpp"

namespace cppbox {

inline BytesDecoder::BytesDecoder(const std::byte* bytes_, const std::size_t size_)
    : BytesDecoder(bytes_, size_, nullptr) {}

inline BytesDecoder BytesDecoder::create_internal_decoder(const std::size_t internal_size) {
    return BytesDecoder{bytes() + offset(), internal_size, this};
}

inline std::size_t BytesDecoder::bytes_remaining() const {
    return size() - offset();
}

inline const std::byte* BytesDecoder::bytes() const {
    return bytes_;
}

template<typename T>
    requires(std::is_trivially_copyable_v<T>)
inline void BytesDecoder::ignore(const std::size_t num_ignore) {
    throw_if_insufficient_bytes_remaining(sizeof(T) * num_ignore);
    increment_offset(sizeof(T) * num_ignore);
}

template<typename T>
    requires(std::is_same_v<T, std::string>)
inline void BytesDecoder::ignore(const std::size_t string_length, const std::size_t num_ignore) {
    throw_if_insufficient_bytes_remaining(string_length * num_ignore);
    increment_offset(string_length * num_ignore);
}

inline void BytesDecoder::ignore_remaining() {
    increment_offset(bytes_remaining());
}

inline bool BytesDecoder::insufficient_bytes_remaining(std::size_t num_bytes) const {
    return num_bytes > bytes_remaining();
}

inline bool BytesDecoder::is_finished() const {
    return bytes_remaining() == 0;
}

inline bool BytesDecoder::is_internal_decoder() const {
    return parent_decoder() != nullptr;
}

inline std::size_t BytesDecoder::offset() const {
    return offset_;
}

template<typename T>
    requires(std::is_trivially_copyable_v<T>)
inline T BytesDecoder::peak(const std::size_t extra_offset) const {
    throw_if_insufficient_bytes_remaining(extra_offset + sizeof(T));
    T value;
    std::memcpy(&value, bytes() + offset() + extra_offset, sizeof(T));
    return value;
}

template<typename T>
    requires(std::is_same_v<T, std::string>)
inline T BytesDecoder::peak(const std::size_t string_length, const std::size_t extra_offset) const {
    throw_if_insufficient_bytes_remaining(extra_offset + string_length);
    std::string string(reinterpret_cast<const char*>(bytes() + offset() + extra_offset), string_length);
    return string;
}

template<typename T>
    requires(std::is_trivially_copyable_v<T>)
inline T BytesDecoder::read() {
    T value = peak<T>();
    increment_offset(sizeof(T));
    return value;
}

template<typename T>
    requires(std::is_same_v<T, std::string>)
inline T BytesDecoder::read(const std::size_t string_length) {
    T string = peak<T>(string_length);
    increment_offset(string_length);
    return string;
}

inline std::size_t BytesDecoder::size() const {
    return size_;
}

inline BytesDecoder::BytesDecoder(const std::byte* bytes_, const std::size_t size_, BytesDecoder* parent_decoder_)
    : bytes_(bytes_), size_(size_), offset_(0), parent_decoder_(parent_decoder_) {}

inline void BytesDecoder::increment_offset(const std::size_t num_bytes) {
    assert(num_bytes <= size_);
    offset_ += num_bytes;
    assert(offset_ <= size_);
    if (is_internal_decoder()) {
        parent_decoder()->increment_offset(num_bytes);
    }
}

inline const BytesDecoder* BytesDecoder::parent_decoder() const {
    return parent_decoder_;
}

inline BytesDecoder* BytesDecoder::parent_decoder() {
    return const_cast<BytesDecoder*>(std::as_const(*this).parent_decoder());
}

}

#if CPPBOX_HEADER_ONLY
#include "bytes.impl.hpp"
#endif

#endif
