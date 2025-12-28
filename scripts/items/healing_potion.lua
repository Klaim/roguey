--==================================================================================================
--  Roguey
--  Copyright : Joel FALCOU
--  SPDX-License-Identifier: MIT
--==================================================================================================

item_data = {
    name = "Healing Potion",
    glyph = "!",
    color = item_hp_potion,
    kind = "consumable"
}

function on_pick(stats, log)
    log:add("You picked up a Healing Potion",ui_hp)
    return true
end

function on_use(stats, log)
    local heal_amount = 20
    stats.hp = math.min(stats.max_hp, stats.hp + heal_amount)
    log:add("You drink the potion and feel better!")
    return true
end
