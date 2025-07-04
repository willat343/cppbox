#ifndef CPPBOX_MACRO_HPP
#define CPPBOX_MACRO_HPP

// Add a comma to the end
#define ADD_COMMA(x) x,

// FE (For each) macros to handle up to 19 arguments
#define FE0(MACRO)
#define FE1(MACRO, X) MACRO(X)
#define FE2(MACRO, X, ...) MACRO(X) FE1(MACRO, __VA_ARGS__)
#define FE3(MACRO, X, ...) MACRO(X) FE2(MACRO, __VA_ARGS__)
#define FE4(MACRO, X, ...) MACRO(X) FE3(MACRO, __VA_ARGS__)
#define FE5(MACRO, X, ...) MACRO(X) FE4(MACRO, __VA_ARGS__)
#define FE6(MACRO, X, ...) MACRO(X) FE5(MACRO, __VA_ARGS__)
#define FE7(MACRO, X, ...) MACRO(X) FE6(MACRO, __VA_ARGS__)
#define FE8(MACRO, X, ...) MACRO(X) FE7(MACRO, __VA_ARGS__)
#define FE9(MACRO, X, ...) MACRO(X) FE8(MACRO, __VA_ARGS__)
#define FE10(MACRO, X, ...) MACRO(X) FE9(MACRO, __VA_ARGS__)
#define FE11(MACRO, X, ...) MACRO(X) FE10(MACRO, __VA_ARGS__)
#define FE12(MACRO, X, ...) MACRO(X) FE11(MACRO, __VA_ARGS__)
#define FE13(MACRO, X, ...) MACRO(X) FE12(MACRO, __VA_ARGS__)
#define FE14(MACRO, X, ...) MACRO(X) FE13(MACRO, __VA_ARGS__)
#define FE15(MACRO, X, ...) MACRO(X) FE14(MACRO, __VA_ARGS__)
#define FE16(MACRO, X, ...) MACRO(X) FE15(MACRO, __VA_ARGS__)
#define FE17(MACRO, X, ...) MACRO(X) FE16(MACRO, __VA_ARGS__)
#define FE18(MACRO, X, ...) MACRO(X) FE17(MACRO, __VA_ARGS__)
#define FE19(MACRO, X, ...) MACRO(X) FE18(MACRO, __VA_ARGS__)

// Expansion based on argument count
#define FOR_EACH_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, IMPL, \
        ...)                                                                                                          \
    IMPL

/**
 * @brief The `FOR_EACH` macro calls `MACRO` on each argument passed in.
 *
 */
#define FOR_EACH(MACRO, ...)                                                                                         \
    FOR_EACH_IMPL(_0, ##__VA_ARGS__, FE19, FE18, FE17, FE16, FE15, FE14, FE13, FE12, FE11, FE10, FE9, FE8, FE7, FE6, \
            FE5, FE4, FE3, FE2, FE1, FE0)                                                                            \
    (MACRO, ##__VA_ARGS__)

#endif
