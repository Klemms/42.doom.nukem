/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:45:40 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/15 11:39:53 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define EyeHeight  6    // Hauteur de la caméra par rapport au sol en position debout
#define DuckHeight 2.5  // Et en s'accroupissant
#define HeadMargin 1    // Combien de place il y a au-dessus de la caméra avant que la tête frappe le plafond
#define KneeHeight 2    // Quelle est la hauteur des obstacles sur lesquels le joueur peut simplement marcher sans sauter
#define hfov (0.73f*H)  // Affecte le champ de vision horizontal
#define vfov (.2f*H)   

#include "../includes/doom.h"

#define min(a,b)             (((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
#define max(a,b)             (((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
#define clamp(a, mi,ma)      min(max(a,mi),ma)         // clamp: Clamp value into set range.
#define vxs(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))   // vxs: Vector cross product
// Overlap:  Determine whether the two number ranges overlap.
#define Overlap(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
// IntersectBox: Déterminer si deux boîtes 2D se croisent.
#define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
// PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
#define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))

static void MovePlayer(t_doom *doom, float dx, float dy)
{
    float px = doom->player.where.x, py = doom->player.where.y;
    /* Check if this movement crosses one of this sector's edges
     * that have a neighboring sector on the other side.
     * Because the edge vertices of each sector are defined in
     * clockwise order, PointSide will always return -1 for a point
     * that is outside the sector and 0 or 1 for a point that is inside.
     */
    t_sector* const sect = &doom->sectors[doom->player.sector];
    t_xy * const vert = sect->vertex;
    for(int s = 0; s < sect->pts; ++s)
        if(sect->neighbors[s] >= 0
        && IntersectBox(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
        && PointSide(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
        {
            doom->player.sector = sect->neighbors[s];
            break;
        }

    doom->player.where.x += dx;
    doom->player.where.y += dy;
    doom->player.anglesin = sin(doom->player.angle);
    doom->player.anglecos = cos(doom->player.angle);
}

int main2()
{
	t_doom	doom;

	ft_init_doom(&doom);
	printf("oui\n");
    SDL_ShowCursor(SDL_DISABLE);

    int wsad[4]={0,0,0,0}, ground=0, falling=1, moving=0, ducking=0;
    float yaw = 0;
    for(;;)
    {
        SDL_RenderClear(doom.rend);
		doom.surface = SDL_GetWindowSurface(doom.win);
		ft_print_screen(&doom);
		SDL_UpdateWindowSurface(doom.win);

        /* Vertical collision detection */
        float eyeheight = ducking ? DuckHeight : EyeHeight;
        ground = !falling;
        if(falling)
        {
            doom.player.velocity.z -= 0.05f; /* Add gravity */
            float nextz = doom.player.where.z + doom.player.velocity.z;
            if(doom.player.velocity.z < 0 && nextz  < doom.sectors[doom.player.sector].floor + eyeheight) // When going down
            {
                /* Fix to ground */
                doom.player.where.z    = doom.sectors[doom.player.sector].floor + eyeheight;
                doom.player.velocity.z = 0;
                falling = 0;
                ground  = 1;
            }
            else if(doom.player.velocity.z > 0 && nextz > doom.sectors[doom.player.sector].ceil) // When going up
            {
                /* Prevent jumping above ceiling */
                doom.player.velocity.z = 0;
                falling = 1;
            }
            if(falling)
            {
                doom.player.where.z += doom.player.velocity.z;
                moving = 1;
            }
        }
        /* Horizontal collision detection */
        if(moving)
        {
            float px = doom.player.where.x,    py = doom.player.where.y;
            float dx = doom.player.velocity.x, dy = doom.player.velocity.y;

            t_sector* const sect = &doom.sectors[doom.player.sector];
            t_xy* const vert = sect->vertex;
            /* Check if the player is about to cross one of the sector's edges */
            for(int s = 0; s < sect->pts; ++s)
                if(IntersectBox(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
                && PointSide(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
                {
                    /* Check where the hole is. */
                    float hole_low  = sect->neighbors[s] < 0 ?  9e9 : max(sect->floor, doom.sectors[sect->neighbors[s]].floor);
                    float hole_high = sect->neighbors[s] < 0 ? -9e9 : min(sect->ceil,  doom.sectors[sect->neighbors[s]].ceil );
                    /* Check whether we're bumping into a wall. */
                    if(hole_high < doom.player.where.z+HeadMargin
                    || hole_low  > doom.player.where.z-eyeheight+KneeHeight)
                    {
                        /* Bumps into a wall! Slide along the wall. */
                        /* This formula is from Wikipedia article "vector projection". */
                        float xd = vert[s+1].x - vert[s+0].x, yd = vert[s+1].y - vert[s+0].y;
                        dx = xd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                        dy = yd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                        moving = 0;
                    }
                }
            MovePlayer(&doom, dx, dy);
            falling = 1;
        }
		printf("OUI\n");
        SDL_Event ev;
        while(SDL_PollEvent(&ev))
		{
			printf("nonon\n");
            switch(ev.type)
            {
                case SDL_KEYDOWN:
                case SDL_KEYUP:
					printf("nonon\n");
                    switch(ev.key.keysym.sym)
                    {
						case SDLK_ESCAPE: ft_quit(&doom, "quit", 3);
                        case 'w': wsad[0] = ev.type==SDL_KEYDOWN; break;
                        case 's': wsad[1] = ev.type==SDL_KEYDOWN; break;
                        case 'a': wsad[2] = ev.type==SDL_KEYDOWN; break;
                        case 'd': wsad[3] = ev.type==SDL_KEYDOWN; break;
                        case ' ': /* jump */
                            if(ground) { doom.player.velocity.z += 0.5; falling = 1; }
                            break;
                        case SDLK_LCTRL: /* duck */
                        case SDLK_RCTRL: ducking = ev.type==SDL_KEYDOWN; falling=1; break;
                        default: break;
                    }
                    break;
            }
		}
        /* mouse aiming */
        int x,y;
        SDL_GetRelativeMouseState(&x,&y);
        doom.player.angle += x * 0.03f;
        yaw          = clamp(yaw - y*0.05f, -5, 5);
        doom.player.yaw   = yaw - doom.player.velocity.z*0.5f;
        MovePlayer(&doom, 0,0);

        float move_vec[2] = {0.f, 0.f};
        if(wsad[0]) { move_vec[0] += doom.player.anglecos*0.2f; move_vec[1] += doom.player.anglesin*0.2f; }
        if(wsad[1]) { move_vec[0] -= doom.player.anglecos*0.2f; move_vec[1] -= doom.player.anglesin*0.2f; }
        if(wsad[2]) { move_vec[0] += doom.player.anglesin*0.2f; move_vec[1] -= doom.player.anglecos*0.2f; }
        if(wsad[3]) { move_vec[0] -= doom.player.anglesin*0.2f; move_vec[1] += doom.player.anglecos*0.2f; }
        int pushing = wsad[0] || wsad[1] || wsad[2] || wsad[3];
        float acceleration = pushing ? 0.4 : 0.2;

        doom.player.velocity.x = doom.player.velocity.x * (1-acceleration) + move_vec[0] * acceleration;
        doom.player.velocity.y = doom.player.velocity.y * (1-acceleration) + move_vec[1] * acceleration;

        if(pushing) moving = 1;

        SDL_Delay(10);
    }
	SDL_DestroyRenderer(doom.rend);
	SDL_DestroyWindow(doom.win);
	SDL_Quit();
	return (EXIT_SUCCESS);
}
