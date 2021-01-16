#ifndef _INT_H
#define _INT_H

#define SPEED 1

#define TABLE_HIGH_BYTE        ((unsigned int)0xD0)
#define JUMP_POINT_HIGH_BYTE   ((unsigned int)0xD1)

#define UI_256                 ((unsigned int)256)
#define TABLE_ADDR             ((void*)(TABLE_HIGH_BYTE*UI_256))
#define JUMP_POINT             ((unsigned char*)( (unsigned int)(JUMP_POINT_HIGH_BYTE*UI_256) + JUMP_POINT_HIGH_BYTE ))

extern uint16_t ticker;
extern uint8_t interrupt_1s;
extern uint8_t interrupt_250ms;
extern uint8_t interrupt_500ms;
extern uint8_t interrupt_100ms;
extern uint8_t interrupt_50ms;

extern void setup_int(void);

#endif