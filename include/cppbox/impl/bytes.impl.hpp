#ifndef CPPBOX_IMPL_BYTES_IMPL_HPP
#define CPPBOX_IMPL_BYTES_IMPL_HPP

#include <cassert>
#include <iomanip>
#include <sstream>
#include <string>

#include "cppbox/exceptions.hpp"
#include "cppbox/impl/bytes.hpp"
#include "cppbox/impl/cppbox.hpp"

namespace cppbox {

CPPBOX_INLINE std::size_t BytesDecoder::internal_depth() const {
    std::size_t internal_depth_{0};
    const BytesDecoder* current_parent_decoder = this;
    while (current_parent_decoder->is_internal_decoder()) {
        ++internal_depth_;
        assert(current_parent_decoder != current_parent_decoder->parent_decoder());
        current_parent_decoder = current_parent_decoder->parent_decoder();
    }
    return internal_depth_;
}

CPPBOX_INLINE std::string BytesDecoder::to_hex_string(const std::size_t num_bytes, const std::size_t extra_offset) {
    throw_if_insufficient_bytes_remaining(extra_offset + num_bytes);
    std::stringstream ss;
    ss << std::hex << std::showbase << std::setfill('0');
    for (std::size_t i = 0; i < num_bytes; ++i) {
        ss << (i == 0 ? "" : " ") << "0x" << std::setw(2)
           << static_cast<unsigned int>(*(bytes() + offset() + extra_offset + i));
    }
    return ss.str();
}

CPPBOX_INLINE void BytesDecoder::throw_if_insufficient_bytes_remaining(const std::size_t num_bytes) const {
    throw_if(insufficient_bytes_remaining(num_bytes),
            "BytesDecoder: Buffer overflow in message parsing when trying to read " + std::to_string(num_bytes) +
                    " bytes when only " + std::to_string(bytes_remaining()) + "/" + std::to_string(size()) +
                    " bytes remaining.");
}

}

#endif
