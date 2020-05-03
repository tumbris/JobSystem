#pragma once

#include <cstdint>

using JobGroupPriority = std::uint32_t;
constexpr static JobGroupPriority JobGroupDefaultPriority = 0;

using WorkerAffinity = std::size_t; //bitmask
