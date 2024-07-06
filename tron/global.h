#pragma once

#include <pch.h>

namespace tron
{
    struct Global
    {
        static std::string Path;

        static std::string GetPath(const std::string& local);
    };
}
