#include "global.h"

namespace tron
{
    std::string Global::Path;

    std::string Global::GetPath(const std::string& local)
    {
        const std::filesystem::path root = Path;
        const std::filesystem::path local_ = local;
        return (root / local_).string();
    }
}
