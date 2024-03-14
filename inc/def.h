#ifndef TRON_DEF_H
#define TRON_DEF_H

#if TRON_RELEASE
#define ASSERT(a)
#else
#define ASSERT(a) assert(a)
#endif
#include <memory>

namespace tron
{
    template<typename T>
    using ptr = std::shared_ptr<T>;    
}

#endif //TRON_DEF_H
