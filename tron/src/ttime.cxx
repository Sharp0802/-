#include "ttime.h"

namespace tron
{
    float Time::_delta;

    float Time::GetDelta()
    {
        return _delta;
    }

    void TimeManager::Update()
    {
        static float last;
        const auto   current = static_cast<float>(glfwGetTime());
        Time::_delta         = current - last;
        last                 = current;
    }
}
