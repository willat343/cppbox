#ifndef CPPBOX_MACRO_HPP
#define CPPBOX_MACRO_HPP

// Add a comma to the end
#define ADD_COMMA(x) x,

// FE (FOR_EACH) macros to handle up to 19 arguments
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
#define FE20(MACRO, X, ...) MACRO(X) FE19(MACRO, __VA_ARGS__)
#define FE21(MACRO, X, ...) MACRO(X) FE20(MACRO, __VA_ARGS__)
#define FE22(MACRO, X, ...) MACRO(X) FE21(MACRO, __VA_ARGS__)
#define FE23(MACRO, X, ...) MACRO(X) FE22(MACRO, __VA_ARGS__)
#define FE24(MACRO, X, ...) MACRO(X) FE23(MACRO, __VA_ARGS__)
#define FE25(MACRO, X, ...) MACRO(X) FE24(MACRO, __VA_ARGS__)
#define FE26(MACRO, X, ...) MACRO(X) FE25(MACRO, __VA_ARGS__)
#define FE27(MACRO, X, ...) MACRO(X) FE26(MACRO, __VA_ARGS__)
#define FE28(MACRO, X, ...) MACRO(X) FE27(MACRO, __VA_ARGS__)
#define FE29(MACRO, X, ...) MACRO(X) FE28(MACRO, __VA_ARGS__)
#define FE30(MACRO, X, ...) MACRO(X) FE29(MACRO, __VA_ARGS__)
#define FE31(MACRO, X, ...) MACRO(X) FE30(MACRO, __VA_ARGS__)
#define FE32(MACRO, X, ...) MACRO(X) FE31(MACRO, __VA_ARGS__)
#define FE33(MACRO, X, ...) MACRO(X) FE32(MACRO, __VA_ARGS__)
#define FE34(MACRO, X, ...) MACRO(X) FE33(MACRO, __VA_ARGS__)
#define FE35(MACRO, X, ...) MACRO(X) FE34(MACRO, __VA_ARGS__)
#define FE36(MACRO, X, ...) MACRO(X) FE35(MACRO, __VA_ARGS__)
#define FE37(MACRO, X, ...) MACRO(X) FE36(MACRO, __VA_ARGS__)
#define FE38(MACRO, X, ...) MACRO(X) FE37(MACRO, __VA_ARGS__)
#define FE39(MACRO, X, ...) MACRO(X) FE38(MACRO, __VA_ARGS__)
#define FE40(MACRO, X, ...) MACRO(X) FE39(MACRO, __VA_ARGS__)
#define FE41(MACRO, X, ...) MACRO(X) FE40(MACRO, __VA_ARGS__)
#define FE42(MACRO, X, ...) MACRO(X) FE41(MACRO, __VA_ARGS__)
#define FE43(MACRO, X, ...) MACRO(X) FE42(MACRO, __VA_ARGS__)
#define FE44(MACRO, X, ...) MACRO(X) FE43(MACRO, __VA_ARGS__)
#define FE45(MACRO, X, ...) MACRO(X) FE44(MACRO, __VA_ARGS__)
#define FE46(MACRO, X, ...) MACRO(X) FE45(MACRO, __VA_ARGS__)
#define FE47(MACRO, X, ...) MACRO(X) FE46(MACRO, __VA_ARGS__)
#define FE48(MACRO, X, ...) MACRO(X) FE47(MACRO, __VA_ARGS__)
#define FE49(MACRO, X, ...) MACRO(X) FE48(MACRO, __VA_ARGS__)
#define FE50(MACRO, X, ...) MACRO(X) FE49(MACRO, __VA_ARGS__)
#define FE51(MACRO, X, ...) MACRO(X) FE50(MACRO, __VA_ARGS__)
#define FE52(MACRO, X, ...) MACRO(X) FE51(MACRO, __VA_ARGS__)
#define FE53(MACRO, X, ...) MACRO(X) FE52(MACRO, __VA_ARGS__)
#define FE54(MACRO, X, ...) MACRO(X) FE53(MACRO, __VA_ARGS__)
#define FE55(MACRO, X, ...) MACRO(X) FE54(MACRO, __VA_ARGS__)
#define FE56(MACRO, X, ...) MACRO(X) FE55(MACRO, __VA_ARGS__)
#define FE57(MACRO, X, ...) MACRO(X) FE56(MACRO, __VA_ARGS__)
#define FE58(MACRO, X, ...) MACRO(X) FE57(MACRO, __VA_ARGS__)
#define FE59(MACRO, X, ...) MACRO(X) FE58(MACRO, __VA_ARGS__)
#define FE60(MACRO, X, ...) MACRO(X) FE59(MACRO, __VA_ARGS__)
#define FE61(MACRO, X, ...) MACRO(X) FE60(MACRO, __VA_ARGS__)
#define FE62(MACRO, X, ...) MACRO(X) FE61(MACRO, __VA_ARGS__)
#define FE63(MACRO, X, ...) MACRO(X) FE62(MACRO, __VA_ARGS__)
#define FE64(MACRO, X, ...) MACRO(X) FE63(MACRO, __VA_ARGS__)
#define FE65(MACRO, X, ...) MACRO(X) FE64(MACRO, __VA_ARGS__)
#define FE66(MACRO, X, ...) MACRO(X) FE65(MACRO, __VA_ARGS__)
#define FE67(MACRO, X, ...) MACRO(X) FE66(MACRO, __VA_ARGS__)
#define FE68(MACRO, X, ...) MACRO(X) FE67(MACRO, __VA_ARGS__)
#define FE69(MACRO, X, ...) MACRO(X) FE68(MACRO, __VA_ARGS__)
#define FE70(MACRO, X, ...) MACRO(X) FE69(MACRO, __VA_ARGS__)
#define FE71(MACRO, X, ...) MACRO(X) FE70(MACRO, __VA_ARGS__)
#define FE72(MACRO, X, ...) MACRO(X) FE71(MACRO, __VA_ARGS__)
#define FE73(MACRO, X, ...) MACRO(X) FE72(MACRO, __VA_ARGS__)
#define FE74(MACRO, X, ...) MACRO(X) FE73(MACRO, __VA_ARGS__)
#define FE75(MACRO, X, ...) MACRO(X) FE74(MACRO, __VA_ARGS__)
#define FE76(MACRO, X, ...) MACRO(X) FE75(MACRO, __VA_ARGS__)
#define FE77(MACRO, X, ...) MACRO(X) FE76(MACRO, __VA_ARGS__)
#define FE78(MACRO, X, ...) MACRO(X) FE77(MACRO, __VA_ARGS__)
#define FE79(MACRO, X, ...) MACRO(X) FE78(MACRO, __VA_ARGS__)
#define FE80(MACRO, X, ...) MACRO(X) FE79(MACRO, __VA_ARGS__)
#define FE81(MACRO, X, ...) MACRO(X) FE80(MACRO, __VA_ARGS__)
#define FE82(MACRO, X, ...) MACRO(X) FE81(MACRO, __VA_ARGS__)
#define FE83(MACRO, X, ...) MACRO(X) FE82(MACRO, __VA_ARGS__)
#define FE84(MACRO, X, ...) MACRO(X) FE83(MACRO, __VA_ARGS__)
#define FE85(MACRO, X, ...) MACRO(X) FE84(MACRO, __VA_ARGS__)
#define FE86(MACRO, X, ...) MACRO(X) FE85(MACRO, __VA_ARGS__)
#define FE87(MACRO, X, ...) MACRO(X) FE86(MACRO, __VA_ARGS__)
#define FE88(MACRO, X, ...) MACRO(X) FE87(MACRO, __VA_ARGS__)
#define FE89(MACRO, X, ...) MACRO(X) FE88(MACRO, __VA_ARGS__)
#define FE90(MACRO, X, ...) MACRO(X) FE89(MACRO, __VA_ARGS__)
#define FE91(MACRO, X, ...) MACRO(X) FE90(MACRO, __VA_ARGS__)
#define FE92(MACRO, X, ...) MACRO(X) FE91(MACRO, __VA_ARGS__)
#define FE93(MACRO, X, ...) MACRO(X) FE92(MACRO, __VA_ARGS__)
#define FE94(MACRO, X, ...) MACRO(X) FE93(MACRO, __VA_ARGS__)
#define FE95(MACRO, X, ...) MACRO(X) FE94(MACRO, __VA_ARGS__)
#define FE96(MACRO, X, ...) MACRO(X) FE95(MACRO, __VA_ARGS__)
#define FE97(MACRO, X, ...) MACRO(X) FE96(MACRO, __VA_ARGS__)
#define FE98(MACRO, X, ...) MACRO(X) FE97(MACRO, __VA_ARGS__)
#define FE99(MACRO, X, ...) MACRO(X) FE98(MACRO, __VA_ARGS__)

