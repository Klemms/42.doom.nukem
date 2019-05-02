/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:20:18 by hdussert          #+#    #+#             */
/*   Updated: 2019/05/01 21:26:18 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double					calc_column(t_sight *p, t_doom *doom, int num)
{
	double	col;
	SDL_Surface	*tmp = get_surface(doom, p->queue[num].tex);
	//if (p->queue[num].tex == 0)
		printf("%d %d %d\n", tmp->w, tmp->h, p->queue[num].tex);
	if (!tmp)
		return (0);
	if (p->queue[num].side == 1)
		col = p->queue[num].x + p->queue[num].z * p->ray_dir.x;
	else
		col = p->queue[num].y + p->queue[num].z * p->ray_dir.y;
	col = col - floor(col);
	col = round(col * (tmp->w - 1));
	if ((p->queue[num].side == 0 && p->ray_dir.x > 0)
	|| (p->queue[num].side == 1 && p->ray_dir.y < 0))
		col = tmp->w - col - 1;
	return (col);
}

double				calc_perp_dist(t_sight *p, t_player *you, int num)
{
	if (p->queue[num].side == 0)
		return(((int)p->queue[num].x - you->pos.x
			+ (1.0 - p->step.x) / 2.0) / p->ray_dir.x);
	else
		return(((int)p->queue[num].y - you->pos.y
			+ (1.0 - p->step.y) / 2.0) / p->ray_dir.y);
}

double				calc_perp_dist_next(t_sight *p, t_player *you, int num, int num2)
{
	if (num2 == 0)
		return(((int)p->queue[num].next_x - you->pos.x
			+ (1.0 - p->step.x) / 2.0) / p->ray_dir.x);
	else
		return(((int)p->queue[num].next_y - you->pos.y
			+ (1.0 - p->step.y) / 2.0) / p->ray_dir.y);
}
/*
void				calc_lov(t_doom *doom)
{
	int		x;
	double		column;
	int		cptest;

	x = 0;
	while (x < doom->w)
	{
		init_sight(doom, &doom->sight, x, &doom->you);
		if (see_wall(&doom->sight, doom))
		{
			cptest = doom->sight.queue_cpt;
			//while (--cptest >= 0)
			//{
			//	column = calc_column(&doom->sight, doom, cptest);
			draw_wall(doom, x, column, 0);
			//}
			column = calc_column(&doom->sight, doom, 0);
			//draw_floor(doom, x, column);
		}
		x++;
	}
}*/
void		fuck_it(t_doom *doom)
{
	SDL_Surface		*texture;
	texture = get_surface(doom, 2);
	printf("ok\n");
	int x = -1;
	while (++x < doom->w)
    {
	//init_sight(doom, &doom->sight, x, &doom->you);
      //calculate ray position and direction
      double cameraX = 2 * x / (double)(doom->w) - 1; //x-coordinate in camera space
      double rayDirX = doom->you.dir.x + doom->you.plane.x * cameraX;
      double rayDirY = doom->you.dir.y + doom->you.plane.y * cameraX;

      //which box of the map we're in
      int mapX = (int)(doom->you.pos.x);
      int mapY = (int)(doom->you.pos.y);

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      double deltaDistX = fabs(1 / rayDirX);
      double deltaDistY = fabs(1 / rayDirY);
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      if (rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (doom->you.pos.x - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - doom->you.pos.x) * deltaDistX;
      }
      if (rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (doom->you.pos.y - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - doom->you.pos.y) * deltaDistY;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if (doom->map.m[mapY][mapX] != '.') hit = 1;
      }

      //Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
      if (side == 0) perpWallDist = (mapX - doom->you.pos.x + (1 - stepX) / 2) / rayDirX;
      else           perpWallDist = (mapY - doom->you.pos.y + (1 - stepY) / 2) / rayDirY;

      //Calculate height of line to draw on screen
      int lineHeight = (int)(doom->h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + doom->h / 2;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + doom->h / 2;
      if(drawEnd >= doom->h) drawEnd = doom->h - 1;
      //texturing calculations
      printf("%d, %d\n", drawStart, drawEnd);
	  if (drawEnd <= 0) drawEnd = doom->h - 1;
	  if (drawStart >= doom->h) drawStart = 0;
	  //int texNum = doom->map.m[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (side == 0) wallX = doom->you.pos.y + perpWallDist * rayDirY;
      else           wallX = doom->you.pos.x + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)(texture->w));
      if(side == 0 && rayDirX > 0) texX = texture->w - texX - 1;
      if(side == 1 && rayDirY < 0) texX = texture->w - texX - 1;
	  int y = drawStart - 1;
      while (++y < drawEnd)
      {
        int d = y * 256 - doom->h * 128 + lineHeight * 128; //256 and 128 factors to avoid floats
        // TODO: avoid the division to speed this up
        int texY = ((d * texture->h) / lineHeight) / 256;
        Uint32 color = ((Uint32 *)texture->pixels)[texture->w * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        //if(side == 1) color = (color >> 1) & 8355711;
        doom->s_pixels[y * doom->w + x] = color;
      }

      //FLOOR CASTING
      double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

      //4 different wall directions possible
      if(side == 0 && rayDirX > 0)
      {
        floorXWall = mapX;
        floorYWall = mapY + wallX;
      }
      else if(side == 0 && rayDirX < 0)
      {
        floorXWall = mapX + 1.0;
        floorYWall = mapY + wallX;
      }
      else if(side == 1 && rayDirY > 0)
      {
        floorXWall = mapX + wallX;
        floorYWall = mapY;
      }
      else
      {
        floorXWall = mapX + wallX;
        floorYWall = mapY + 1.0;
      }

      double distWall, distPlayer, currentDist;

      distWall = perpWallDist;
      distPlayer = 0.0;


      if (drawEnd < 0) drawEnd = doom->h; //becomes < 0 when the integer overflows

      //draw the floor from drawEnd to the bottom of the screen
	  y = drawEnd;
      while (++y < doom->h)
      {
        currentDist = doom->h / (2.0 * y - doom->h); //you could make a small lookup table for this instead

        double weight = (currentDist - distPlayer) / (distWall - distPlayer);

        double currentFloorX = weight * floorXWall + (1.0 - weight) * doom->you.pos.x;
        double currentFloorY = weight * floorYWall + (1.0 - weight) * doom->you.pos.y;

        int floorTexX, floorTexY;
        floorTexX = (int)(currentFloorX * texture->w) % texture->w;
        floorTexY = (int)(currentFloorY * texture->h) % texture->h;

        int checkerBoardPattern = ((int)(currentFloorX + currentFloorY)) % 2;
        int floorTexture;
        if(checkerBoardPattern == 0) floorTexture = 3;
        else floorTexture = 4;
		
        //floor
        doom->s_pixels[y * doom->w + x] = (((Uint32 *)texture->pixels)[texture->w * floorTexY + floorTexX] >> 1) & 8355711;
        //ceiling (symmetrical!)
        doom->s_pixels[(doom->h - y) * doom->w + x] = ((Uint32 *)texture->pixels)[texture->w * floorTexY + floorTexX];
      }
	}
	printf("--0 okend 0 --\n");
}

void		calc_lov(t_doom *doom)
{
	fuck_it(doom);
}
