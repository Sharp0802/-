#pragma once

namespace tron
{
    struct Global
    {
        static std::string Path;

        static std::string GetPath(const std::string& local);
    };
}
