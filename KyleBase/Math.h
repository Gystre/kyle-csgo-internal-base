#pragma once

constexpr auto degreesToRadians = [](float degrees) constexpr noexcept { return degrees * M_PI / 180.0f; };
constexpr auto radiansToDegrees = [](float radians) constexpr noexcept { return radians * 180.0f / M_PI; };

namespace Math
{

}