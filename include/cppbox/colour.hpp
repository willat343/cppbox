#ifndef CPPBOX_COLOUR_HPP
#define CPPBOX_COLOUR_HPP

#include <array>
#include <concepts>
#include <string>

#include "cppbox/enum.hpp"

namespace cppbox {

CREATE_SMART_ENUM(ColourName, BLACK, WHITE, GREY, RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, ORANGE, PURPLE)

/**
 * @brief Colour of red, green, blue and alpha (opacity) components, each in \f$ [0, 1] \f$.
 *
 * @tparam Scalar_ floating point type of the components
 */
template<std::floating_point Scalar_>
class Colour {
public:
    using Scalar = Scalar_;

    /**
     * @brief Construct a colour from its components, by default opaque black.
     *
     * @param r red
     * @param g green
     * @param b blue
     * @param a alpha (opacity)
     * @throws std::invalid_argument if a component is outside \f$ [0, 1] \f$
     */
    explicit Colour(const Scalar r = Scalar(0), const Scalar g = Scalar(0), const Scalar b = Scalar(0),
            const Scalar a = Scalar(1));

    /**
     * @brief Construct an opaque colour from its red, green and blue components.
     *
     * @param rgb
     * @throws std::invalid_argument if a component is outside \f$ [0, 1] \f$
     */
    explicit Colour(const std::array<Scalar, 3>& rgb);

    /**
     * @brief Construct a colour from its red, green, blue and alpha components.
     *
     * @param rgba
     * @throws std::invalid_argument if a component is outside \f$ [0, 1] \f$
     */
    explicit Colour(const std::array<Scalar, 4>& rgba);

    /**
     * @brief Create an opaque named colour.
     *
     * @param name
     * @return Colour
     */
    static Colour from_name(const ColourName name);

    /**
     * @brief Create an opaque colour determined by a seed string, the same for the same seed, e.g. to tell apart the
     * sources of data without choosing their colours.
     *
     * @param seed
     * @return Colour
     */
    static Colour from_seed(const std::string& seed);

    Scalar r() const;

    Scalar g() const;

    Scalar b() const;

    Scalar a() const;

    bool operator==(const Colour&) const = default;

private:
    Scalar r_;
    Scalar g_;
    Scalar b_;
    Scalar a_;
};

}

#include "cppbox/impl/colour.hpp"

#endif
