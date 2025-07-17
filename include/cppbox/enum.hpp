#ifndef CPPBOX_ENUM_HPP
#define CPPBOX_ENUM_HPP

#include <ostream>
#include <stdexcept>
#include <string>

#include "cppbox/macro.hpp"

#define CREATE_SMART_ENUM_IMPL_ADD_SWITCH_CASE_TO_STRING(x) \
    case (x):                                               \
        return std::string(#x);
#define CREATE_SMART_ENUM_IMPL_ADD_IF_ELSE_CASE_CONSTRUCTOR_STRING(x) \
    if (string == std::string(#x)) {                                  \
        identifier = x;                                               \
    } else
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
 * To allow smart enums to be defined within classes, this macro cannot create free functions (e.g. for operators).
 * Hence an additional macro `CREATE_SMART_ENUM_FREE_FUNCTIONS(FullScopeSmartEnum)` is available to create additional
 * optional but useful functions, such as additional operators which must be free. Here `FullScopeSmartEnum` is the full
 * scope to the `SmartEnum`, e.g. my_namespace::MyClass::MySmartEnum. For smart enums where the full scope is
 * templated, (e.g. my_namespace::MyClass<T>::MySmartEnum, an additional macro
 * `CREATE_SMART_ENUM_TEMPLATED_FREE_FUNCTIONS(FullScopeSmartEnum, Template)` is avaiable where `Template` is the full
 * template descriptor, e.g. `template<typename T>`).
 *
 */
#define CREATE_SMART_ENUM(SmartEnum, ...)                                                                     \
    class SmartEnum {                                                                                         \
    public:                                                                                                   \
        enum Identifiers { FOR_EACH(ADD_COMMA, __VA_ARGS__) };                                                \
                                                                                                              \
        SmartEnum() {};                                                                                       \
                                                                                                              \
        SmartEnum(const Identifiers identifier) : identifier(identifier) {}                                   \
                                                                                                              \
        SmartEnum(const std::string& string) {                                                                \
            FOR_EACH(CREATE_SMART_ENUM_IMPL_ADD_IF_ELSE_CASE_CONSTRUCTOR_STRING, __VA_ARGS__) {               \
                throw std::runtime_error("Failed to convert " #SmartEnum " from string \"" + string + "\"."); \
            }                                                                                                 \
        }                                                                                                     \
                                                                                                              \
        inline Identifiers operator()() const {                                                               \
            return identifier;                                                                                \
        }                                                                                                     \
                                                                                                              \
        /**                                                                                                   \
         * @brief Compile-time conversion to integer-type allows switch statements to be used for the class.  \
         *                                                                                                    \
         * @return int                                                                                        \
         */                                                                                                   \
        constexpr inline operator int() const {                                                               \
            return static_cast<int>(identifier);                                                              \
        }                                                                                                     \
                                                                                                              \
        inline operator std::string() const {                                                                 \
            switch (identifier) {                                                                             \
                FOR_EACH(CREATE_SMART_ENUM_IMPL_ADD_SWITCH_CASE_TO_STRING, __VA_ARGS__)                       \
                default:                                                                                      \
                    throw std::runtime_error("Failed to convert " #SmartEnum " to string.");                  \
            }                                                                                                 \
        }                                                                                                     \
                                                                                                              \
        bool operator==(const SmartEnum rhs) const {                                                          \
            return identifier == rhs();                                                                       \
        }                                                                                                     \
        bool operator!=(const SmartEnum rhs) const {                                                          \
            return !(this->operator==(rhs));                                                                  \
        }                                                                                                     \
        bool operator==(const Identifiers rhs) const {                                                        \
            return identifier == rhs;                                                                         \
        }                                                                                                     \
        bool operator!=(const Identifiers rhs) const {                                                        \
            return !(this->operator==(rhs));                                                                  \
        }                                                                                                     \
                                                                                                              \
    private:                                                                                                  \
        Identifiers identifier;                                                                               \
    };

#define CREATE_SMART_ENUM_TEMPLATED_FREE_FUNCTIONS(FullScopeSmartEnum, Template)                        \
    Template inline std::ostream& operator<<(std::ostream& os, const typename FullScopeSmartEnum rhs) { \
        os << std::string(rhs);                                                                         \
        return os;                                                                                      \
    }                                                                                                   \
    Template inline bool operator==(const typename FullScopeSmartEnum::Identifiers lhs,                 \
            const typename FullScopeSmartEnum rhs) {                                                    \
        return lhs == rhs();                                                                            \
    }                                                                                                   \
    Template inline bool operator!=(const typename FullScopeSmartEnum::Identifiers lhs,                 \
            const typename FullScopeSmartEnum rhs) {                                                    \
        return !(lhs == rhs);                                                                           \
    }

#define CREATE_SMART_ENUM_FREE_FUNCTIONS(FullScopeSmartEnum)                                          \
    inline std::ostream& operator<<(std::ostream& os, const FullScopeSmartEnum rhs) {                 \
        os << std::string(rhs);                                                                       \
        return os;                                                                                    \
    }                                                                                                 \
    inline bool operator==(const FullScopeSmartEnum::Identifiers lhs, const FullScopeSmartEnum rhs) { \
        return lhs == rhs();                                                                          \
    }                                                                                                 \
    inline bool operator!=(const FullScopeSmartEnum::Identifiers lhs, const FullScopeSmartEnum rhs) { \
        return !(lhs == rhs);                                                                         \
    }

#endif
