--==================================================================================================
--  Roguey
--  Copyright : Joel FALCOU
--  SPDX-License-Identifier: MIT
--==================================================================================================

item_data = {
    name = "Gold",
    glyph = "$",
    color = item_gold,
    kind  = "gold"
}

function on_pick(stats, log)
    stats.gold = stats.gold + 10
    log:add("You found 10 gold!")
    return false
end