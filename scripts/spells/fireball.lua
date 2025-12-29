--==================================================================================================
--  Roguey
--  Copyright : Joel FALCOU
--  SPDX-License-Identifier: MIT
--==================================================================================================

spell_data = {
  name = "Fireball",
  mana_cost = 1,
  damage = 400,
  range = 8,
  glyph = "X",
  color = "fx_fire",
  delay = 1
}

function update_projectile(x, y, dx, dy)
  -- Keep going straight
  return dx, dy
end

function on_damage(target, log)
  local dmg = spell_data.damage;
  target.hp = math.max(target.hp - dmg, 0)
  log:add("The " .. spell_data.name .. " burns the " .. target.name .. " for " .. dmg .. " damage(s)", fx_fire)
end

function on_kill(target, log)
  print("[LUA] " .. target.name .. " has been turned to ash!")
end