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

namespace roguey
{
  using EntityID = std::uint64_t;

  struct Stats
  {
    std::string archetype;
    int hp, max_hp, mana, max_mana, damage, xp, level, fov_range, gold;
    int action_delay = 10, action_timer = 0;
  };
}
