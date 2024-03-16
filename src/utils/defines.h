#pragma once

#define private static
#define override // empty (used for readability)

#define function(function_name, ...) (*function_name)(__VA_ARGS__)

#define type(type_name, ...) \
    typedef struct __##type_name __TYPE__; \
    __TYPE__ new_##type_name(__VA_ARGS__); \
    struct __##type_name
#define method(method_name, ...) (*method_name)(__TYPE__ obj, __VA_ARGS__)

#define constructor(type_name, ...) type_name new_##type_name(__VA_ARGS__)
#define new(type_name, ...) new_##type_name(__VA_ARGS__)

#define get_impl(type_name, method_name) impl_##type_name##_##method_name
#define impl_function(type_name, method_name, ...) get_impl(type_name, method_name)(__VA_ARGS__)
#define impl_method(type_name, method_name, ...) impl_function(type_name, method_name, type_name obj, __VA_ARGS__)

#define call(obj, method_name, ...) obj->method_name(obj, __VA_ARGS__)