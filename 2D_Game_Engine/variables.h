#ifndef VARIABLES_H
#define VARIABLES_H

#pragma once

//Physics enums
enum phys_state { obj_static, obj_dynamic, obj_physics };

//Gamestate enums
enum game_state { gs_menu, gs_pausemenu, gs_game };
enum game_leveltype { gs_bullethell, gs_overworld };
enum game_camerastate { camera_fixed, camera_follow, camera_dynamic, camera_split }; //TODO: Change
enum game_keyfocus { gs_keyboard_game, gs_keyboard_menu, gs_keyboard_console };

//Texture enums
enum tex_type { tex_static, tex_dynamic, tex_animated };

//Console enums

#endif