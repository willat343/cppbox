#ifndef CPPBOX_BYTES_HPP
#define CPPBOX_BYTES_HPP

#include <cstddef>
#include <string>
#include <type_traits>

namespace cppbox {

class BytesDecoder {
public:
    explicit BytesDecoder(const std::byte* bytes_, const std::size_t size_);

    virtual ~BytesDecoder() = default;

    std::size_t bytes_remaining() const;

    const std::byte* bytes() const;

    BytesDecoder create_internal_decoder(const std::size_t internal_size);

    template<typename T>
        requires(std::is_trivially_copyable_v<T>)
    void ignore(const std::size_t num_ignore = 1);

    template<typename T>
        requires(std::is_same_v<T, std::string>)
    void ignore(const std::size_t string_length, const std::size_t num_ignore = 1);

    void ignore_remaining();

    bool insufficient_bytes_remaining(std::size_t num_bytes) const;

    bool is_finished() const;

    bool is_internal_decoder() const;

    std::size_t internal_depth() const;

    std::size_t offset() const;

    template<typename T>
        requires(std::is_trivially_copyable_v<T>)
    T peak(const std::size_t extra_offset = 0) const;

    template<typename T>
        requires(std::is_same_v<T, std::string>)
    T peak(const std::size_t string_length, const std::size_t extra_offset = 0) const;

    template<typename T>
        requires(std::is_trivially_copyable_v<T>)
    T read();

    template<typename T>
        requires(std::is_same_v<T, std::string>)
    T read(const std::size_t string_length);

    std::string to_hex_string(const std::size_t num_bytes, const std::size_t extra_offset = 0);

    std::size_t size() const;

protected:
    explicit BytesDecoder(const std::byte* bytes_, const std::size_t size_, BytesDecoder* parent_decoder_);

    void increment_offset(const std::size_t num_bytes);

    const BytesDecoder* parent_decoder() const;

    BytesDecoder* parent_decoder();

    void throw_if_insufficient_bytes_remaining(const std::size_t num_bytes) const;

private:
    const std::byte* bytes_;
    std::size_t size_;
    std::size_t offset_;
    BytesDecoder* parent_decoder_;
};

}

#include "cppbox/impl/bytes.hpp"

#endif