// Expansion based on argument count
#define FOR_EACH_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,  \
        _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, \
        _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, \
        _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, \
        _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, IMPL, ...)                                   \
    IMPL

/**
 * @brief The `FOR_EACH` macro calls `MACRO` on each argument passed in.
 *
 */
#define FOR_EACH(MACRO, ...)                                                                                       \
    FOR_EACH_IMPL(_0, ##__VA_ARGS__, FE99, FE98, FE97, FE96, FE95, FE94, FE93, FE92, FE91, FE90, FE89, FE88, FE87, \
            FE86, FE85, FE84, FE83, FE82, FE81, FE80, FE79, FE78, FE77, FE76, FE75, FE74, FE73, FE72, FE71, FE70,  \
            FE69, FE68, FE67, FE66, FE65, FE64, FE63, FE62, FE61, FE60, FE59, FE58, FE57, FE56, FE55, FE54, FE53,  \
            FE52, FE51, FE50, FE49, FE48, FE47, FE46, FE45, FE44, FE43, FE42, FE41, FE40, FE39, FE38, FE37, FE36,  \
            FE35, FE34, FE33, FE32, FE31, FE30, FE29, FE28, FE27, FE26, FE25, FE24, FE23, FE22, FE21, FE20, FE19,  \
            FE18, FE17, FE16, FE15, FE14, FE13, FE12, FE11, FE10, FE9, FE8, FE7, FE6, FE5, FE4, FE3, FE2, FE1,     \
            FE0)(MACRO, ##__VA_ARGS__)

// FEI (FOR_EACH_I) macros to handle up to 19 arguments
#define FEI0(MACRO, DATA)
#define FEI1(MACRO, DATA, X) MACRO(DATA, X)
#define FEI2(MACRO, DATA, X, ...) MACRO(DATA, X) FEI1(MACRO, DATA, __VA_ARGS__)
#define FEI3(MACRO, DATA, X, ...) MACRO(DATA, X) FEI2(MACRO, DATA, __VA_ARGS__)
#define FEI4(MACRO, DATA, X, ...) MACRO(DATA, X) FEI3(MACRO, DATA, __VA_ARGS__)
#define FEI5(MACRO, DATA, X, ...) MACRO(DATA, X) FEI4(MACRO, DATA, __VA_ARGS__)
#define FEI6(MACRO, DATA, X, ...) MACRO(DATA, X) FEI5(MACRO, DATA, __VA_ARGS__)
#define FEI7(MACRO, DATA, X, ...) MACRO(DATA, X) FEI6(MACRO, DATA, __VA_ARGS__)
#define FEI8(MACRO, DATA, X, ...) MACRO(DATA, X) FEI7(MACRO, DATA, __VA_ARGS__)
#define FEI9(MACRO, DATA, X, ...) MACRO(DATA, X) FEI8(MACRO, DATA, __VA_ARGS__)
#define FEI10(MACRO, DATA, X, ...) MACRO(DATA, X) FEI9(MACRO, DATA, __VA_ARGS__)
#define FEI11(MACRO, DATA, X, ...) MACRO(DATA, X) FEI10(MACRO, DATA, __VA_ARGS__)
#define FEI12(MACRO, DATA, X, ...) MACRO(DATA, X) FEI11(MACRO, DATA, __VA_ARGS__)
#define FEI13(MACRO, DATA, X, ...) MACRO(DATA, X) FEI12(MACRO, DATA, __VA_ARGS__)
#define FEI14(MACRO, DATA, X, ...) MACRO(DATA, X) FEI13(MACRO, DATA, __VA_ARGS__)
#define FEI15(MACRO, DATA, X, ...) MACRO(DATA, X) FEI14(MACRO, DATA, __VA_ARGS__)
#define FEI16(MACRO, DATA, X, ...) MACRO(DATA, X) FEI15(MACRO, DATA, __VA_ARGS__)
#define FEI17(MACRO, DATA, X, ...) MACRO(DATA, X) FEI16(MACRO, DATA, __VA_ARGS__)
#define FEI18(MACRO, DATA, X, ...) MACRO(DATA, X) FEI17(MACRO, DATA, __VA_ARGS__)
#define FEI19(MACRO, DATA, X, ...) MACRO(DATA, X) FEI18(MACRO, DATA, __VA_ARGS__)
#define FEI20(MACRO, DATA, X, ...) MACRO(DATA, X) FEI19(MACRO, DATA, __VA_ARGS__)
#define FEI21(MACRO, DATA, X, ...) MACRO(DATA, X) FEI20(MACRO, DATA, __VA_ARGS__)
#define FEI22(MACRO, DATA, X, ...) MACRO(DATA, X) FEI21(MACRO, DATA, __VA_ARGS__)
#define FEI23(MACRO, DATA, X, ...) MACRO(DATA, X) FEI22(MACRO, DATA, __VA_ARGS__)
#define FEI24(MACRO, DATA, X, ...) MACRO(DATA, X) FEI23(MACRO, DATA, __VA_ARGS__)
#define FEI25(MACRO, DATA, X, ...) MACRO(DATA, X) FEI24(MACRO, DATA, __VA_ARGS__)
#define FEI26(MACRO, DATA, X, ...) MACRO(DATA, X) FEI25(MACRO, DATA, __VA_ARGS__)
#define FEI27(MACRO, DATA, X, ...) MACRO(DATA, X) FEI26(MACRO, DATA, __VA_ARGS__)
#define FEI28(MACRO, DATA, X, ...) MACRO(DATA, X) FEI27(MACRO, DATA, __VA_ARGS__)
#define FEI29(MACRO, DATA, X, ...) MACRO(DATA, X) FEI28(MACRO, DATA, __VA_ARGS__)
#define FEI30(MACRO, DATA, X, ...) MACRO(DATA, X) FEI29(MACRO, DATA, __VA_ARGS__)
#define FEI31(MACRO, DATA, X, ...) MACRO(DATA, X) FEI30(MACRO, DATA, __VA_ARGS__)
#define FEI32(MACRO, DATA, X, ...) MACRO(DATA, X) FEI31(MACRO, DATA, __VA_ARGS__)
#define FEI33(MACRO, DATA, X, ...) MACRO(DATA, X) FEI32(MACRO, DATA, __VA_ARGS__)
#define FEI34(MACRO, DATA, X, ...) MACRO(DATA, X) FEI33(MACRO, DATA, __VA_ARGS__)
#define FEI35(MACRO, DATA, X, ...) MACRO(DATA, X) FEI34(MACRO, DATA, __VA_ARGS__)
#define FEI36(MACRO, DATA, X, ...) MACRO(DATA, X) FEI35(MACRO, DATA, __VA_ARGS__)
#define FEI37(MACRO, DATA, X, ...) MACRO(DATA, X) FEI36(MACRO, DATA, __VA_ARGS__)
#define FEI38(MACRO, DATA, X, ...) MACRO(DATA, X) FEI37(MACRO, DATA, __VA_ARGS__)
#define FEI39(MACRO, DATA, X, ...) MACRO(DATA, X) FEI38(MACRO, DATA, __VA_ARGS__)
#define FEI40(MACRO, DATA, X, ...) MACRO(DATA, X) FEI39(MACRO, DATA, __VA_ARGS__)
#define FEI41(MACRO, DATA, X, ...) MACRO(DATA, X) FEI40(MACRO, DATA, __VA_ARGS__)
#define FEI42(MACRO, DATA, X, ...) MACRO(DATA, X) FEI41(MACRO, DATA, __VA_ARGS__)
#define FEI43(MACRO, DATA, X, ...) MACRO(DATA, X) FEI42(MACRO, DATA, __VA_ARGS__)
#define FEI44(MACRO, DATA, X, ...) MACRO(DATA, X) FEI43(MACRO, DATA, __VA_ARGS__)
#define FEI45(MACRO, DATA, X, ...) MACRO(DATA, X) FEI44(MACRO, DATA, __VA_ARGS__)
#define FEI46(MACRO, DATA, X, ...) MACRO(DATA, X) FEI45(MACRO, DATA, __VA_ARGS__)
#define FEI47(MACRO, DATA, X, ...) MACRO(DATA, X) FEI46(MACRO, DATA, __VA_ARGS__)
#define FEI48(MACRO, DATA, X, ...) MACRO(DATA, X) FEI47(MACRO, DATA, __VA_ARGS__)
#define FEI49(MACRO, DATA, X, ...) MACRO(DATA, X) FEI48(MACRO, DATA, __VA_ARGS__)
#define FEI50(MACRO, DATA, X, ...) MACRO(DATA, X) FEI49(MACRO, DATA, __VA_ARGS__)
#define FEI51(MACRO, DATA, X, ...) MACRO(DATA, X) FEI50(MACRO, DATA, __VA_ARGS__)
#define FEI52(MACRO, DATA, X, ...) MACRO(DATA, X) FEI51(MACRO, DATA, __VA_ARGS__)
#define FEI53(MACRO, DATA, X, ...) MACRO(DATA, X) FEI52(MACRO, DATA, __VA_ARGS__)
#define FEI54(MACRO, DATA, X, ...) MACRO(DATA, X) FEI53(MACRO, DATA, __VA_ARGS__)
#define FEI55(MACRO, DATA, X, ...) MACRO(DATA, X) FEI54(MACRO, DATA, __VA_ARGS__)
#define FEI56(MACRO, DATA, X, ...) MACRO(DATA, X) FEI55(MACRO, DATA, __VA_ARGS__)
#define FEI57(MACRO, DATA, X, ...) MACRO(DATA, X) FEI56(MACRO, DATA, __VA_ARGS__)
#define FEI58(MACRO, DATA, X, ...) MACRO(DATA, X) FEI57(MACRO, DATA, __VA_ARGS__)
#define FEI59(MACRO, DATA, X, ...) MACRO(DATA, X) FEI58(MACRO, DATA, __VA_ARGS__)
#define FEI60(MACRO, DATA, X, ...) MACRO(DATA, X) FEI59(MACRO, DATA, __VA_ARGS__)
#define FEI61(MACRO, DATA, X, ...) MACRO(DATA, X) FEI60(MACRO, DATA, __VA_ARGS__)
#define FEI62(MACRO, DATA, X, ...) MACRO(DATA, X) FEI61(MACRO, DATA, __VA_ARGS__)
#define FEI63(MACRO, DATA, X, ...) MACRO(DATA, X) FEI62(MACRO, DATA, __VA_ARGS__)
#define FEI64(MACRO, DATA, X, ...) MACRO(DATA, X) FEI63(MACRO, DATA, __VA_ARGS__)
#define FEI65(MACRO, DATA, X, ...) MACRO(DATA, X) FEI64(MACRO, DATA, __VA_ARGS__)
#define FEI66(MACRO, DATA, X, ...) MACRO(DATA, X) FEI65(MACRO, DATA, __VA_ARGS__)
#define FEI67(MACRO, DATA, X, ...) MACRO(DATA, X) FEI66(MACRO, DATA, __VA_ARGS__)
#define FEI68(MACRO, DATA, X, ...) MACRO(DATA, X) FEI67(MACRO, DATA, __VA_ARGS__)
#define FEI69(MACRO, DATA, X, ...) MACRO(DATA, X) FEI68(MACRO, DATA, __VA_ARGS__)
#define FEI70(MACRO, DATA, X, ...) MACRO(DATA, X) FEI69(MACRO, DATA, __VA_ARGS__)
#define FEI71(MACRO, DATA, X, ...) MACRO(DATA, X) FEI70(MACRO, DATA, __VA_ARGS__)
#define FEI72(MACRO, DATA, X, ...) MACRO(DATA, X) FEI71(MACRO, DATA, __VA_ARGS__)
#define FEI73(MACRO, DATA, X, ...) MACRO(DATA, X) FEI72(MACRO, DATA, __VA_ARGS__)
#define FEI74(MACRO, DATA, X, ...) MACRO(DATA, X) FEI73(MACRO, DATA, __VA_ARGS__)
#define FEI75(MACRO, DATA, X, ...) MACRO(DATA, X) FEI74(MACRO, DATA, __VA_ARGS__)
#define FEI76(MACRO, DATA, X, ...) MACRO(DATA, X) FEI75(MACRO, DATA, __VA_ARGS__)
#define FEI77(MACRO, DATA, X, ...) MACRO(DATA, X) FEI76(MACRO, DATA, __VA_ARGS__)
#define FEI78(MACRO, DATA, X, ...) MACRO(DATA, X) FEI77(MACRO, DATA, __VA_ARGS__)
#define FEI79(MACRO, DATA, X, ...) MACRO(DATA, X) FEI78(MACRO, DATA, __VA_ARGS__)
#define FEI80(MACRO, DATA, X, ...) MACRO(DATA, X) FEI79(MACRO, DATA, __VA_ARGS__)
#define FEI81(MACRO, DATA, X, ...) MACRO(DATA, X) FEI80(MACRO, DATA, __VA_ARGS__)
#define FEI82(MACRO, DATA, X, ...) MACRO(DATA, X) FEI81(MACRO, DATA, __VA_ARGS__)
#define FEI83(MACRO, DATA, X, ...) MACRO(DATA, X) FEI82(MACRO, DATA, __VA_ARGS__)
#define FEI84(MACRO, DATA, X, ...) MACRO(DATA, X) FEI83(MACRO, DATA, __VA_ARGS__)
#define FEI85(MACRO, DATA, X, ...) MACRO(DATA, X) FEI84(MACRO, DATA, __VA_ARGS__)
#define FEI86(MACRO, DATA, X, ...) MACRO(DATA, X) FEI85(MACRO, DATA, __VA_ARGS__)
#define FEI87(MACRO, DATA, X, ...) MACRO(DATA, X) FEI86(MACRO, DATA, __VA_ARGS__)
#define FEI88(MACRO, DATA, X, ...) MACRO(DATA, X) FEI87(MACRO, DATA, __VA_ARGS__)
#define FEI89(MACRO, DATA, X, ...) MACRO(DATA, X) FEI88(MACRO, DATA, __VA_ARGS__)
#define FEI90(MACRO, DATA, X, ...) MACRO(DATA, X) FEI89(MACRO, DATA, __VA_ARGS__)
#define FEI91(MACRO, DATA, X, ...) MACRO(DATA, X) FEI90(MACRO, DATA, __VA_ARGS__)
#define FEI92(MACRO, DATA, X, ...) MACRO(DATA, X) FEI91(MACRO, DATA, __VA_ARGS__)
#define FEI93(MACRO, DATA, X, ...) MACRO(DATA, X) FEI92(MACRO, DATA, __VA_ARGS__)
#define FEI94(MACRO, DATA, X, ...) MACRO(DATA, X) FEI93(MACRO, DATA, __VA_ARGS__)
#define FEI95(MACRO, DATA, X, ...) MACRO(DATA, X) FEI94(MACRO, DATA, __VA_ARGS__)
#define FEI96(MACRO, DATA, X, ...) MACRO(DATA, X) FEI95(MACRO, DATA, __VA_ARGS__)
#define FEI97(MACRO, DATA, X, ...) MACRO(DATA, X) FEI96(MACRO, DATA, __VA_ARGS__)
#define FEI98(MACRO, DATA, X, ...) MACRO(DATA, X) FEI97(MACRO, DATA, __VA_ARGS__)
#define FEI99(MACRO, DATA, X, ...) MACRO(DATA, X) FEI98(MACRO, DATA, __VA_ARGS__)

/**
 * @brief The `FOR_EACH` macro calls `MACRO` on each argument passed in.
 *
 */
#define FOR_EACH_I(MACRO, DATA, ...)                                                                                 \
    FOR_EACH_IMPL(_0, ##__VA_ARGS__, FEI99, FEI98, FEI97, FEI96, FEI95, FEI94, FEI93, FEI92, FEI91, FEI90, FEI89,    \
            FEI88, FEI87, FEI86, FEI85, FEI84, FEI83, FEI82, FEI81, FEI80, FEI79, FEI78, FEI77, FEI76, FEI75, FEI74, \
            FEI73, FEI72, FEI71, FEI70, FEI69, FEI68, FEI67, FEI66, FEI65, FEI64, FEI63, FEI62, FEI61, FEI60, FEI59, \
            FEI58, FEI57, FEI56, FEI55, FEI54, FEI53, FEI52, FEI51, FEI50, FEI49, FEI48, FEI47, FEI46, FEI45, FEI44, \
            FEI43, FEI42, FEI41, FEI40, FEI39, FEI38, FEI37, FEI36, FEI35, FEI34, FEI33, FEI32, FEI31, FEI30, FEI29, \
            FEI28, FEI27, FEI26, FEI25, FEI24, FEI23, FEI22, FEI21, FEI20, FEI19, FEI18, FEI17, FEI16, FEI15, FEI14, \
            FEI13, FEI12, FEI11, FEI10, FEI9, FEI8, FEI7, FEI6, FEI5, FEI4, FEI3, FEI2, FEI1,                        \
            FEI0)(MACRO, DATA, ##__VA_ARGS__)

/**
 * @brief The `GLUE` macro combines two strings together.
 *
 */
#define GLUE(left, right) left##right

/**
 * @brief The `DISPATCH_GLUE` macro enables a two-step expansion of the left and right arguments before gluing,
 * useful for VA_NARGS for macro selection.
 *
 */
#define DISPATCH_GLUE(left, right) GLUE(left, right)

// Implementation for VA_NARGS macro
#define VA_NARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,  \
        _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, \
        _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, \
        _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, \
        _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, N, ...)                                      \
    N

/**
 * @brief The `VA_NARGS` returns the number of arguments when in range 0 to 19.
 *
 */
#define VA_NARGS(...)                                                                                                \
    VA_NARGS_IMPL(_0, ##__VA_ARGS__, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, \
            79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54,  \
            53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28,  \
            27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#endif
