#ifndef __LOG_HPP__
#define __LOG_HPP__
#include <iostream>
#include <libgen.h>
#include <stdarg.h>
#include <string.h>
#include <string>

inline std::string format__(const char *format, ...)
{
    char buf[4096];
    va_list list;
    va_start(list, format);
    vsnprintf(buf, 4096, format, list);
    va_end(list);
    return std::string(buf);
}

inline std::string basename__(const char *name)
{
    char buffer[4096];
    strncpy(buffer, name, 4096);
    return std::string(basename(buffer));
}

#define LOG(...)                                           \
    std::cerr << format__(__VA_ARGS__) << " "              \
              << basename__(__FILE__) << ":" << __LINE__   \
              << std::endl;
#endif