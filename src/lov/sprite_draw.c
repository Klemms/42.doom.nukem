#include "doom.h"

Uint32            calc_gradient(Uint32 color1, Uint32 color2, double stage)
{
        Uint32             color;
        Uint32             r;
        Uint32             g;
        Uint32             b;

        r = (Uint32)((((color1 >> 16) & 0xFF) + ((color2 >> 16) & 0xFF)) * stage) << 16;
        g = (Uint32)((((color1 >> 8) & 0xFF) + ((color2 >> 8) & 0xFF)) * stage) << 8;
        b = (Uint32)((color1 & 0xFF) + (color2 & 0xFF)) * stage;
        color = r | g | b;
        return (color);
}

void              sprite_flat_draw(t_raycasting *rc, double **z_buffer, SDL_Surface *texture_sprite, Uint32 **canvas)
{
  int stripe;
  Uint32 color;
  int y;
  int d;
  
  stripe = rc->draw_start_x - 1;
  while (++stripe < rc->draw_end_x)
  {
    rc->tex_x = (int)((stripe - (-rc->sprite_width / 2 + rc->sprite_screen_x)) * texture_sprite->w / rc->sprite_width);
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
        d = ((y - rc->v_move_screen) - (WIN_H * rc->p_z)) * 256 + rc->sprite_height * 128; //256 and 128 factors to avoid floats
        //d = (y - (WIN_H * rc->p_z)) * 256) + rc->lineHeight * 128; 
        rc->tex_y = ((d * texture_sprite->h) / rc->sprite_height) / 256; // this 64 whas HEIGHT the other WIDTH
        color = ((Uint32*)texture_sprite->pixels)[texture_sprite->w * rc->tex_y + rc->tex_x]; //get current color from the texture
        if((color & 0x00FFFFFF) != 0)
          (*canvas)[y * WIN_W + stripe] = calc_gradient(0xFFFFFF - (*canvas)[y * WIN_W + stripe], color, 0.35);// + color / 2; //paint pixel if it isn't black, black is the invisible color

      }
    }
  }
}



void    draw_sprites(t_doom *doom, t_raycasting *rc, t_player *p, double **z_buffer, Uint32 **canvas)
{
  //SPRITE CASTING
  
  
  int numSprites = 2;
  int spriteOrder[2];
  int spriteDistance[2];
  t_vec   sprite_flat[2] = { { 2, 2, 0 }, { 3, 3, 1 } };
  t_vec   sprite_wall[2] = { { 4, 4, 1 }, { 4, 6, 0 } };
  int i;
  SDL_Surface *texture_sprite;
  


  i = -1;
  while (++i < numSprites)
  {
    spriteOrder[i] = i;
    spriteDistance[i] = ((p->pos.x - sprite_flat[i].x) * (p->pos.x - sprite_flat[i].x) + (p->pos.y - sprite_flat[i].y) * (p->pos.y - sprite_flat[i].y)); //sqrt not taken, unneeded
  }
  //combSort(spriteOrder, spriteDistance, numSprites);
  i = -1;
  while (++i < numSprites)
  {
    //if (sprite[numSprites].cast == wall_like)
    // {
      //init_raycasting_draw_wall_sprite();
      //ray_hit_sprite();
      //draw_wall_sprite();
    // }
  }
  i = -1;
  while (++i < numSprites)
  {
    //else if (sprite[numSprites].cast == flat)
    //{
        texture_sprite = get_surface(doom, sprite_flat[i].z);
        sprite_flat_init(rc, p, i, texture_sprite, sprite_flat, spriteOrder);
        sprite_flat_draw(rc, z_buffer, texture_sprite, canvas);
    //}
  }
}