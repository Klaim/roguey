#include "renderer.hpp"
#include <ncurses.h>
#include <locale.h>
#include <filesystem>

namespace fs = std::filesystem;

Renderer::Renderer() {
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
}

Renderer::~Renderer() {
    endwin();
}

void Renderer::init_colors(ScriptEngine& scripts) {
    sol::table color_table = scripts.lua["game_colors"];
    for (size_t i = 1; i <= color_table.size(); ++i) {
        sol::table entry = color_table[i];
        int id = static_cast<int>(i);
        init_pair(id, entry[1], entry[2]);
        scripts.lua[entry[3]] = id;
    }
}

void Renderer::clear_screen() {
    clear();
}

void Renderer::refresh_screen() {
    refresh();
}

void Renderer::show_error(const std::string& msg) {
    clear();
    attron(A_BOLD);
    mvprintw(10, 10, "CRITICAL ERROR:");
    attroff(A_BOLD);
    mvprintw(12, 10, "%s", msg.c_str());
    mvprintw(14, 10, "[ Press any key to exit ]");
    refresh();
    getch();
}

void Renderer::draw_borders(int w, int h) {
    attron(COLOR_PAIR(0) | A_BOLD);
    mvaddch(0, 0, ACS_ULCORNER);
    mvaddch(0, w + 1, ACS_URCORNER);
    mvaddch(h + 1, 0, ACS_LLCORNER);
    mvaddch(h + 1, w + 1, ACS_LRCORNER);

    for (int x = 1; x <= w; ++x) {
        mvaddch(0, x, ACS_HLINE);
        mvaddch(h + 1, x, ACS_HLINE);
        mvaddch(h - 4, x, ACS_HLINE);
    }

    for (int y = 1; y <= h; ++y) {
        mvaddch(y, 0, ACS_VLINE);
        mvaddch(y, w + 1, ACS_VLINE);
    }

    mvaddch(h - 4, 0, ACS_LTEE);
    mvaddch(h - 4, w + 1, ACS_RTEE);
    attroff(COLOR_PAIR(0) | A_BOLD);
}

void Renderer::draw_log(const MessageLog& log, int start_y, int max_row, int max_col) {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int limit_y = (max_row < max_y) ? max_row : max_y;
    int visible_lines = limit_y - start_y + 1;

    if (visible_lines <= 0) return;

    int msg_count = (int)log.messages.size();
    int start_index = 0;
    if (msg_count > visible_lines) {
        start_index = msg_count - visible_lines;
    }

    int draw_y = start_y;
    for (int i = start_index; i < msg_count; ++i) {
        if (draw_y > limit_y) break;
        wmove(stdscr, draw_y, 2);
        int available_width = max_col - 2;
        std::string txt = log.messages[i].text;
        if ((int)txt.length() > available_width - 2) {
            txt = txt.substr(0, available_width - 2);
        }
        attron(COLOR_PAIR(static_cast<short>(log.messages[i].color)));
        printw("> %s", txt.c_str());
        attroff(COLOR_PAIR(static_cast<short>(log.messages[i].color)));

        // Clear rest of the line
        int cx, cy;
        getyx(stdscr, cy, cx);
        while (cx <= max_col) { addch(' '); cx++; }
        draw_y++;
    }
}

void Renderer::draw_dungeon(const Dungeon& map, const Registry& reg, const MessageLog& log,
                            int player_id, int depth, int wall_color, int floor_color) {
    int ui_width = map.width;
    int ui_height = map.height + 7;
    draw_borders(ui_width, ui_height);

    int wall_pair = wall_color;
    int floor_pair = floor_color;

    for (int y = 0; y < map.height; ++y) {
        for (int x = 0; x < map.width; ++x) {
            if (map.visible_tiles.count({x, y})) {
                attron(COLOR_PAIR(map.grid[y][x] == '#' ? wall_pair : floor_pair));
                mvaddch(y + 1, x + 1, map.grid[y][x]);
                attroff(COLOR_PAIR(map.grid[y][x] == '#' ? wall_pair : floor_pair));
            } else if (map.explored[y][x]) {
                attron(COLOR_PAIR(8));
                mvaddch(y + 1, x + 1, map.grid[y][x]);
                attroff(COLOR_PAIR(8));
            }
        }
    }

    for (auto const& [id, r] : reg.renderables) {
        Position p = reg.positions.at(id);
        if (id == player_id || map.visible_tiles.count(p)) {
            attron(COLOR_PAIR((short)r.color));
            mvaddch(p.y + 1, p.x + 1, r.glyph);
            attroff(COLOR_PAIR((short)r.color));
        }
    }

    if (reg.stats.contains(player_id)) {
        auto s = reg.stats.at(player_id);
        mvprintw(map.height + 2, 2, "HP: %d/%d | MP: %d/%d | Depth: %d | [I]nv [C]har",
                 s.hp, s.max_hp, s.mana, s.max_mana, depth);
    }

    draw_log(log, map.height + 4, ui_height, ui_width);
}

