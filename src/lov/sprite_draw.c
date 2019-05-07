#include "doom.h"

void		sprite_flat_draw(t_raycasting *rc, double **z_buffer,
	Uint32 **canvas)
{
	Uint32	color;
	int		y;
	int		d;

	rc->x = rc->draw_start_x - 1;
	while (++rc->x < rc->draw_end_x)
	{
		rc->tex_x = (int)((rc->x - (-((int)rc->sprite_width >> 1)
		+ rc->sprite_screen_x)) * rc->texture->w / rc->sprite_width);
		if (rc->transform.y > 0 && rc->x > 0 && rc->x < WIN_W
		&& rc->transform.y < (*z_buffer)[rc->x])
		{
			y = rc->draw_start_y - 1;
			while (++y < rc->draw_end_y)
			{
				d = ((int)((y - rc->v_move_screen) - (WIN_H * rc->p_z)) << 8)
				+ ((int)rc->sprite_height << 7);
				rc->tex_y = ((d * rc->texture->h) / rc->sprite_height) >> 8;
				color = ((Uint32*)rc->texture->pixels)[rc->texture->w
				* rc->tex_y + rc->tex_x];
				if ((color & 0x00FFFFFF) != 0)
					(*canvas)[y * WIN_W + rc->x] = color;
			}
		}
	}
}

void		sprite_door_draw(t_raycasting *rc, double **z_buffer,
	Uint32 **canvas, double stage)
{
	int		d;
	Uint32	color;
	int		y;

	if (rc->perp_wall_dist > 0 && rc->perp_wall_dist < (*z_buffer)[rc->x])
	{
		y = rc->draw_start - 1;
		while (++y < rc->draw_end - rc->lineHeight * stage)
		{
			d = ((int)((y + rc->lineHeight * stage)
			- (WIN_H * rc->p_z)) << 8) + ((int)rc->lineHeight << 7);
			rc->tex.y = ((d * rc->texture->h) / rc->lineHeight) >> 8;
			rc->tex.y = rc->tex.y % rc->texture->h;
			color = ((Uint32 *)rc->texture->pixels)[rc->texture->w
				* rc->tex.y + rc->tex.x];
			if (rc->side == 1)
				color = (color >> 1) & 8355711;
			if (rc->cur_sprite->render_mode == rend_window)
				color = calc_gradient((*canvas)[y * WIN_W + rc->x], color, 0.5);
			(*canvas)[y * WIN_W + rc->x] = color;
		}
	}
}

void		sprite_cast_wall(t_doom *doom, t_raycasting *rc,
	t_player *p, double **z_buffer)
{
	rc->x = -1;
	while (++rc->x < WIN_W)
	{
		wfc_init(rc, p);
		if (sprite_rayhit(rc, p, doom->nmap))
		{
			if (rc->cur_sprite->pos.x != rc->map.x
			|| rc->cur_sprite->pos.y != rc->map.y)
				continue ;
			sprite_door_init(rc, p);
			sprite_door_draw(rc, z_buffer, &doom->s_pixels,
				rc->cur_sprite->stage);
			wfc_init(rc, p);
		}
	}
}

void		draw_sprites2(t_doom *doom, t_player *p, t_raycasting *rc)
{
	t_list	*tmp;
	int		i;

	i = -1;
	tmp = doom->nmap->sprites->firstelement;
	while (++i < doom->lsprite.numbSprites)
	{
		rc->cur_sprite = tmp->content;
		doom->lsprite.spritesOrder[i] = i;
		doom->lsprite.spritesDist[i] = ((p->pos.x - rc->cur_sprite->pos.x)
		* (p->pos.x - rc->cur_sprite->pos.x)
		+ (p->pos.y - rc->cur_sprite->pos.y)
		* (p->pos.y - rc->cur_sprite->pos.y));
		tmp = tmp->next;
	}
}

void		draw_sprites(t_doom *doom, t_raycasting *rc, t_player *p,
		double **z_buffer)
{
	t_list	*tmp;
	int		i;

	draw_sprites2(doom, &doom->you, &doom->raycasting);
	combSort(doom->lsprite.spritesOrder,
		doom->lsprite.spritesDist, doom->lsprite.numbSprites);
	i = -1;
	tmp = doom->nmap->sprites->firstelement;
	while (++i < doom->lsprite.numbSprites)
	{
		rc->cur_sprite = ft_lstget(doom->lsprite.spritesOrder[i], tmp)->content;
		if (doom->nmap->map[(int)rc->cur_sprite->pos.y]
						[(int)rc->cur_sprite->pos.x].state == 1)
			rc->cur_sprite->stage += (rc->cur_sprite->stage < 1 ? 0.01 : 0.0);
		rc->texture = get_surface(doom, rc->cur_sprite->texture);
		if (rc->cur_sprite->render_mode == rend_door
		|| rc->cur_sprite->render_mode == rend_window)
			sprite_cast_wall(doom, rc, p, z_buffer);
		else if (rc->cur_sprite->render_mode == rend_flat)
		{
			sprite_flat_init(rc, p, i, rc->cur_sprite,
				doom->lsprite.spritesOrder);
			sprite_flat_draw(rc, z_buffer, &doom->s_pixels);
		}
	}
}
