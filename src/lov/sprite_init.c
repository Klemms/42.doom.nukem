#include "doom.h"

void    sprite_flat_init(t_raycasting *rc, t_player *p, int i, t_sprite *sprite, int *spriteOrder)
{
  //parameters for scaling and moving the sprites
  #define uDiv 1
  #define vDiv 1
  #define vMove 0.0

  double invDet;

  //translate sprite position to relative to camera
  rc->rel_sprite_pos.x = sprite->pos.x - p->pos.x;
  rc->rel_sprite_pos.y = sprite->pos.y - p->pos.y;

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
  rc->draw_start_y = -rc->sprite_height / 2 + WIN_H * rc->p_z + rc->v_move_screen;
  if (rc->draw_start_y < 0)
    rc->draw_start_y = 0;
  rc->draw_end_y = rc->sprite_height / 2 + WIN_H * rc->p_z + rc->v_move_screen;
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

void    sprite_door_init(t_raycasting *rc, t_player *p)
{
  if (rc->side == 0) // HERE
    rc->perp_wall_dist = (rc->map.x + (rc->step.x / 2.0) - p->pos.x + (1 - (rc->step.x)) / 2) / rc->ray_dir.x;
  else
    rc->perp_wall_dist = (rc->map.y + (rc->step.y / 2.0) - p->pos.y + (1 - (rc->step.y)) / 2) / rc->ray_dir.y;
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