#pragma once

#define as_string__(d) #d
#define as_string_(d) as_string__(d)

#define pout(...) std::println(                                 \
    std::cout,                                                  \
    "[INF/" __TIME__ "/" __FILE__ ":" as_string_(__LINE__) "] " \
    __VA_ARGS__)

#define perr(...) std::println(                                 \
    std::cerr,                                                  \
    "[ERR/" __TIME__ "/" __FILE__ ":" as_string_(__LINE__) "] " \
    __VA_ARGS__)
