#pragma once

#include "pch.h"

namespace tron
{
    enum GLTypeEnum
    {
        GT_INT8 = GL_BYTE,
        GT_UINT8 = GL_UNSIGNED_BYTE,
        GT_INT16 = GL_SHORT,
        GT_UINT16 = GL_UNSIGNED_SHORT,
        GT_INT32 = GL_INT,
        GT_UINT32 = GL_UNSIGNED_INT,
        GT_FP32 = GL_FLOAT,
        GT_FP64 = GL_DOUBLE
    };


    template<typename T>
    struct GLBuiltinType;

    template<>
    struct GLBuiltinType<char>
    {
        static constexpr GLTypeEnum Value = GT_INT8;
    };

    template<>
    struct GLBuiltinType<unsigned char>
    {
        static constexpr GLTypeEnum Value = GT_INT8;
    };

    template<>
    struct GLBuiltinType<short>
    {
        static constexpr GLTypeEnum Value = GT_INT16;
    };

    template<>
    struct GLBuiltinType<unsigned short>
    {
        static constexpr GLTypeEnum Value = GT_UINT16;
    };

    template<>
    struct GLBuiltinType<int>
    {
        static constexpr GLTypeEnum Value = GT_INT32;
    };

    template<>
    struct GLBuiltinType<unsigned int>
    {
        static constexpr GLTypeEnum Value = GT_UINT32;
    };

    template<>
    struct GLBuiltinType<float>
    {
        static constexpr GLTypeEnum Value = GT_FP32;
    };

    template<>
    struct GLBuiltinType<double>
    {
        static constexpr GLTypeEnum Value = GT_FP64;
    };


    template<typename>
    struct GLComplexType;

    template<
        template<glm::length_t, typename, glm::qualifier> typename V,
        glm::length_t L, typename T, glm::qualifier Q>
        requires std::is_assignable_v<glm::vec<L, T, Q>, V<L, T, Q>>
    struct GLComplexType<V<L, T, Q>>
    {
        static constexpr size_t Count = L;
        using Type                    = T;
    };

    template<
        template<glm::length_t, glm::length_t, typename, glm::qualifier> typename V,
        glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
        requires std::is_assignable_v<glm::mat<C, R, T, Q>, V<C, R, T, Q>>
    struct GLComplexType<V<C, R, T, Q>>
    {
        static constexpr size_t Count = C * R;
        using Type                    = T;
    };

    template<
        template<typename, glm::qualifier> typename V,
        typename T, glm::qualifier Q>
        requires std::is_assignable_v<glm::qua<T, Q>, V<T, Q>>
    struct GLComplexType<V<T, Q>>
    {
        static constexpr size_t Count = 4;
        using Type                    = T;
    };


    template<class T, std::size_t = sizeof(T)>
    std::true_type IsComplete_(T*);

    std::false_type IsComplete_(...);

    template<class T>
    concept IsComplete = decltype(IsComplete_(std::declval<T*>()))::value;

    template<typename>
    struct GLType;

    template<typename T> requires IsComplete<GLBuiltinType<T>>
    struct GLType<T>
    {
        static constexpr size_t Size         = sizeof(T);
        static constexpr size_t Count        = 1;
        static constexpr GLTypeEnum TypeEnum = GLBuiltinType<T>::Value;
    };

    template<typename T> requires (!IsComplete<GLBuiltinType<T>>)
    struct GLType<T>
    {
        static constexpr size_t Size         = sizeof(T);
        static constexpr size_t Count        = GLComplexType<T>::Count;
        static constexpr GLTypeEnum TypeEnum = GLBuiltinType<typename GLComplexType<T>::Type>::Value;
    };
}
