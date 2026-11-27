#ifndef CPPBOX_IMPL_COLOUR_HPP
#define CPPBOX_IMPL_COLOUR_HPP

#include <array>
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <string>

#include "cppbox/colour.hpp"
#include "cppbox/exceptions.hpp"

namespace cppbox {

template<std::floating_point Scalar_>
inline Colour<Scalar_>::Colour(const Scalar r, const Scalar g, const Scalar b, const Scalar a)
    : r_(r), g_(g), b_(b), a_(a) {
    throw_if(!(r >= Scalar(0) && r <= Scalar(1) && g >= Scalar(0) && g <= Scalar(1) && b >= Scalar(0) &&
                     b <= Scalar(1) && a >= Scalar(0) && a <= Scalar(1)),
            "Colour components (" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ", " +
                    std::to_string(a) + ") must be in [0, 1].",
            std::invalid_argument);
}

template<std::floating_point Scalar_>
inline Colour<Scalar_>::Colour(const std::array<Scalar, 3>& rgb) : Colour(rgb[0], rgb[1], rgb[2]) {}

template<std::floating_point Scalar_>
inline Colour<Scalar_>::Colour(const std::array<Scalar, 4>& rgba) : Colour(rgba[0], rgba[1], rgba[2], rgba[3]) {}

template<std::floating_point Scalar_>
inline Colour<Scalar_> Colour<Scalar_>::from_name(const ColourName name) {
    switch (name) {
        case ColourName::BLACK:
            return Colour{Scalar(0.0), Scalar(0.0), Scalar(0.0)};
        case ColourName::WHITE:
            return Colour{Scalar(1.0), Scalar(1.0), Scalar(1.0)};
        case ColourName::GREY:
            return Colour{Scalar(0.5), Scalar(0.5), Scalar(0.5)};
        case ColourName::RED:
            return Colour{Scalar(1.0), Scalar(0.0), Scalar(0.0)};
        case ColourName::GREEN:
            return Colour{Scalar(0.0), Scalar(1.0), Scalar(0.0)};
        case ColourName::BLUE:
            return Colour{Scalar(0.0), Scalar(0.0), Scalar(1.0)};
        case ColourName::YELLOW:
            return Colour{Scalar(1.0), Scalar(1.0), Scalar(0.0)};
        case ColourName::CYAN:
            return Colour{Scalar(0.0), Scalar(1.0), Scalar(1.0)};
        case ColourName::MAGENTA:
            return Colour{Scalar(1.0), Scalar(0.0), Scalar(1.0)};
        case ColourName::ORANGE:
            return Colour{Scalar(1.0), Scalar(0.5), Scalar(0.0)};
        case ColourName::PURPLE:
            return Colour{Scalar(0.5), Scalar(0.0), Scalar(0.5)};
        default:
            throw_here("Colour name " + std::string(name) + " has no colour.");
    }
}

template<std::floating_point Scalar_>
inline Colour<Scalar_> Colour<Scalar_>::from_seed(const std::string& seed) {
    // Each of red, green and blue from a byte of the seed's hash
    const std::size_t hash = std::hash<std::string>{}(seed);
    return Colour{static_cast<Scalar>((hash >> 0) & 0xFF) / Scalar(255),
            static_cast<Scalar>((hash >> 8) & 0xFF) / Scalar(255),
            static_cast<Scalar>((hash >> 16) & 0xFF) / Scalar(255)};
}

template<std::floating_point Scalar_>
inline typename Colour<Scalar_>::Scalar Colour<Scalar_>::r() const {
    return r_;
}

template<std::floating_point Scalar_>
inline typename Colour<Scalar_>::Scalar Colour<Scalar_>::g() const {
    return g_;
}

template<std::floating_point Scalar_>
inline typename Colour<Scalar_>::Scalar Colour<Scalar_>::b() const {
    return b_;
}

template<std::floating_point Scalar_>
inline typename Colour<Scalar_>::Scalar Colour<Scalar_>::a() const {
    return a_;
}

}

#endif
