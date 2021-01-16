#pragma output REGISTER_SP = 0xD000

#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <input.h>
#include <stdlib.h>
#include <intrinsic.h>
#include "int.h"

struct sp1_Rect full_screen = {0, 0, 32, 24};

extern unsigned char bubble_col1[];
extern unsigned char bubble_col2[];

extern unsigned char brick[];
extern unsigned char window[];

struct my_sprite {
    struct sp1_ss *s;
    uint8_t x, y;
};
struct my_sprite bubble; 

struct sp1_cs brick_object;
struct sp1_cs brick_object2;
struct sp1_cs window_object;
struct sp1_update *bricks_update;

// get the player keys input and update our sprite x/y
void get_movement(){

    if (in_key_pressed( IN_KEY_SCANCODE_q )) {
        --bubble.y;
    }
    if (in_key_pressed( IN_KEY_SCANCODE_a )) {
        ++bubble.y;
    }
    if (in_key_pressed( IN_KEY_SCANCODE_o )) {
        --bubble.x;
    }
    if (in_key_pressed( IN_KEY_SCANCODE_p )) {
        ++bubble.x;
    }

}

// create a sprite bubble
void create_bubble() {

    bubble.s = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)bubble_col1, 10);
    sp1_AddColSpr(bubble.s, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)bubble_col2, 10);
    sp1_AddColSpr(bubble.s, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 10);
    bubble.x = 115;
    bubble.y = 84;
}

// create the 8x8 sprite with independent cs structure
void create_foreground() {

    // Plane 5, so in front of the bubble
    sp1_InitCharStruct(&brick_object, SP1_DRAW_LOAD1NR, SP1_TYPE_1BYTE, &brick, 5);     // create the CS structure (NR - no rotation needed), plane 5
    bricks_update = sp1_GetUpdateStruct(11, 10);                                        // get the update tile (row, col) I want to apply the sprite
    sp1_InsertCharStruct(bricks_update, &brick_object);                                 // insert the cs structure in the sp_update

    // Plane 15, so behind of the bubble
    sp1_InitCharStruct(&brick_object2, SP1_DRAW_LOAD1NR, SP1_TYPE_1BYTE, &brick, 15);   // create the CS structure (NR - no rotation needed), plane 15
    bricks_update = sp1_GetUpdateStruct(11, 20);                                        // get the update tile (row, col) I want to apply the sprite
    sp1_InsertCharStruct(bricks_update, &brick_object2);                                // insert the cs structure in the sp_update

    // Plane 5, so in front of the bubble, but we can see through it :)
    sp1_InitCharStruct(&window_object, SP1_DRAW_MASK2NR, SP1_TYPE_2BYTE, &window, 5);   // create the CS structure (NR - no rotation needed), plane 5 with mask
    bricks_update = sp1_GetUpdateStruct(18, 15);                                        // get the update tile (row, col) I want to apply the sprite
    sp1_InsertCharStruct(bricks_update, &window_object);                                // insert the cs structure in the sp_update
}

int main() {

    zx_border(INK_WHITE);

    setup_int();

    sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                   INK_WHITE | PAPER_BLACK, ' ' );
            
    sp1_Invalidate(&full_screen);

    create_bubble();

    create_foreground();

    while(1) {

        get_movement();
        
        sp1_MoveSprPix(bubble.s, &full_screen, 0, bubble.x, bubble.y);

        intrinsic_halt();
        sp1_UpdateNow();
    }
}