void Renderer::animate_projectile(int x, int y, char glyph, ColorPair color) {
    attron(COLOR_PAIR(static_cast<short>(color)) | A_BOLD);
    mvaddch(y + 1, x + 1, glyph);
    attroff(COLOR_PAIR(static_cast<short>(color)) | A_BOLD);
    refresh();
    napms(50);
}

// UPDATED: Now draws borders and log
void Renderer::draw_inventory(const std::vector<ItemTag>& inventory, const MessageLog& log, int width, int height) {
    int ui_width = width;
    int ui_height = height + 7;
    draw_borders(ui_width, ui_height);

    attron(A_BOLD);
    mvprintw(2, 4, "--- INVENTORY ---");
    attroff(A_BOLD);

    if (inventory.empty()) {
        mvprintw(4, 6, "(Empty)");
    } else {
        for (size_t i = 0; i < inventory.size(); ++i) {
            // Ensure we don't overflow into the log area or stats line
            if (4 + i >= (size_t)height + 2) break;
            mvprintw(4 + i, 6, "[%zu] %s", i + 1, inventory[i].name.c_str());
        }
    }

    mvprintw(height + 2, 2, "[1-9] Use Item | [I/ESC] Close Inventory");
    draw_log(log, height + 4, ui_height, ui_width);
}

// UPDATED: Now draws borders and log
void Renderer::draw_stats(const Registry& reg, int player_id, std::string player_name, const MessageLog& log, int width, int height) {
    int ui_width = width;
    int ui_height = height + 7;
    draw_borders(ui_width, ui_height);

    if (!reg.stats.contains(player_id)) return;
    auto s = reg.stats.at(player_id);

    attron(A_BOLD);
    mvprintw(2, 4, "--- CHARACTER SHEET ---");
    attroff(A_BOLD);

    mvprintw(4, 6, "Name:   %s", player_name.c_str());
    mvprintw(5, 6, "Level:  %d", s.level);
    mvprintw(6, 6, "XP:     %d", s.xp);
    mvprintw(8, 6, "HP:     %d / %d", s.hp, s.max_hp);
    mvprintw(9, 6, "Mana:   %d / %d", s.mana, s.max_mana);
    mvprintw(10, 6,"Damage: %d", s.damage);
    mvprintw(11, 6,"FOV:    %d", s.fov_range);

    mvprintw(height + 2, 2, "[C/ESC] Close Stats");
    draw_log(log, height + 4, ui_height, ui_width);
}

void Renderer::draw_character_creation_header() {
    clear();
    mvprintw(5, 10, "--- CHARACTER CREATION ---");
    mvprintw(7, 10, "Enter your name: ");
    refresh();
}

void Renderer::draw_class_selection(const std::vector<std::string>& class_paths, int selection) {
    clear();
    mvprintw(5, 10, "--- SELECT YOUR CLASS ---");
    for (size_t i = 0; i < class_paths.size(); ++i) {
        if ((int)i == selection) attron(A_REVERSE);
        std::string name = fs::path(class_paths[i]).stem().string();
        mvprintw(7 + i, 12, "[ %s ]", name.c_str());
        attroff(A_REVERSE);
    }
    refresh();
}

void Renderer::draw_game_over() {
    clear();
    attron(A_BOLD | COLOR_PAIR(static_cast<short>(ColorPair::Orc)));
    mvprintw(10, 30, " !!! YOU DIED !!! ");
    attroff(A_BOLD | COLOR_PAIR(static_cast<short>(ColorPair::Orc)));
    mvprintw(15, 20, "Press 'r' to Restart, 'q' to Quit");
    refresh();
}

void Renderer::draw_victory() {
    clear();
    attron(A_BOLD | COLOR_PAIR(static_cast<short>(ColorPair::Gold)));
    mvprintw(10, 30, " !!! VICTORY !!! ");
    attroff(A_BOLD | COLOR_PAIR(static_cast<short>(ColorPair::Gold)));
    mvprintw(15, 20, "Press 'c' to Continue, 'q' to Quit");
    refresh();
}