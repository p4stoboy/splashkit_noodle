#include "splashkit.h"
#include "XOR.h"
#include "Settings.h"
#include "Util.h"
#include "Block.h"


enum GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

struct GameVals {
    int BLOCK_FRAME_MOD = MAX_BLOCK_FRAME_MOD;
    float BLOCK_VEL = MIN_BLOCK_VEL;
    float BLOCK_ACC = MIN_BLOCK_ACC;
};

struct Input {
    key_code left = LEFT_KEY;
    key_code right = RIGHT_KEY;
    key_code shoot = SPACE_KEY;
};

int main()
{
    // instantiate game state, values, input controls, and random number generator
    open_window("CuteBlocks", 500, 800);
    hide_mouse();
    GameState state = MENU;
    GameVals values;
    Input controls;
    XOR rng = XOR();
    vector<Block> blocks;
    vector<Particle> particles;
    Block player = Block({screen_width() / 2, screen_height() - 20}, {0, 0}, {0, 0}, COLOR_BLACK, 5);
    int frame = 0;

    // game loop
    while (!quit_requested()) {
        process_events();
        clear_screen(color_from_hex("#F7D4C8"));
        if (state == MENU) {
            draw_text("CuteBlocks", COLOR_BLACK, 20, 20);
            draw_text("Press Space to start", COLOR_BLACK, 20, 40);
            if (key_typed(SPACE_KEY)) {
                state = PLAYING;
            }
        }
        else if (state == PLAYING) {
            frame = (frame + 1) % INT32_MAX;
            player.position.x = mouse_x();
            player.position.y = mouse_y();
            bool shouldSpawnBlock = frame % values.BLOCK_FRAME_MOD == 0;
            if (shouldSpawnBlock) {
                values.BLOCK_VEL += 0.001;
                values.BLOCK_ACC += 0.001;
                float size = rng.randomInt(4, 12);
                float x = rng.randomFloat(0, screen_width() - size);
                float y = 0;
                vector_2d vel = {0, rng.randomFloat(MIN_BLOCK_VEL, values.BLOCK_VEL)};
                vector_2d acc = {0, rng.randomFloat(MIN_BLOCK_ACC, values.BLOCK_ACC)};
                color clr = choose(saturated_pastel_colors, 7);
                Block block = Block({x, y}, vel, acc, clr, size);
                blocks.push_back(block);
            }
            if (frame % values.BLOCK_FRAME_MOD * 100 == 0) {
                values.BLOCK_FRAME_MOD = std::max(MIN_BLOCK_FRAME_MOD, values.BLOCK_FRAME_MOD - 1);
            }
            update_blocks(blocks, particles, rng);
            update_particles(particles);
            draw_blocks(blocks);
            draw_particles(particles);
            player.draw();
            for (auto& block : blocks) {
                if (block.check_collision(player)) {
                    state = GAME_OVER;
                }
            }
            draw_text("Score: " + std::to_string(frame), COLOR_BLACK, 20, 20);
        }
        else if (state == GAME_OVER) {
            draw_text("Game Over", COLOR_BLACK, screen_width() / 2 - 50, screen_height() / 2);
            draw_text("Score: " + std::to_string(frame), COLOR_BLACK, screen_width() / 2 - 50, screen_height() / 2 + 30);
            draw_text("Press Space to restart", COLOR_BLACK, screen_width() / 2 - 200, screen_height() - 100);
            if(key_typed(SPACE_KEY)) {
                state = MENU;
                blocks.clear();
                particles.clear();
                values.BLOCK_FRAME_MOD = MAX_BLOCK_FRAME_MOD;
                values.BLOCK_VEL = MIN_BLOCK_VEL;
                values.BLOCK_ACC = MIN_BLOCK_ACC;
                frame = 0;
            }
        }
        refresh_screen(60);
    }
    return 0;
}
