/*
** EPITECH PROJECT, 2023
** open
** File description:
** window
*/

#include <ncurses.h>
#include "struct.h"
#include <stdlib.h>
#include <unistd.h>

head_t *serpent(WINDOW *win)
{
    head_t *head = malloc(sizeof(*head));
    snake_t *part = malloc(sizeof(*part));
    part->x = 20;
    part->y = 30;
    part->next = NULL;
    part->previous = NULL;
    head->first = part;
    return head;
}

head_t *add_element(head_t *head, int x, int y)
{
    snake_t *part = malloc(sizeof(*part));
    part->x = x;
    part->y = y;
    snake_t *tmp = head->first;
    part->next = NULL;
    while (tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = part;
    part->previous = tmp;
    return head;
}

head_t *init_snake(head_t *head, all_t *game, int x, int y, WINDOW *win)
{
    int i = 0;
    while (i < game->length) {
        add_element(head, x, y);
        y--; i++;
    } return head;
}

last_t *get_last(head_t *head, last_t *last)
{
    snake_t *tmp = head->first;
    while (tmp->next) {
        tmp = tmp->next;
    } last->last = tmp;
    return last;
}

void display(head_t *head, food_t *snake_food, WINDOW *win, last_t *last)
{
    werase(win);
    box(win, '|', '-');
    wattron(win, A_REVERSE);
    mvwprintw(win, snake_food->x, snake_food->y, " ");
    wattroff(win, A_REVERSE);
    snake_t *tmp = head->first;
    mvwprintw(win, tmp->x, tmp->y, "D");
    tmp = tmp->next;
    int i = 48;
    while (tmp) {
        wattron(win, A_REVERSE);
        mvwprintw(win, tmp->x, tmp->y, " ");
        tmp = tmp->next;
    } wattroff(win, A_REVERSE);
    usleep(10000);
}

food_t *init_food(int x, int y, WINDOW *win)
{
    food_t *snake_food = malloc(sizeof(*snake_food));
    snake_food->x = x;
    snake_food->y = y;
    return snake_food;
}

void movements(all_t *game, int ch, head_t *head, last_t *last)
{
    if (ch == KEY_LEFT && game->direction != 2) {
        game->direction = 1;
    } else if (ch == KEY_RIGHT && game->direction != 1) {
	game->direction	= 2;
    } else if (ch == KEY_UP && game->direction != 4) {
	game->direction	= 3;
    } else if (ch == KEY_DOWN && game->direction != 3) {
	game->direction	= 4;
    } usleep(1000);
}

void execute()
{
}

void move_left(all_t *game, last_t *last, head_t *head)
{
    if (game->direction == 1) {
        head->first->y--;
        snake_t *tmp = last->last;
        while (tmp->previous) {
            tmp->x = tmp->previous->x;
            tmp->y = tmp->previous->y;
            tmp = tmp->previous;
        }
    }
}

void move_up(all_t *game, last_t *last, head_t *head)
{
    if (game->direction == 3) {
        head->first->x--;
        snake_t *tmp = last->last;
	while (tmp->previous) {
            tmp->x = tmp->previous->x;
            tmp->y = tmp->previous->y;
            tmp = tmp->previous;
        }
    }
}

void move_right(all_t *game, last_t *last, head_t *head)
{
    if (game->direction == 2) {
        head->first->y++;
        snake_t *tmp = last->last;
        while (tmp->previous) {
            tmp->x = tmp->previous->x;
            tmp->y = tmp->previous->y;
            tmp = tmp->previous;
        }
    }
}

void move_down(all_t *game, last_t *last, head_t *head)
{
    if (game->direction == 4) {
        head->first->x++;
        snake_t *tmp = last->last;
        while (tmp->previous) {
            tmp->x = tmp->previous->x;
            tmp->y = tmp->previous->y;
            tmp = tmp->previous;
        }
    }
}

void recome(head_t *head)
{
    if (head->first->x == 40)
        head->first->x = 0;
    else if (head->first->x == 0)
        head->first->x = 40;
    else if (head->first->y == 0)
        head->first->y = 80;
    else if (head->first->y == 80)
	head->first->y = 0;
}

void eat_food(food_t *food, head_t *head, last_t *last, all_t *game)
{
    if (head->first->x == food->x &&
        head->first->y == food->y) {
        game->length++;
        add_element(head, last->last->x--, last->last->y--);
        last = get_last(head, last);
        food->x = rand() % 40; food->y = rand() % 80;
    }
}

int main(void)
{
    all_t *game = malloc(sizeof(*game));
    last_t *last = malloc(sizeof(*last));
    game->direction = 0;
    game->length = 7; initscr(); noecho(); curs_set(false); refresh();
    WINDOW *win = newwin(40, 80, (LINES - 40) / 2, (COLS - 80) / 2);
    nodelay(win, true); head_t *snake_head = serpent(win);
    init_snake(snake_head, game, 20, 35, win);
    food_t *food = init_food(10, 15, win); wrefresh(win); refresh();
    last = get_last(snake_head, last);
    int n; keypad(win, true);
    while (1) {
        wclear(win);
        display(snake_head, food, win, last); n = wgetch(win);
        movements(game, n, snake_head, last); move_left(game, last, snake_head); move_up(game, last, snake_head);
        move_right(game, last, snake_head); move_down(game, last, snake_head); recome(snake_head);
        eat_food(food, snake_head, last, game);
        wrefresh(win); usleep(100000);
    }
    endwin();
    free(snake_head); free(game); free(food); free(last);
}
