/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguranda <pguranda@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:01:58 by pguranda          #+#    #+#             */
/*   Updated: 2022/09/25 13:37:52 by pguranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	kill_player(t_game *game)
{
	game->player.tile = NULL;
	ft_printf("You lost!");
	end_program(game);
}

void	remove_player(t_game *game)
{
	game->player.tile->type = EMPTY;
	game->player.tile = NULL;
}

void	move_to_empty(t_game *game, t_tile *tile)
{
	tile->type = PLAYER;
	if (game->player.tile->type != EXIT)
		game->player.tile->type = EMPTY;
	if (game->player.tile->was_exit == TRUE)
		game->player.tile->type = EXIT;
	game->player.tile = tile;
}

void	pick_collect(t_game *game, t_tile *tile)
{
	tile->type = PLAYER;
	game->collects--;
	if (game->player.tile->type != EXIT)
		game->player.tile->type = EMPTY;
	if (game->player.tile->was_exit == TRUE)
		game->player.tile->type = EXIT;
	game->player.tile = tile;
}

void	through_exit(t_game *game, t_tile *tile)
{
	tile->type = PLAYER;
	if (game->player.tile->type != EXIT)
		game->player.tile->type = EMPTY;
	ft_printf("Not all collectables are gathered!\n");
	game->player.tile = tile;
}

void	move_to_exit(t_game *game)
{
	remove_player(game);
	game->collects = -1;
	ft_printf("You won!");
	end_program(game);
}

void	move_to_enemy(t_game *game)
{
	remove_player(game);
	ft_printf("You lost!");
	end_program(game);
}

t_bool	move_to(t_game *game, t_tile *tile)
{
	if(tile->type == EMPTY)
		move_to_empty(game, tile);
	else if(tile->type == COLLECTABLE)
		pick_collect(game, tile);
	else if (tile->type == EXIT && game->collects <= 0)
		move_to_exit(game);
	else if (tile->type == EXIT && game->collects > 0)
		through_exit(game, tile);
	else if (tile->type == ENEMY)
		move_to_enemy(game);
	else
		return (FALSE);
	move_enemies(game);
	return (TRUE);
}

int	input(int key, t_game *game)
{
	t_bool	moved;
	
	if (key == ESC)
		end_program(game);
	if (game->player.tile == NULL)
		return (0);
	if (key == KEY_UP)
		moved = move_to(game, game->player.tile->up);
	else if (key == KEY_DOWN)
		moved = move_to(game, game->player.tile->down);
	else if (key == KEY_LEFT)
		moved = move_to(game, game->player.tile->left);
	else if (key == KEY_RIGHT)
		moved = move_to(game, game->player.tile->right);
	else
		return (0);
	if  (moved != FALSE )
		ft_printf("Moves -> %02d\n", game->moves++);
	return (1);
}