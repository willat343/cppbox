#include "cppbox/bytes.hpp"

#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

namespace cppbox {

BytesDecoder::BytesDecoder(const std::byte* bytes_, const std::size_t size_) : BytesDecoder(bytes_, size_, nullptr) {}

BytesDecoder BytesDecoder::create_internal_decoder(const std::size_t internal_size) {
    return BytesDecoder{bytes() + offset(), internal_size, this};
}

std::size_t BytesDecoder::internal_depth() const {
    std::size_t internal_depth_{0};
    const BytesDecoder* current_parent_decoder = this;
    while (current_parent_decoder->is_internal_decoder()) {
        ++internal_depth_;
        assert(current_parent_decoder != current_parent_decoder->parent_decoder());
        current_parent_decoder = current_parent_decoder->parent_decoder();
    }
    return internal_depth_;
}

BytesDecoder::BytesDecoder(const std::byte* bytes_, const std::size_t size_, BytesDecoder* parent_decoder_)
    : bytes_(bytes_), size_(size_), offset_(0), parent_decoder_(parent_decoder_) {}

std::string BytesDecoder::to_hex_string(const std::size_t num_bytes, const std::size_t extra_offset) {
    throw_if_insufficient_bytes_remaining(extra_offset + num_bytes);
    std::stringstream ss;
    ss << std::hex << std::showbase << std::setfill('0');
    for (std::size_t i = 0; i < num_bytes; ++i) {
        ss << (i == 0 ? "" : " ") << "0x" << std::setw(2)
           << static_cast<unsigned int>(*(bytes() + offset() + extra_offset + i));
    }
    return ss.str();
}

void BytesDecoder::throw_if_insufficient_bytes_remaining(const std::size_t num_bytes) const {
    if (insufficient_bytes_remaining(num_bytes)) {
        throw std::runtime_error("BytesDecoder: Buffer overflow in message parsing when trying to read " +
                                 std::to_string(num_bytes) + " bytes when only " + std::to_string(bytes_remaining()) +
                                 "/" + std::to_string(size()) + " bytes remaining.");
    }
}

}
