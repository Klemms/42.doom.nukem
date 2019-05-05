#include "doom.h"

void    sprite_flat_init(t_raycasting *rc, t_player *p, int i, SDL_Surface *texture_sprite, t_vec *sprite, int *spriteOrder)
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