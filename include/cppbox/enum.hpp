#ifndef CPPBOX_ENUM_HPP
#define CPPBOX_ENUM_HPP

#include <array>
#include <ostream>
#include <stdexcept>
#include <string>

#include "cppbox/exceptions.hpp"
#include "cppbox/macro.hpp"
#include "cppbox/parse.hpp"

#define CREATE_SMART_ENUM_IMPL_ADD_SWITCH_CASE_TO_STRING(x) \
    case (x):                                               \
        return std::string(#x);
#define CREATE_SMART_ENUM_IMPL_ADD_IF_ELSE_CASE_CONSTRUCTOR_STRING(x) \
    if (string == std::string(#x)) {                                  \
        identifier = x;                                               \
    } else
#define CREATE_SMART_ENUM_IMPL_CONTRUCTOR_WITH_COMMA(SmartEnum, x) SmartEnum(x),
/**
 * @brief This macro creates a class which acts as an enum, except it is constructable from and convertable to a string.
 * The enum values are passed as variadic arguments, of which there must be at least 1. Example usage:
 * ```
 * CREATE_SMART_ENUM(Quality, GOOD, BAD, UGLY)
 * // ...
 * Quality quality("GOOD");
 * ```
 *
 * The class can directly be used within switch statements without change of syntax, for example:
 * ```
 * switch (quality) {
 *     case Quality::GOOD: // ...
 *     case Quality::BAD: // ...
 *     case Quality::UGLY: // ...
 *     default: // ...
 * }
 * ```
 *
 * Implicitly every identifier is associated with a string and std::size_t value. One can be iterate over the
 * identifiers in several ways:
 * ```
 * for (Quality quality : Quality::values()) {
 *     // ...
 * }
 * ```
 * or
 * ```
 * for (auto it = Quality::begin(); it != Quality::end(); ++it) {
 *     Quality quality = *it;
 *     // ...
 * }
 * ```
 * or even in extreme performance cases:
 * ```
 * for (Quality::Identifiers quality_id : Quality::identifiers) {
 *     // ...
 * }
 * ```
 *
 */
#define CREATE_SMART_ENUM(SmartEnum, ...)                                                                         \
    class SmartEnum {                                                                                             \
    public:                                                                                                       \
        enum Identifiers : std::size_t { FOR_EACH(ADD_COMMA, __VA_ARGS__) };                                      \
                                                                                                                  \
        static constexpr inline std::size_t count = VA_NARGS(__VA_ARGS__);                                        \
                                                                                                                  \
        static constexpr std::array<Identifiers, SmartEnum::count> identifiers =                                  \
                std::to_array<Identifiers>({FOR_EACH(ADD_COMMA, __VA_ARGS__)});                                   \
                                                                                                                  \
        static constexpr std::array<SmartEnum, SmartEnum::count> values() {                                       \
            return std::to_array<SmartEnum>(                                                                      \
                    {FOR_EACH_I(CREATE_SMART_ENUM_IMPL_CONTRUCTOR_WITH_COMMA, SmartEnum, __VA_ARGS__)});          \
        }                                                                                                         \
                                                                                                                  \
        constexpr SmartEnum() {};                                                                                 \
                                                                                                                  \
        constexpr SmartEnum(const Identifiers identifier) : identifier(identifier) {}                             \
                                                                                                                  \
        template<std::integral Integer>                                                                           \
            requires(!std::same_as<Integer, bool>)                                                                \
        explicit SmartEnum(const Integer index) {                                                                 \
            if constexpr (std::is_signed_v<Integer>) {                                                            \
                throw_if(index < 0, "Cannot create from index < 0.");                                             \
            }                                                                                                     \
            throw_if(static_cast<std::size_t>(index) >= SmartEnum::count, "Cannot create from index >= count)."); \
            identifier = identifiers[index];                                                                      \
        }                                                                                                         \
                                                                                                                  \
        explicit SmartEnum(const std::string& string) {                                                           \
            FOR_EACH(CREATE_SMART_ENUM_IMPL_ADD_IF_ELSE_CASE_CONSTRUCTOR_STRING, __VA_ARGS__) {                   \
                throw_here("Failed to convert " #SmartEnum " from string \"" + string + "\".");                   \
            }                                                                                                     \
        }                                                                                                         \
                                                                                                                  \
        inline Identifiers operator()() const {                                                                   \
            return identifier;                                                                                    \
        }                                                                                                         \
                                                                                                                  \
        constexpr inline operator Identifiers() const {                                                           \
            return identifier;                                                                                    \
        }                                                                                                         \
                                                                                                                  \
        inline operator std::string() const {                                                                     \
            switch (identifier) {                                                                                 \
                FOR_EACH(CREATE_SMART_ENUM_IMPL_ADD_SWITCH_CASE_TO_STRING, __VA_ARGS__)                           \
                default:                                                                                          \
                    throw_here("Failed to convert " #SmartEnum " to string.");                                    \
            }                                                                                                     \
        }                                                                                                         \
                                                                                                                  \
        template<std::integral Integer>                                                                           \
            requires(!std::same_as<Integer, bool>)                                                                \
        static inline std::string string(const Integer index) {                                                   \
            return std::string(SmartEnum(index));                                                                 \
        }                                                                                                         \
                                                                                                                  \
        template<std::integral Integer>                                                                           \
            requires(!std::same_as<Integer, bool>)                                                                \
        static inline std::string string_lower(const Integer index) {                                             \
            return cppbox::tolower(SmartEnum::string(index));                                                     \
        }                                                                                                         \
                                                                                                                  \
        inline std::string string_lower() const {                                                                 \
            return cppbox::tolower(*this);                                                                        \
        }                                                                                                         \
                                                                                                                  \
        template<std::integral Integer>                                                                           \
            requires(!std::same_as<Integer, bool>)                                                                \
        static inline std::string string_upper(const Integer index) {                                             \
            return cppbox::toupper(SmartEnum::string(index));                                                     \
        }                                                                                                         \
                                                                                                                  \
        inline std::string string_upper() const {                                                                 \
            return cppbox::toupper(*this);                                                                        \
        }                                                                                                         \
                                                                                                                  \
        friend inline std::ostream& operator<<(std::ostream& os, const SmartEnum rhs) {                           \
            os << std::string(rhs);                                                                               \
            return os;                                                                                            \
        }                                                                                                         \
        friend inline bool operator==(const SmartEnum::Identifiers lhs, const SmartEnum rhs) {                    \
            return lhs == rhs();                                                                                  \
        }                                                                                                         \
        friend inline bool operator!=(const SmartEnum::Identifiers lhs, const SmartEnum rhs) {                    \
            return !(lhs == rhs);                                                                                 \
        }                                                                                                         \
        inline bool operator==(const SmartEnum rhs) const {                                                       \
            return identifier == rhs();                                                                           \
        }                                                                                                         \
        inline bool operator!=(const SmartEnum rhs) const {                                                       \
            return !(this->operator==(rhs));                                                                      \
        }                                                                                                         \
        inline bool operator==(const Identifiers rhs) const {                                                     \
            return identifier == rhs;                                                                             \
        }                                                                                                         \
        inline bool operator!=(const Identifiers rhs) const {                                                     \
            return !(this->operator==(rhs));                                                                      \
        }                                                                                                         \
                                                                                                                  \
        class Iterator {                                                                                          \
        public:                                                                                                   \
            using iterator_category = std::forward_iterator_tag;                                                  \
            using value_type = SmartEnum;                                                                         \
            using difference_type = std::ptrdiff_t;                                                               \
            using reference = SmartEnum;                                                                          \
            using pointer = void;                                                                                 \
                                                                                                                  \
            constexpr Iterator(const std::size_t index = 0) noexcept : index(index) {}                            \
                                                                                                                  \
            constexpr SmartEnum operator*() const noexcept {                                                      \
                return identifiers[index];                                                                        \
            }                                                                                                     \
                                                                                                                  \
            constexpr Iterator& operator++() noexcept {                                                           \
                ++index;                                                                                          \
                return *this;                                                                                     \
            }                                                                                                     \
                                                                                                                  \
            constexpr Iterator operator++(int) noexcept {                                                         \
                Iterator tmp = *this;                                                                             \
                ++(*this);                                                                                        \
                return tmp;                                                                                       \
            }                                                                                                     \
                                                                                                                  \
            constexpr bool operator==(const Iterator& it) const noexcept {                                        \
                return index == it.index;                                                                         \
            }                                                                                                     \
                                                                                                                  \
            constexpr bool operator!=(const Iterator& it) const noexcept {                                        \
                return index != it.index;                                                                         \
            }                                                                                                     \
                                                                                                                  \
        private:                                                                                                  \
            std::size_t index;                                                                                    \
        };                                                                                                        \
                                                                                                                  \
        static constexpr inline Iterator begin() {                                                                \
            return Iterator(0);                                                                                   \
        }                                                                                                         \
                                                                                                                  \
        static constexpr inline Iterator end() {                                                                  \
            return Iterator(SmartEnum::count);                                                                    \
        }                                                                                                         \
                                                                                                                  \
    private:                                                                                                      \
        Identifiers identifier;                                                                                   \
    };

#endif
