//==================================================================================================
/*
  Roguey
  Copyright : Joel FALCOU
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once
#include "types.hpp"
#include <map>
#include <string>
#include <vector>

namespace roguey
{
  struct Renderable
  {
    char glyph;
    std::string color;
  };

  struct Projectile
  {
    int dx, dy;
    int damage;
    int range;
    EntityID owner;
    int action_delay = 2;
    int action_timer = 0;
  };

  class Registry
  {
  public:
    std::map<EntityID, Position> positions;
    std::map<EntityID, Renderable> renderables;
    std::map<EntityID, Stats> stats;
    std::map<EntityID, ItemTag> items;
    std::map<EntityID, std::string> names;
    std::map<EntityID, std::string> script_paths;
    std::map<EntityID, std::string> monster_types;
    std::map<EntityID, Projectile> projectiles;

    std::vector<EntityID> monsters;
    EntityID player_id = 0;
    EntityID boss_id = 0;
    EntityID next_id = 1;
    std::string player_name = "Hero";
    std::string player_class_script;

    EntityID create_entity() { return next_id++; }

    void clear();
    void destroy_entity(EntityID id);
  };
}
