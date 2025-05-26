#pragma once
#include <rttr/registration>

#define MAKE_PUBLIC(CLASS, MEMBER)                                                              \
    namespace {                                                                                 \
        struct AutoRegister_##MEMBER##__LINE__ {                                                \
            AutoRegister_##MEMBER##__LINE__() {                                                 \
                rttr::registration::class_<CLASS>(#CLASS)                                       \
                    .property(#MEMBER, &CLASS::MEMBER);                                         \
            }                                                                                   \
        };                                                                                      \
        static AutoRegister_##MEMBER##__LINE__ autoRegister_##MEMBER##__LINE__;                 \
    }

// Internal helper to create a unique symbol
#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)

// Main macro
#define MAKE_PUBLIC_WITH_BASE(CLASS, BASE, MEMBER)                                   \
    namespace {                                                                      \
        struct CONCAT(AutoRegister_, CONCAT(MEMBER, __LINE__)) {                     \
            CONCAT(AutoRegister_, CONCAT(MEMBER, __LINE__))() {                      \
                rttr::registration::class_<CLASS>(#CLASS)                            \
                    .property(#MEMBER, &CLASS::MEMBER);                              \
            }                                                                        \
        };                                                                           \
        static CONCAT(AutoRegister_, CONCAT(MEMBER, __LINE__))                       \
            CONCAT(autoReg_, CONCAT(MEMBER, __LINE__));                              \
    }

#define ENABLE_REFLECTION() RTTR_ENABLE()

// Macro with a base class parameter
#define ENABLE_REFLECTION_WITH_BASE(BASE) RTTR_ENABLE(BASE)