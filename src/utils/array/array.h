#pragma once

#include <stdlib.h>

#include "../defines.h"

#define arraydef(type_name) \
    type(type_name##_array) { \
        int length; \
        type_name* values; \
        type_name method(type_name##_array, get, int index); \
        void method(type_name##_array, add, type_name value); \
        type_name method(type_name##_array, set, int index, type_name value); \
        void method(type_name##_array, insert, int index, type_name value); \
        type_name method(type_name##_array, remove, int index); \
        void method0(type_name##_array, clear); \
        destruct(type_name##_array); \
    };

#define impl_arraydef(type_name) \
    private type_name impl_method(type_name##_array, get, int index) { \
        return obj->values[index]; \
    } \
    private void impl_method(type_name##_array, add, type_name value) { \
        obj->length++; \
        obj->values = realloc(obj->values, obj->length * sizeof(type_name)); \
        obj->values[obj->length - 1] = value; \
    } \
    private type_name impl_method(type_name##_array, set, int index, type_name value) { \
        type_name old = obj->values[index]; \
        obj->values[index] = value; \
        return old; \
    } \
    private void impl_method(type_name##_array, insert, int index, type_name value) { \
        obj->length++; \
        obj->values = realloc(obj->values, obj->length * sizeof(type_name)); \
        for (int i = obj->length - 1; i > index; i--) { \
            obj->values[i] = obj->values[i - 1]; \
        } \
        obj->values[index] = value; \
    } \
    private type_name impl_method(type_name##_array, remove, int index) { \
        type_name value = obj->values[index]; \
        for (int i = index; i < obj->length - 1; i++) { \
            obj->values[i] = obj->values[i + 1]; \
        } \
        obj->length--; \
        obj->values = realloc(obj->values, obj->length * sizeof(type_name)); \
        return value; \
    } \
    private void impl_method0(type_name##_array, clear) { \
        free(obj->values); \
        obj->length = 0; \
        obj->values = NULL; \
    } \
    destructor(type_name##_array) { \
        free(obj->values); \
    } \
    constructor(type_name##_array) { \
        type_name##_array obj = malloc(sizeoftype(type_name##_array)); \
        obj->length = 0; \
        obj->values = NULL; \
        set_impl(type_name##_array, obj, get); \
        set_impl(type_name##_array, obj, add); \
        set_impl(type_name##_array, obj, set); \
        set_impl(type_name##_array, obj, insert); \
        set_impl(type_name##_array, obj, remove); \
        set_impl(type_name##_array, obj, clear); \
        set_impl(type_name##_array, obj, __destruct); \
        return obj; \
    }

arraydef(char);
arraydef(int);
arraydef(float);
arraydef(long);
arraydef(double);
