/*
** EPITECH PROJECT, 2023
** struct
** File description:
** head file
*/

#ifndef STRUCT_H
    #define STRUCT_H

    typedef struct snake {
        int x;
        int y;
        struct snake *next;
        struct snake *previous;
    } snake_t;

    typedef struct snake_head {
        snake_t *first;
    } head_t;

    typedef struct food {
        int x;
        int y;
    } food_t;

    typedef struct all {
        int length;
        int direction;
    } all_t;

    typedef struct last {
        snake_t *last;
    } last_t;

#endif
