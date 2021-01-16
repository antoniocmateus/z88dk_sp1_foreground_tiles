# z88dk Foreground objects

Foreground objects with SP1 - The freesprite characters structure solution

## Getting Started

There are 3 ways in wich we can create foreground tiles with SP1: 

* By validating squares before rendering (see example ex5b from z88dk)
* by removing tiles from the render array (see example ex5c from z88dk)
* by using the free sprite characters structure, sp1_cs, which is the one we're going to see here

Each one has it's merits, but using sp1_cs allows us to use much of sprite capabilities, so we may have sprites walking behind the object, sprites walking in front of the object, we may use masks (for fences or windows).

## Description

The secret is in the use of 4 methods available from the SP1 library:

* sp1_InitCharStruct, to create the sp1_cs structure which is usually created automatically by sp1_CreateSpr
* sp1_GetUpdateStruct to get the update structure region where we're going to insert our free sprite characters structure
* sp1_InsertCharStruct to insert our free sprite characters structure into the update structure
* sp1_RemoveCharStruct to remove the free sprite characters structure (not covered here)


## Program

The code is fully documented and can be compiled with

```
zcc +zx -vn -startup=31 -clib=sdcc_iy sprites.asm tile1.asm tile2.asm int.c main.c -o test_bed -create-app
```

You also have a compiled TAP file. Use QAOP keys to move the bubble and see the sprites/tiles behaviour.

## License

You can freely use the code or ideas as you wish. I have commented most of it, you should be able to follow it easily.
If it helps you in any way, I'll be happy.

## Acknowledgments

As always

* [z88dk](https://z88dk.org/) - z88dk home
* [World of Spectrum forums](https://worldofspectrum.org/forums)


