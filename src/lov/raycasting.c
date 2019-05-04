/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cababou <cababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:20:18 by hdussert          #+#    #+#             */
/*   Updated: 2019/05/04 09:43:07 by cababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void    init_raycasting(t_raycasting *rc, t_player *p)
{
  rc->p_z = p->pos.z;
  rc->camera_x = 2 * rc->x / (double)(WIN_W) - 1;
  rc->ray_dir.x = p->dir.x + p->plane.x * rc->camera_x;
  rc->ray_dir.y = p->dir.y + p->plane.y * rc->camera_x;
  rc->map.x = (int)(p->pos.x);
  rc->map.y = (int)(p->pos.y);
  rc->delta_dist.x = fabs(1 / rc->ray_dir.x);//length of ray from one x or y-rc->side to next x or y-rc->side
  rc->delta_dist.y = fabs(1 / rc->ray_dir.y);
  if (rc->ray_dir.x < 0) //calculate step and initial sideDist
  {
    rc->step.x = -1;
    rc->side_dist.x = (p->pos.x - rc->map.x) * rc->delta_dist.x;
  }
  else
  {
    rc->step.x = 1;
    rc->side_dist.x = (rc->map.x + 1.0 - p->pos.x) * rc->delta_dist.x;
  }
  if (rc->ray_dir.y < 0)
  {
    rc->step.y = -1;
    rc->side_dist.y = (p->pos.y - rc->map.y) * rc->delta_dist.y;
  }
  else
  {
    rc->step.y = 1;
    rc->side_dist.y = (rc->map.y + 1.0 - p->pos.y) * rc->delta_dist.y;
  }
}

void    init_raycasting_draw_wall(t_raycasting *rc, t_player *p)
{
  if (rc->side == 0)
    rc->perp_wall_dist = (rc->map.x - p->pos.x + (1 - rc->step.x) / 2) / rc->ray_dir.x;
  else
    rc->perp_wall_dist = (rc->map.y - p->pos.y + (1 - rc->step.y) / 2) / rc->ray_dir.y;
  rc->lineHeight = (int)(WIN_H / rc->perp_wall_dist);
  rc->draw_start = -rc->lineHeight / 2 + WIN_H * rc->p_z;
  rc->draw_end = rc->lineHeight / 2 + WIN_H * rc->p_z;
  if(rc->draw_start < 0)
    rc->draw_start = 0;
  if(rc->draw_end >= WIN_H)
    rc->draw_end = WIN_H - 1;
  if (rc->draw_end < rc->draw_start)
  {
    rc->draw_start = 0;
    rc->draw_end = WIN_H - 1;
  }
  //int texNum = doom->map.m[rc->map.x][rc->map.y] - 1; //1 subtracted from it so that texture 0 can be used!
  if (rc->side == 0)
    rc->wall_x = p->pos.y + rc->perp_wall_dist * rc->ray_dir.y;
  else 
    rc->wall_x = p->pos.x + rc->perp_wall_dist * rc->ray_dir.x;
  rc->wall_x -= floor((rc->wall_x));
  rc->tex.x = (int)(rc->wall_x * (double)(rc->texture->w));
  rc->tex.x = rc->tex.x % rc->texture->w;
  if(rc->side == 0 && rc->ray_dir.x > 0)
    rc->tex.x = rc->texture->w - rc->tex.x - 1;
  if(rc->side == 1 && rc->ray_dir.y < 0)
    rc->tex.x = rc->texture->w - rc->tex.x - 1;
}

void    init_raycasting_draw_floor(t_raycasting *rc)
{
  //4 different wall directions possible
  if(rc->side == 0 && rc->ray_dir.x > 0)
  {
    rc->floor.x = rc->map.x;
    rc->floor.y = rc->map.y + rc->wall_x;
  }
  else if(rc->side == 0 && rc->ray_dir.x < 0)
  {
    rc->floor.x = rc->map.x + 1.0;
    rc->floor.y = rc->map.y + rc->wall_x;
  }
  else if(rc->side == 1 && rc->ray_dir.y > 0)
  {
    rc->floor.x = rc->map.x + rc->wall_x;
    rc->floor.y = rc->map.y;
  }
  else
  {
    rc->floor.x = rc->map.x + rc->wall_x;
    rc->floor.y = rc->map.y + 1.0;
  }
  if (rc->draw_end < 0)
    rc->draw_end = WIN_H; //becomes < 0 when the integer overflows
}
void    ray_hit(t_raycasting *rc, t_nmap *nmap)
{
  int hit;
  hit = 0;
  rc->dist_hit = 0;
  while (hit == 0)
  {
    if (rc->side_dist.x < rc->side_dist.y)
    {
      rc->side_dist.x += rc->delta_dist.x;
      rc->map.x += rc->step.x;
      rc->side = 0;
    }
    else
    {
      rc->side_dist.y += rc->delta_dist.y;
      rc->map.y += rc->step.y;
      rc->side = 1;
    }
    rc->dist_hit++;
    if (nmap->map[rc->map.y][rc->map.x].collides)
      hit = 1;
  }
}


// Épurer lov dans lov_cp, trouver comment gérer le choix des textures
// Probablement quelques variables a ajouter dans rc
// Bien vérifier que chacun s'y trouvant est utile
// Ajouter variable hauteur de tête / angle
// Fog sur la distance?


void    draw_wall(t_raycasting *rc, Uint32 **canvas)
{
  int     d;
  Uint32  color;
  int     y;

  y = rc->draw_start - 1;
  while (++y < rc->draw_end)
  {
    d = y * 256 - (WIN_H * rc->p_z * 256) + rc->lineHeight * 128; //256 and 128 factors to avoid floats
    // TODO: avoid the division to speed this up
    rc->tex.y = ((d * rc->texture->h) / rc->lineHeight) / 256;
    rc->tex.y = rc->tex.y % rc->texture->h;
    color = ((Uint32 *)rc->texture->pixels)[rc->texture->w * rc->tex.y + rc->tex.x];
    //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
    if(rc->side == 1) color = (color >> 1) & 8355711;
    (*canvas)[y * WIN_W + rc->x] = color;
  }
}


void    draw_floor(t_raycasting *rc, t_player *p, Uint32 **canvas)
{
  double weight;
  double currentFloorX;
  double currentFloorY;
  double distWall, distPlayer, currentDist;
  int   y;

  distWall = rc->perp_wall_dist;
  distPlayer = 0.0;
  y = rc->draw_end;
  while (++y < WIN_H)
  {
    currentDist = WIN_H / (2.0 * y - (WIN_H * rc->p_z * 2.0)); //you could make a small lookup table for this instead
    weight = (currentDist - distPlayer) / (distWall - distPlayer);
    currentFloorX = weight * rc->floor.x + (1.0 - weight) * p->pos.x;
    currentFloorY = weight * rc->floor.y + (1.0 - weight) * p->pos.y;
    rc->floor_tex.x = (int)(currentFloorX * rc->texture->w) % rc->texture->w;
    rc->floor_tex.y = (int)(currentFloorY * rc->texture->h) % rc->texture->h;
    // int checkerBoardPattern = ((int)(currentFloorX + currentFloorY)) % 2;
    // int floorTexture;
    // if(checkerBoardPattern == 0) floorTexture = 3;
    // else floorTexture = 4;
    (*canvas)[y * WIN_W + rc->x] = (((Uint32 *)rc->texture->pixels)[rc->texture->w * rc->floor_tex.y + rc->floor_tex.x] >> 1) & 8355711; //floor
  }
}

void    draw_ceiling(t_raycasting *rc, t_player *p, Uint32 **canvas)
{
  double weight;
  double currentFloorX;
  double currentFloorY;
  double distWall, distPlayer, currentDist;
  int   y;

  distWall = rc->perp_wall_dist;
  distPlayer = 0.0;
  y = 0;
  while (++y < rc->draw_start)
  {
    currentDist = WIN_H / ((WIN_H * rc->p_z * 2.0) - 2.0 * y); //you could make a small lookup table for this instead
    weight = (currentDist - distPlayer) / (distWall - distPlayer);
    currentFloorX = weight * rc->floor.x + (1.0 - weight) * p->pos.x;
    currentFloorY = weight * rc->floor.y + (1.0 - weight) * p->pos.y;
    rc->floor_tex.x = (int)(currentFloorX * rc->texture->w) % rc->texture->w;
    rc->floor_tex.y = (int)(currentFloorY * rc->texture->h) % rc->texture->h;
    (*canvas)[y * WIN_W + rc->x] = ((Uint32 *)rc->texture->pixels)[rc->texture->w * rc->floor_tex.y + rc->floor_tex.x]; //ceiling (symmetrical!)
  }
}

void    init_raycasting_draw_sprites(t_raycasting *rc, t_player *p, int i, SDL_Surface *texture_sprite, t_vec *sprite, int *spriteOrder)
{
  //parameters for scaling and moving the sprites
  #define uDiv 1
  #define vDiv 1
  #define vMove 0.0

  double invDet;

//translate sprite position to relative to camera
  rc->rel_sprite_pos.x = sprite[spriteOrder[i]].x - p->pos.x;
  rc->rel_sprite_pos.y = sprite[spriteOrder[i]].y - p->pos.y;

  //transform sprite with the inverse camera matrix
  // [ p->plane.x   p->dir.x ] -1                                       [ p->dir.y      -p->dir.x ]
  // [               ]       =  1/(p->plane.x*p->dir.y-p->dir.x*p->plane.y) *   [                 ]
  // [ p->plane.y   p->dir.y ]                                          [ -p->plane.y  p->plane.x ]
  invDet = 1.0 / (p->plane.x * p->dir.y - p->dir.x * p->plane.y); //required for correct matrix multiplication

  rc->transform.x = invDet * (p->dir.y * rc->rel_sprite_pos.x - p->dir.x * rc->rel_sprite_pos.y);
  rc->transform.y = invDet * (-p->plane.y * rc->rel_sprite_pos.x + p->plane.x * rc->rel_sprite_pos.y); //this is actually the depth inside the screen, that what Z is in 3D
  rc->sprite_screen_x = (int)((WIN_W / 2) * (1 + rc->transform.x / rc->transform.y));
  rc->v_move_screen = (int)(vMove / rc->transform.y);
  //calculate height of the sprite on screen
  rc->sprite_height = abs((int)(WIN_H / (rc->transform.y))) / vDiv; //using "rc->transform.y" instead of the real distance prevents fisheye
  //calculate lowest and highest pixel to fill in current stripe
  rc->draw_start_y = -rc->sprite_height / 2 + WIN_H / 2 + rc->v_move_screen;
  if (rc->draw_start_y < 0)
    rc->draw_start_y = 0;
  rc->draw_end_y = rc->sprite_height / 2 + WIN_H / 2 + rc->v_move_screen;
  if (rc->draw_end_y >= WIN_H)
    rc->draw_end_y = WIN_H - 1;

  //calculate width of the sprite
  rc->sprite_width = abs((int)(WIN_H / (rc->transform.y))) / uDiv;
  rc->draw_start_x = -rc->sprite_width / 2 + rc->sprite_screen_x;
  if (rc->draw_start_x < 0)
    rc->draw_start_x = 0;
  rc->draw_end_x = rc->sprite_width / 2 + rc->sprite_screen_x;
  if (rc->draw_end_x >= WIN_W)
    rc->draw_end_x = WIN_W - 1;
}

void    draw_sprites(t_doom *doom, t_raycasting *rc, t_player *p, double **z_buffer, SDL_Surface *texture_sprite, Uint32 **canvas)
{
  //SPRITE CASTING
  int stripe;
  int d;
  int numSprites = 2;
  int spriteOrder[2];
  int spriteDistance[2];
  t_vec   sprite[2] = { { 2, 2, 0 }, { 3, 3, 0 } };
  int i;
  int y;
  Uint32 color;

  i = -1;
  while (++i < numSprites)
  {
    spriteOrder[i] = i;
    spriteDistance[i] = ((p->pos.x - sprite[i].x) * (p->pos.x - sprite[i].x) + (p->pos.y - sprite[i].y) * (p->pos.y - sprite[i].y)); //sqrt not taken, unneeded
  }
  //combSort(spriteOrder, spriteDistance, numSprites);
  i = -1;
  while (++i < numSprites)
  {
    init_raycasting_draw_sprites(rc, p, i, texture_sprite, sprite, spriteOrder);
    stripe = rc->draw_start_x - 1;
    while (++stripe < rc->draw_end_x)
    {
      rc->tex_x = (int)(256 * (stripe - (-rc->sprite_width / 2 + rc->sprite_screen_x)) * 64 / rc->sprite_width) / 256;
      //the conditions in the if are:
      //1) it's in front of camera plane so you don't see things behind you
      //2) it's on the screen (left)
      //3) it's on the screen (right)
      //4) ZBuffer, with perpendicular distance
      if (rc->transform.y > 0 && stripe > 0 && stripe < WIN_W && rc->transform.y < (*z_buffer)[stripe])
      {
        y = rc->draw_start_y - 1;
        while (++y < rc->draw_end_y) //for every pixel of the current stripe
        {
          //d = (y - rc->v_move_screen) * 256 - WIN_H * 128 + rc->sprite_height * 128; //256 and 128 factors to avoid floats
          //rc->tex_y = ((d * 64) / rc->sprite_height) / 256; // this 64 whas HEIGHT the other WIDTH
          rc->tex_y = 0;
          color = 0xFFFF00FF;//((Uint32*)texture_sprite->pixels)[64 * rc->tex_y + rc->tex_x]; //get current color from the texture
          //if((color & 0x00FFFFFF) != 0)
            (*canvas)[y * WIN_W + stripe] = color; //paint pixel if it isn't black, black is the invisible color
        }
      }
    }
  }
}

void    draw_screen(t_doom *doom)
{
  doom->raycasting.texture = get_surface(doom, 2);
  doom->raycasting.x = -1;

  SDL_Surface *texture_sprite;
  texture_sprite = get_surface(doom, 1);
  //SDL_Surface *sprite;
  //sprite = get_surface(doom, 0);
  double    **z_buffer;
  z_buffer = malloc(sizeof(double *));
  *z_buffer = malloc(sizeof(double) * WIN_W);
  while (++doom->raycasting.x < WIN_W)
  {
    init_raycasting(&doom->raycasting, &doom->you);
    ray_hit(&doom->raycasting, doom->nmap);

    init_raycasting_draw_wall(&doom->raycasting, &doom->you);
    draw_wall(&doom->raycasting, &doom->s_pixels);
    (*z_buffer)[doom->raycasting.x] = doom->raycasting.perp_wall_dist;
    init_raycasting_draw_floor(&doom->raycasting);
    draw_floor(&doom->raycasting, &doom->you, &doom->s_pixels);
    draw_ceiling(&doom->raycasting, &doom->you, &doom->s_pixels);

    //init_raycasting_draw_sprites(&doom->raycasting);
  }
  draw_sprites(doom, &doom->raycasting, &doom->you, z_buffer, texture_sprite, &doom->s_pixels);
  free(*z_buffer);
  free(z_buffer);
}