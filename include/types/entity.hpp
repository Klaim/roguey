//==================================================================================================
/*
  Roguey
  Copyright : Joel FALCOU
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once
#include <cstdint>
#include <string>

using EntityID = std::uint32_t;

struct Stats
{
  std::string archetype;
  int hp, max_hp, mana, max_mana, damage, xp, level, fov_range, gold;
};
