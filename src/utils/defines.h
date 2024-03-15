#pragma once

#define private static
#define override // empty (for readability)

#define function(function_name, ...) (*function_name)(__VA_ARGS__)