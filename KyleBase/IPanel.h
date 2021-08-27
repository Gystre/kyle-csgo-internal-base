#pragma once

#include <string_view>
#include "VirtualMethod.h"

class IPanel {
public:
    constexpr auto getName(unsigned int panel) noexcept
    {
        return std::string_view{ VirtualMethod::call<const char*, 36>(this, panel) };
    }
};
