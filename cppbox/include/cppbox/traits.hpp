#ifndef CPPBOX_TRAITS_HPP
#define CPPBOX_TRAITS_HPP

#include <type_traits>

#define REF_TYPES(Name)                               \
    using Name##ConstRef = cppbox::const_ref_t<Name>; \
    using Name##Ref = cppbox::ref_t<Name>;

#define REF_TEMPLATE_TYPES(NameT)                          \
    template<typename T>                                   \
    using NameT##ConstRef = cppbox::const_ref_t<NameT<T>>; \
    template<typename T>                                   \
    using NameT##Ref = cppbox::ref_t<NameT<T>>;

namespace cppbox {

template<typename T, typename Enable = void>
struct const_ref {
    using type = const T&;
};

template<typename T, typename Enable = void>
using const_ref_t = const_ref<T, Enable>::type;

template<typename T, typename Enable = void>
struct ref {
    using type = T&;
};

template<typename T, typename Enable = void>
using ref_t = ref<T, Enable>::type;

template<typename T, typename Enable = void>
struct remove_ref {
    using type = std::remove_reference_t<T>;
};

template<typename T, typename Enable = void>
using remove_ref_t = remove_ref<T, Enable>::type;

}

#endif
