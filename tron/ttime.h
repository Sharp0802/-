#pragma once

#include "pch.h"

namespace tron
{
    class Time
    {
        friend class TimeManager;

        static float _delta;

    public:
        static float GetDelta();
    };

    class TimeManager
    {
    public:
        static void Update();
    };
}
