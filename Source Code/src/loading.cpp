#include <game.hpp>

extern "C" {
    const char* I_kinoko = "I_kinoko";
    const char* I_fireflower = "I_fireflower";
    const char* I_iceflower = "I_iceflower";
    const char* I_star = "I_star";
    const char* I_propeller = "I_propeller";
    const char* I_penguin = "I_penguin";
    const char* I_hammer = "I_hammer";
}

const char* LoadListArray[] = {
    "Mario",
    "Luigi",
    "Kinopio",
    "Yoshi",
    "P_rcha",
    "L_rcha",
    "K_rcha",
    "Y_rcha",
    "Y_TexGreen",
    "Y_TexRed",
    "Y_TexYellow",
    "Y_TexBlue",
    "obj_coin",
    "balloon",
    I_kinoko,
    I_fireflower,
    I_iceflower,
    I_star,
    I_propeller,
    I_penguin,
    "I_yoshi_egg",
    "block_tsuta",
    "teresa",
    "jump_step",
    "ice",
    "ice_piece",
    "obj_dokan",
    "obj_door",
    "obj_kusa",
    "obj_hana",
    "obj_hana_daishizen",
    "block_jump",
    "obj_chikuwa_block",
    "lift_rakka_ashiba",
    "Mask",
    NULL
};

kmBranchDefCpp(0x8091ec50, NULL, int, void) {
    dResMng_c::instance->setRes("Object", LoadListArray, 35, (void*)0x0);
    return 1;
}