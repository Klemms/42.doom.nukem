/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 12:46:03 by lde-batz          #+#    #+#             */
/*   Updated: 2019/03/18 11:27:27 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../includes/SDL.h"

/* Define window size */
#define W 608
#define H 480
/* Définir diverses constantes liées à la vision */
#define EyeHeight  6    // Hauteur de la caméra par rapport au sol en position debout
#define DuckHeight 2.5  // Et en s'accroupissant
#define HeadMargin 1    // Combien de place il y a au-dessus de la caméra avant que la tête frappe le plafond
#define KneeHeight 2    // Quelle est la hauteur des obstacles sur lesquels le joueur peut simplement marcher sans sauter
#define hfov (0.73f*H)  // Affecte le champ de vision horizontal
#define vfov (.2f*H)    // Affecte le champ de vision vertical

/* Sectors: Floor and ceiling height; list of edge vertices and neighbors */
static struct sector
{
    float floor, ceil;
    struct xy { float x,y; } *vertex; // chaque sommet a une coord x et y
    signed char *neighbors;           // chaque bord peut avoir un secteur voisin correspondant
    unsigned npoints;                 // combiem de sommet il y a
} *sectors = NULL;
static unsigned NumSectors = 0;

/* Player: location */
static struct player
{
    struct xyz { float x,y,z; } where,      // position du jouer
                                velocity;   // vecteur de movement
    float angle, anglesin, anglecos, yaw;   // Looking towards (and sin() and cos() thereof)
    unsigned sector;                        // dans quel secteur est le joueur
} player;

// Utility functions. Because C doesn't have templates,
// we use the slightly less safe preprocessor macros to
// implement these functions that work with multiple types.
#define min(a,b)             (((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
#define max(a,b)             (((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
#define clamp(a, mi,ma)      min(max(a,mi),ma)         // clamp: Clamp value into set range.
#define vxs(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))   // vxs: Vector cross product
// Overlap:  Déterminez si les deux tranches de numéros se chevauchent.
#define Overlap(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
// IntersectBox: Déterminer si deux boîtes 2D se croisent.
#define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
// PointSide: Déterminez de quel côté de la ligne se trouve le point. Valeur renvoyée: <0, = 0 ou> 0.
#define PointSide(px,py, x1,y1, x2,y2) vxs((x2)-(x1), (y2)-(y1), (px)-(x1), (py)-(y1))
// Intersect: Calculate the point of intersection between two lines.
#define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((struct xy) { \
    vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })

static void LoadData()
{
    FILE* fp = fopen("map-clear.txt", "rt");
    if(!fp) { perror("map-clear.txt"); exit(1); }
    char Buf[256], word[256], *ptr;
    struct xy* vert = NULL, v;
    int n, m, NumVertices = 0;
    while(fgets(Buf, sizeof Buf, fp))
        switch(sscanf(ptr = Buf, "%32s%n", word, &n) == 1 ? word[0] : '\0')
        {
            case 'v': // vertex
                for(sscanf(ptr += n, "%f%n", &v.y, &n); sscanf(ptr += n, "%f%n", &v.x, &n) == 1; )
                    { vert = realloc(vert, ++NumVertices * sizeof(*vert)); vert[NumVertices-1] = v; }
                break;
            case 's': // sector
                sectors = realloc(sectors, ++NumSectors * sizeof(*sectors));
                struct sector* sect = &sectors[NumSectors-1];
                int* num = NULL;
                sscanf(ptr += n, "%f%f%n", &sect->floor,&sect->ceil, &n);
                for(m=0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#'; )
                    { num = realloc(num, ++m * sizeof(*num)); num[m-1] = word[0]=='x' ? -1 : atoi(word); }
                sect->npoints   = m /= 2;
                sect->neighbors = malloc( (m  ) * sizeof(*sect->neighbors) );
                sect->vertex    = malloc( (m+1) * sizeof(*sect->vertex)    );
                for(n=0; n<m; ++n) sect->neighbors[n] = num[m + n];
                for(n=0; n<m; ++n) sect->vertex[n+1]  = vert[num[n]]; // TODO: Range checking
                sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a loop
                free(num);
                break;
            case 'p':; // player
                float angle;
                sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle,&n);
                player = (struct player) { {v.x, v.y, 0}, {0,0,0}, angle,0,0,0, n }; // TODO: Range checking
                player.where.z = sectors[player.sector].floor + EyeHeight;
        }
    fclose(fp);
    free(vert);
}
static void UnloadData()
{
    for(unsigned a=0; a<NumSectors; ++a) free(sectors[a].vertex);
    for(unsigned a=0; a<NumSectors; ++a) free(sectors[a].neighbors);
    free(sectors);
    sectors    = NULL;
    NumSectors = 0;
}

static SDL_Surface* surface = NULL;

/* vline: trace une ligne verticale sur l'écran, avec un pixel de couleur différente en haut et en bas */
static void vline(int x, int y1,int y2, int top,int middle,int bottom)
{
    int *pix = (int*) surface->pixels;
    y1 = clamp(y1, 0, H-1);
    y2 = clamp(y2, 0, H-1);
    if(y2 == y1)
        pix[y1*W+x] = middle;
    else if(y2 > y1)
    {
        pix[y1*W+x] = top;
        for(int y=y1+1; y<y2; ++y) pix[y*W+x] = middle;
        pix[y2*W+x] = bottom;
    }
}

/* MovePlayer(dx,dy): Moves the player by (dx,dy) in the map, and
 * also updates their anglesin/anglecos/sector properties properly.
 */
static void MovePlayer(float dx, float dy)
{
    float px = player.where.x, py = player.where.y;
    /* Check if this movement crosses one of this sector's edges
     * that have a neighboring sector on the other side.
     * Because the edge vertices of each sector are defined in
     * clockwise order, PointSide will always return -1 for a point
     * that is outside the sector and 0 or 1 for a point that is inside.
     */
    const struct sector* const sect = &sectors[player.sector];
    const struct xy* const vert = sect->vertex;
    for(unsigned s = 0; s < sect->npoints; ++s)
        if(sect->neighbors[s] >= 0
        && IntersectBox(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
        && PointSide(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
        {
            player.sector = sect->neighbors[s];
            break;
        }

    player.where.x += dx;
    player.where.y += dy;
    player.anglesin = sinf(player.angle);
    player.anglecos = cosf(player.angle);
}

static void DrawScreen()
{
    enum { MaxQueue = 32 };  // nombre maximum de rendus de portail en attente
    struct item { int sectorno,sx1,sx2; } queue[MaxQueue], *head=queue, *tail=queue;
    int ytop[W]={0}, ybottom[W], renderedsectors[NumSectors];
    for(unsigned x=0; x<W; ++x) ybottom[x] = H-1;
    for(unsigned n=0; n<NumSectors; ++n) renderedsectors[n] = 0;

    /* Commencez le rendu sur tout l'écran à partir de l'endroit où se trouve le lecteur. */
    *head = (struct item) { player.sector, 0, W-1 };
    if(++head == queue+MaxQueue) head = queue;

    do {
		/* Choisissez un secteur et une tranche dans la file d'attente pour dessiner */
		const struct item now = *tail;
		if(++tail == queue+MaxQueue) tail = queue;

		if(renderedsectors[now.sectorno] & 0x21) continue; // Odd = toujours rendu, 0x20 = abandonner
		++renderedsectors[now.sectorno];
		const struct sector* const sect = &sectors[now.sectorno];
		/* Rendu chaque mur de ce secteur qui fait face au joueur. */
		for(unsigned s = 0; s < sect->npoints; ++s)
		{
			/* Acquérir les coordonnées x, y des deux extrémités (sommets) de cette arête du secteur */
			float vx1 = sect->vertex[s+0].x - player.where.x, vy1 = sect->vertex[s+0].y - player.where.y;
			float vx2 = sect->vertex[s+1].x - player.where.x, vy2 = sect->vertex[s+1].y - player.where.y;
			/* Faites-les pivoter autour de la vue du joueur */
			float pcos = player.anglecos, psin = player.anglesin;
			float tx1 = vx1 * psin - vy1 * pcos,  tz1 = vx1 * pcos + vy1 * psin;
			float tx2 = vx2 * psin - vy2 * pcos,  tz2 = vx2 * pcos + vy2 * psin;
			/* Le mur est-il au moins partiellement devant le joueur? */
			if(tz1 <= 0 && tz2 <= 0) continue;
			/* Le mur est-il au moins partiellement devant le joueur? */
			if(tz1 <= 0 || tz2 <= 0)
			{
				float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
				// Trouver une intersection entre le mur et les bords approximatifs de la vue du joueur
				struct xy i1 = Intersect(tx1,tz1,tx2,tz2, -nearside,nearz, -farside,farz);
				struct xy i2 = Intersect(tx1,tz1,tx2,tz2,  nearside,nearz,  farside,farz);
				if(tz1 < nearz) { if(i1.y > 0) { tx1 = i1.x; tz1 = i1.y; } else { tx1 = i2.x; tz1 = i2.y; } }
				if(tz2 < nearz) { if(i1.y > 0) { tx2 = i1.x; tz2 = i1.y; } else { tx2 = i2.x; tz2 = i2.y; } }
			}
			/* Faire la transformation de perspective */
			float xscale1 = hfov / tz1, yscale1 = vfov / tz1;    int x1 = W/2 - (int)(tx1 * xscale1);
			float xscale2 = hfov / tz2, yscale2 = vfov / tz2;    int x2 = W/2 - (int)(tx2 * xscale2);
			if(x1 >= x2 || x2 < now.sx1 || x1 > now.sx2) continue; // Rendre seulement si c'est visible
			/* Acquérir les hauteurs de plancher et de plafond, par rapport à la vue du joueur */
			float yceil  = sect->ceil  - player.where.z;
			float yfloor = sect->floor - player.where.z;
			/* Vérifiez le type de bord. voisin = -1 signifie mur, autre = frontière entre deux secteurs. */
			int neighbor = sect->neighbors[s];
			float nyceil=0, nyfloor=0;
			if(neighbor >= 0) // Un autre secteur apparaît-il sur ce portail?
			{
				nyceil  = sectors[neighbor].ceil  - player.where.z;
				nyfloor = sectors[neighbor].floor - player.where.z;
			}
			/* Projeter nos hauteurs de plafond et de plancher en coordonnées d'écran (coordonnée en Y) */
			#define Yaw(y,z) (y + z*player.yaw)
			int y1a  = H/2 - (int)(Yaw(yceil, tz1) * yscale1),  y1b = H/2 - (int)(Yaw(yfloor, tz1) * yscale1);
			int y2a  = H/2 - (int)(Yaw(yceil, tz2) * yscale2),  y2b = H/2 - (int)(Yaw(yfloor, tz2) * yscale2);
			/* Même chose pour le secteur voisin */
			int ny1a = H/2 - (int)(Yaw(nyceil, tz1) * yscale1), ny1b = H/2 - (int)(Yaw(nyfloor, tz1) * yscale1);
			int ny2a = H/2 - (int)(Yaw(nyceil, tz2) * yscale2), ny2b = H/2 - (int)(Yaw(nyfloor, tz2) * yscale2);

			/* Rendu du mur */
			int beginx = max(x1, now.sx1), endx = min(x2, now.sx2);
			for(int x = beginx; x <= endx; ++x)
			{
				/* Calculez la coordonnée Z pour ce point. (Utilisé uniquement pour l'éclairage.) */
				int z = ((x - x1) * (tz2-tz1) / (x2-x1) + tz1) * 8;
				/* Acquérir les coordonnées Y pour notre plafond et le sol pour cette coordonnée X. Les pince. */
				int ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a, cya = clamp(ya, ytop[x],ybottom[x]); // top
				int yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b, cyb = clamp(yb, ytop[x],ybottom[x]); // bottom

				/* Render plafond: tout ce qui dépasse la hauteur de plafond de ce secteur. */
				vline(x, ytop[x], cya-1, 0x111111 ,0x222222,0x111111);
				/* Render floor: tout en dessous de la hauteur de plancher de ce secteur. */
				vline(x, cyb+1, ybottom[x], 0x0000FF,0x0000AA,0x0000FF);

				/* Y a-t-il un autre secteur derrière ce bord? */
				if(neighbor >= 0)
				{
					/* Pareil pour le sol et le plafond */
					int nya = (x - x1) * (ny2a-ny1a) / (x2-x1) + ny1a, cnya = clamp(nya, ytop[x],ybottom[x]);
					int nyb = (x - x1) * (ny2b-ny1b) / (x2-x1) + ny1b, cnyb = clamp(nyb, ytop[x],ybottom[x]);
					/* Si notre plafond est plus élevé que leur plafond, rendez mur supérieur */
					unsigned r1 = 0x010101 * (255-z), r2 = 0x040007 * (31-z/8);
					vline(x, cya, cnya-1, 0, x==x1||x==x2 ? 0 : r1, 0); // Entre notre et leur plafond
					ytop[x] = clamp(max(cya, cnya), ytop[x], H-1);   // Réduire la fenêtre restante au-dessous de ces plafonds
					/* If our floor is lower than their floor, render bottom wall */
					vline(x, cnyb+1, cyb, 0, x==x1||x==x2 ? 0 : r2, 0); // Between their and our floor
					ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]); // Shrink the remaining window above these floors
				}
				else
				{
					/* Il n'y a pas de voisin. Rendu du mur du haut (cya = niveau du plafond) vers le bas (cyb = niveau du sol). */
					unsigned r = 0x010101 * (255-z);
					vline(x, cya, cyb, 0, x==x1||x==x2 ? 0 : r, 0);
				}
			}
			/* Schedule the neighboring sector for rendering within the window formed by this wall. */
			if(neighbor >= 0 && endx >= beginx && (head+MaxQueue+1-tail)%MaxQueue)
			{
				*head = (struct item) { neighbor, beginx, endx };
				if(++head == queue+MaxQueue) head = queue;
			}
		} // for s in sector's edges
		++renderedsectors[now.sectorno];
    } while(head != tail); // rendre tous les autres secteurs en file d'attente
}

int main()
{
    LoadData();

    surface = SDL_SetVideoMode(W, H, 32, 0);

    SDL_EnableKeyRepeat(150, 30);
    SDL_ShowCursor(SDL_DISABLE);

    int wsad[4]={0,0,0,0}, ground=0, falling=1, moving=0, ducking=0;
    float yaw = 0;
    for(;;)
    {
        SDL_LockSurface(surface);
        DrawScreen();
        SDL_UnlockSurface(surface);
        SDL_Flip(surface);

        /* Vertical collision detection */
        float eyeheight = ducking ? DuckHeight : EyeHeight;
        ground = !falling;
        if(falling)
        {
            player.velocity.z -= 0.05f; /* Add gravity */
            float nextz = player.where.z + player.velocity.z;
            if(player.velocity.z < 0 && nextz  < sectors[player.sector].floor + eyeheight) // When going down
            {
                /* Fix to ground */
                player.where.z    = sectors[player.sector].floor + eyeheight;
                player.velocity.z = 0;
                falling = 0;
                ground  = 1;
            }
            else if(player.velocity.z > 0 && nextz > sectors[player.sector].ceil) // When going up
            {
                /* Prevent jumping above ceiling */
                player.velocity.z = 0;
                falling = 1;
            }
            if(falling)
            {
                player.where.z += player.velocity.z;
                moving = 1;
            }
        }
        /* Horizontal collision detection */
        if(moving)
        {
            float px = player.where.x,    py = player.where.y;
            float dx = player.velocity.x, dy = player.velocity.y;

            const struct sector* const sect = &sectors[player.sector];
            const struct xy* const vert = sect->vertex;
            /* Check if the player is about to cross one of the sector's edges */
            for(unsigned s = 0; s < sect->npoints; ++s)
                if(IntersectBox(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
                && PointSide(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
                {
                    /* Check where the hole is. */
                    float hole_low  = sect->neighbors[s] < 0 ?  9e9 : max(sect->floor, sectors[sect->neighbors[s]].floor);
                    float hole_high = sect->neighbors[s] < 0 ? -9e9 : min(sect->ceil,  sectors[sect->neighbors[s]].ceil );
                    /* Check whether we're bumping into a wall. */
                    if(hole_high < player.where.z+HeadMargin
                    || hole_low  > player.where.z-eyeheight+KneeHeight)
                    {
                        /* Bumps into a wall! Slide along the wall. */
                        /* This formula is from Wikipedia article "vector projection". */
                        float xd = vert[s+1].x - vert[s+0].x, yd = vert[s+1].y - vert[s+0].y;
                        dx = xd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                        dy = yd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                        moving = 0;
                    }
                }
            MovePlayer(dx, dy);
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
                        case 'w': wsad[0] = ev.type==SDL_KEYDOWN; break;
                        case 's': wsad[1] = ev.type==SDL_KEYDOWN; break;
                        case 'a': wsad[2] = ev.type==SDL_KEYDOWN; break;
                        case 'd': wsad[3] = ev.type==SDL_KEYDOWN; break;
                        case 'q': goto done;
                        case ' ': /* jump */
                            if(ground) { player.velocity.z += 0.5; falling = 1; }
                            break;
                        case SDLK_LCTRL: /* duck */
                        case SDLK_RCTRL: ducking = ev.type==SDL_KEYDOWN; falling=1; break;
                        default: break;
                    }
                    break;
                case SDL_QUIT: goto done;
            }
		}
        /* mouse aiming */
        int x,y;
        SDL_GetRelativeMouseState(&x,&y);
        player.angle += x * 0.03f;
        yaw          = clamp(yaw - y*0.05f, -5, 5);
        player.yaw   = yaw - player.velocity.z*0.5f;
        MovePlayer(0,0);

        float move_vec[2] = {0.f, 0.f};
        if(wsad[0]) { move_vec[0] += player.anglecos*0.2f; move_vec[1] += player.anglesin*0.2f; }
        if(wsad[1]) { move_vec[0] -= player.anglecos*0.2f; move_vec[1] -= player.anglesin*0.2f; }
        if(wsad[2]) { move_vec[0] += player.anglesin*0.2f; move_vec[1] -= player.anglecos*0.2f; }
        if(wsad[3]) { move_vec[0] -= player.anglesin*0.2f; move_vec[1] += player.anglecos*0.2f; }
        int pushing = wsad[0] || wsad[1] || wsad[2] || wsad[3];
        float acceleration = pushing ? 0.4 : 0.2;

        player.velocity.x = player.velocity.x * (1-acceleration) + move_vec[0] * acceleration;
        player.velocity.y = player.velocity.y * (1-acceleration) + move_vec[1] * acceleration;

        if(pushing) moving = 1;

        SDL_Delay(10);
    }
done:
    UnloadData();
    SDL_Quit();
    return 0;
}


void	ft_print_screen1(t_doom *doom)
{
	t_raycasting	r;
	int				render_sector[doom->num_sectors];

	r.head = r.wait;
	r.tail = r.wait;
	r.i = WIN_W;
	while (--r.i >= 0)
	{
		r.y_top[r.i] = 0;
		r.y_bot[r.i] = WIN_H - 1;
	}
	while (++r.i < doom->num_sectors)
		render_sector[r.i] = 0;
    /* Commencez le rendu sur tout l'écran à partir de l'endroit où se trouve le lecteur. */
    *r.head = (t_window) {doom->player.sector, 0, WIN_W - 1};
    if(++r.head == r.wait + MAX_WAIT)
		r.head = r.wait;
	// rendre tous les autres secteurs en file d'attente
    while(r.head != r.tail)
	{
		/* Choisissez un secteur et une tranche dans la file d'attente pour dessiner */
		r.now = *r.tail;
		if (++r.tail == r.wait + MAX_WAIT)
			r.tail = r.wait;
		// Odd = toujours rendu, 0x20 = abandonner
		if (render_sector[r.now.sector] & 0x21)
			continue;
		++render_sector[r.now.sector];
		r.sect = &doom->sectors[r.now.sector];
		/* Rendu chaque mur de ce secteur qui fait face au joueur. */
		r.i = -1;
		// pour r.i dans les bords du secteur
		while (++r.i < r.sect->pts)
		{
			/* Acquérir les coordonnées x, y des deux extrémités (sommets) de cette arête du secteur */
			r.v1.x = r.sect->vertex[r.i].x - doom->player.where.x;
			r.v1.y = r.sect->vertex[r.i].y - doom->player.where.y;
			r.v2.x = r.sect->vertex[r.i + 1].x - doom->player.where.x;
			r.v2.y = r.sect->vertex[r.i + 1].y - doom->player.where.y;
			/* Faites-les pivoter autour de la vue du joueur */
			r.p_cos = doom->player.anglecos;
			r.p_sin = doom->player.anglesin;
			r.t1.x = r.v1.x * r.p_sin - r.v1.y * r.p_cos;
			r.t1.y = r.v1.x * r.p_cos - r.v1.y * r.p_sin;
			r.t2.x = r.v2.x * r.p_sin - r.v2.y * r.p_cos;
			r.t2.y = r.v2.x * r.p_cos - r.v2.y * r.p_sin;
			/* Le mur est-il au moins partiellement devant le joueur? */
			if(r.t1.y <= 0 && r.t2.y <= 0)
				continue;
			/* Le mur est-il au moins partiellement devant le joueur? */
			if(r.t1.y <= 0 || r.t2.y <= 0)
			{
				// Trouver une intersection entre le mur et les bords approximatifs de la vue du joueur
				r.near.x = -0.00001;
				r.near.y = 0.0001;
				r.far.x = -20.0;
				r.far.y = 5.0;
				r.i1 = ft_intersect_lines(r.t1, r.t2, r.near, r.far);r.near.x *= -1;
				r.far.x *= -1;
				r.i2 = ft_intersect_lines(r.t1, r.t2, r.near, r.far);
				if (r.t1.y < r.near.y)
				{
					if (r.i1.y > 0)
					{
						r.t1.x = r.i1.x;
						r.t1.y = r.i1.y;
					}
					else
					{
						r.t1.x = r.i2.x;
						r.t1.y = r.i2.y;
					}
				}
				if (r.t2.y < r.near.y)
				{
					if (r.i1.y > 0)
					{
						r.t2.x = r.i1.x;
						r.t2.y = r.i1.y;
					}
					else
					{
						r.t2.x = r.i2.x;
						r.t2.y = r.i2.y;
					}
				}
			}
			/* Faire la transformation de perspective */
			r.scale1.x = ANGLE_H / r.t1.y;
			r.scale1.y = ANGLE_V / r.t1.y;
			r.scale2.x = ANGLE_H / r.t2.y;
			r.scale2.y = ANGLE_V / r.t2.y;
			r.lim_x.x = (WIN_W / 2) - (int)(r.t1.x * r.scale1.x);
			r.lim_x.y = (WIN_W / 2) - (int)(r.t2.x * r.scale2.x);
			// Rendre seulement si c'est visible
			if(r.lim_x.x >= r.lim_x.y || r.lim_x.x > r.now.x2 || r.lim_x.y < r.now.x1)
				continue;
			/* Acquérir les hauteurs de plancher et de plafond, par rapport à la vue du joueur */
			r.y_ceil = r.sect->ceil - doom->player.where.z;
			r.y_floor = r.sect->floor - doom->player.where.z;
			/* Vérifiez le type de bord. voisin = -1 signifie mur, autre = frontière entre deux secteurs. */
			r.neighbor = r.sect->neighbors[r.i];
			r.ny_ceil = 0;
			r.ny_floor = 0;
			// Un autre secteur apparaît-il sur ce portail?
			if(r.neighbor >= 0)
			{
				r.ny_ceil  = doom->sectors[r.neighbor].ceil  - doom->player.where.z;
				r.ny_floor = doom->sectors[r.neighbor].floor - doom->player.where.z;
			}
			/* Projeter nos hauteurs de plafond et de plancher en coordonnées d'écran (coordonnée en Y) */
			r.y1.x = (WIN_H / 2) - (int)((doom->player.yaw * r.t1.y + r.y_ceil) * r.scale1.y);
			r.y1.y = (WIN_H / 2) - (int)((doom->player.yaw * r.t1.y + r.y_floor) * r.scale1.y);
			r.y2.x = (WIN_H / 2) - (int)((doom->player.yaw * r.t2.y + r.y_ceil) * r.scale2.y);
			r.y2.y = (WIN_H / 2) - (int)((doom->player.yaw * r.t2.y + r.y_floor) * r.scale2.y);
			/* Même chose pour le secteur voisin */
			r.n_y1.x = (WIN_H / 2) - (int)((doom->player.yaw * r.t1.y + r.ny_ceil) * r.scale1.y);
			r.n_y1.y = (WIN_H / 2) - (int)((doom->player.yaw * r.t1.y + r.ny_floor) * r.scale1.y);
			r.n_y2.x = (WIN_H / 2) - (int)((doom->player.yaw * r.t2.y + r.ny_ceil) * r.scale2.y);
			r.n_y2.y = (WIN_H / 2) - (int)((doom->player.yaw * r.t2.y + r.ny_floor) * r.scale2.y);
			/* Rendu du mur */
			r.x_start_end.x = (r.lim_x.x > r.now.x1) ? r.lim_x.x : r.now.x1;
			r.x_start_end.y = (r.lim_x.y < r.now.x2) ? r.lim_x.y : r.now.x2;
			r.x = r.x_start_end.x - 1;
			while (++r.x <= r.x_start_end.y)
			{
				/* Calculez la coordonnée Z pour ce point. (Utilisé uniquement pour l'éclairage.) */
				r.z = ((r.x - r.lim_x.x) * (r.t2.y-r.t1.y) / (r.lim_x.y-r.lim_x.x) + r.t1.y) * 8;
				/* Acquérir les coordonnées Y pour notre plafond et le sol pour cette coordonnée X. Les pince. */
				// top
				r.y.x = (r.x - r.lim_x.x) * (r.y2.x - r.y1.x) / (r.lim_x.y - r.lim_x.x) + r.y1.x;
				r.c_y.x = ft_clamp(r.y.x, r.y_top[r.x], r.y_bot[r.x]);
				// bottom
				r.y.y = (r.x - r.lim_x.x) * (r.y2.y - r.y1.y) / (r.lim_x.y - r.lim_x.x) + r.y1.y;
				r.c_y.y = ft_clamp(r.y.y, r.y_top[r.x], r.y_bot[r.x]);

				/* Render plafond: tout ce qui dépasse la hauteur de plafond de ce secteur. */
//				ft_print_x_wall2(doom, r.x, r.y_top[r.x], r.c_y.x-1, 0x111111 ,0x222222,0x111111);
				ft_print_x_wall(doom, r.x, r.y_top[r.x], r.c_y.x-1, 0x222222);

				/* Render floor: tout en dessous de la hauteur de plancher de ce secteur. */
//				ft_print_x_wall2(doom, r.x, r.c_y.y+1, r.y_bot[r.x], 0x0000FF,0x0000AA,0x0000FF);
				ft_print_x_wall(doom, r.x, r.c_y.y+1, r.y_bot[r.x], 0x0000AA);

				/* Y a-t-il un autre secteur derrière ce bord? */
				if(r.neighbor >= 0)
				{
					/* Pareil pour le sol et le plafond */
					r.n_y.x = (r.x - r.lim_x.x) * (r.n_y2.x-r.n_y1.x) / (r.lim_x.y-r.lim_x.x) + r.n_y1.x;
					r.c_n_y.x = ft_clamp(r.n_y.x, r.y_top[r.x],r.y_bot[r.x]);
					r.n_y.y = (r.x - r.lim_x.x) * (r.n_y2.y-r.n_y1.y) / (r.lim_x.y-r.lim_x.x) + r.n_y1.y;
					r.c_n_y.y = ft_clamp(r.n_y.y, r.y_top[r.x],r.y_bot[r.x]);
					r.color_ceil = 0x010101 * (255 - r.z);
					r.color_floor = 0x040007 * (31 - r.z / 8);
					/* Si notre plafond est plus élevé que leur plafond, rendez mur supérieur */
					// Entre notre et leur plafond
					ft_print_x_wall(doom, r.x, r.c_y.x, r.c_n_y.x - 1, r.color_ceil);
//					ft_print_x_wall2(doom, r.x, r.c_y.x, r.c_n_y.x-1, 0, r.x==r.lim_x.x||r.x==r.lim_x.y ? 0 : r.color_ceil, 0);
					// Réduire la fenêtre restante au-dessous de ces plafonds
					if (r.c_y.x < r.c_n_y.x)
						r.c_y.x = r.c_n_y.x;
					r.y_top[r.x] = ft_clamp(r.c_y.x, r.y_top[r.x], WIN_H-1);
					/* Si notre sol est plus bas que le sol, rendez le mur du bas */
					// Entre leur et notre sol
					ft_print_x_wall(doom, r.x, r.c_n_y.y + 1, r.c_y.y, r.color_floor);
//					ft_print_x_wall2(doom, r.x, r.c_n_y.y+1, r.c_y.y, 0, r.x==r.lim_x.x||r.x==r.lim_x.y ? 0 : r.color_floor, 0);
					//Réduire la fenêtre restante au-dessus de ces sol
					if (r.c_y.y > r.c_n_y.y)
						r.c_y.y = r.c_n_y.y;
					r.y_bot[r.x] = ft_clamp(r.c_y.y, 0, r.y_bot[r.x]);
				}
				else
				{
					/* Il n'y a pas de voisin. Rendu du mur du haut (cya = niveau du plafond) vers le bas (cyb = niveau du sol). */
					r.color_wall = 0x010101 * (255 - r.z);
					ft_print_x_wall(doom, r.x, r.c_y.x, r.c_y.y, r.color_wall);
//					ft_print_x_wall2(doom, r.x, r.c_y.x, r.c_y.y, 0, r.x==r.lim_x.x||r.x==r.lim_x.y ? 0 : t, 0);
				}
			}
			/* Planifiez le rendu du secteur voisin dans la fenêtre formée par ce mur. */
			if (r.neighbor >= 0 && r.x_start_end.y >= r.x_start_end.x && (r.head + MAX_WAIT + 1 - r.tail) % MAX_WAIT)
			{
				*r.head = (t_window){r.neighbor, r.x_start_end.x, r.x_start_end.y};
				if (++r.head == r.wait + MAX_WAIT)
					r.head = r.wait;
			}
		}
		++render_sector[r.now.sector];
    }
}


void	ft_print_s2(t_doom *doom)
{
    enum { MaxQueue = 32 };  // nombre maximum de rendus de portail en attente
    struct item { int sectorno,sx1,sx2; } queue[MaxQueue], *head=queue, *tail=queue;
    int ytop[WIN_W]={0}, ybottom[WIN_W], renderedsectors[doom->num_sectors];
    for(unsigned x=0; x<WIN_W; ++x) ybottom[x] = WIN_H-1;
    for(int n=0; n<doom->num_sectors; ++n) renderedsectors[n] = 0;

    /* Commencez le rendu sur tout l'écran à partir de l'endroit où se trouve le lecteur. */
    *head = (struct item) { doom->player.sector, 0, WIN_W-1 };
    if(++head == queue+MaxQueue) head = queue;

    do {
		/* Choisissez un secteur et une tranche dans la file d'attente pour dessiner */
		const struct item now = *tail;
		if(++tail == queue+MaxQueue) tail = queue;

		if(renderedsectors[now.sectorno] & 0x21) continue; // Odd = toujours rendu, 0x20 = abandonner
		++renderedsectors[now.sectorno];
		t_sector * const sect = &doom->sectors[now.sectorno];
		/* Rendu chaque mur de ce secteur qui fait face au joueur. */
		for(int s = 0; s < sect->pts; ++s)
		{
			/* Acquérir les coordonnées x, y des deux extrémités (sommets) de cette arête du secteur */
			float vx1 = sect->vertex[s+0].x - doom->player.where.x, vy1 = sect->vertex[s+0].y - doom->player.where.y;
			float vx2 = sect->vertex[s+1].x - doom->player.where.x, vy2 = sect->vertex[s+1].y - doom->player.where.y;
			/* Faites-les pivoter autour de la vue du joueur */
			float pcos = doom->player.anglecos, psin = doom->player.anglesin;
			float tx1 = vx1 * psin - vy1 * pcos,  tz1 = vx1 * pcos + vy1 * psin;
			float tx2 = vx2 * psin - vy2 * pcos,  tz2 = vx2 * pcos + vy2 * psin;
			/* Le mur est-il au moins partiellement devant le joueur? */
			if(tz1 <= 0 && tz2 <= 0) continue;
			/* Le mur est-il au moins partiellement devant le joueur? */
			if(tz1 <= 0 || tz2 <= 0)
			{
				float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
				// Trouver une intersection entre le mur et les bords approximatifs de la vue du joueur
				t_xy i1 = Intersect(tx1,tz1,tx2,tz2, -nearside,nearz, -farside,farz);
				t_xy i2 = Intersect(tx1,tz1,tx2,tz2,  nearside,nearz,  farside,farz);
				if(tz1 < nearz) { if(i1.y > 0) { tx1 = i1.x; tz1 = i1.y; } else { tx1 = i2.x; tz1 = i2.y; } }
				if(tz2 < nearz) { if(i1.y > 0) { tx2 = i1.x; tz2 = i1.y; } else { tx2 = i2.x; tz2 = i2.y; } }
			}
			/* Faire la transformation de perspective */
			float xscale1 = ANGLE_H / tz1, yscale1 = ANGLE_V / tz1;    int x1 = WIN_W/2 - (int)(tx1 * xscale1);
			float xscale2 = ANGLE_H / tz2, yscale2 = ANGLE_V / tz2;    int x2 = WIN_W/2 - (int)(tx2 * xscale2);
			if(x1 >= x2 || x2 < now.sx1 || x1 > now.sx2) continue; // Rendre seulement si c'est visible
			/* Acquérir les hauteurs de plancher et de plafond, par rapport à la vue du joueur */
			float yceil  = sect->ceil  - doom->player.where.z;
			float yfloor = sect->floor - doom->player.where.z;
			/* Vérifiez le type de bord. voisin = -1 signifie mur, autre = frontière entre deux secteurs. */
			int neighbor = sect->neighbors[s];
			float nyceil=0, nyfloor=0;
			if(neighbor >= 0) // Un autre secteur apparaît-il sur ce portail?
			{
				nyceil  = doom->sectors[neighbor].ceil  - doom->player.where.z;
				nyfloor = doom->sectors[neighbor].floor - doom->player.where.z;
			}
			/* Projeter nos hauteurs de plafond et de plancher en coordonnées d'écran (coordonnée en Y) */
			#define Yaw(y,z) (y + z*doom->player.yaw)
			int y1a  = WIN_H/2 - (int)(Yaw(yceil, tz1) * yscale1),  y1b = WIN_H/2 - (int)(Yaw(yfloor, tz1) * yscale1);
			int y2a  = WIN_H/2 - (int)(Yaw(yceil, tz2) * yscale2),  y2b = WIN_H/2 - (int)(Yaw(yfloor, tz2) * yscale2);
			/* Même chose pour le secteur voisin */
			int ny1a = WIN_H/2 - (int)(Yaw(nyceil, tz1) * yscale1), ny1b = WIN_H/2 - (int)(Yaw(nyfloor, tz1) * yscale1);
			int ny2a = WIN_H/2 - (int)(Yaw(nyceil, tz2) * yscale2), ny2b = WIN_H/2 - (int)(Yaw(nyfloor, tz2) * yscale2);

			/* Rendu du mur */
			int beginx = max(x1, now.sx1), endx = min(x2, now.sx2);
			for(int x = beginx; x <= endx; ++x)
			{
				/* Calculez la coordonnée Z pour ce point. (Utilisé uniquement pour l'éclairage.) */
				int z = ((x - x1) * (tz2-tz1) / (x2-x1) + tz1) * 8;
				/* Acquérir les coordonnées Y pour notre plafond et le sol pour cette coordonnée X. Les pince. */
				int ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a, cya = clamp(ya, ytop[x],ybottom[x]); // top
				int yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b, cyb = clamp(yb, ytop[x],ybottom[x]); // bottom

				/* Render plafond: tout ce qui dépasse la hauteur de plafond de ce secteur. */
				ft_print_x_wall2(doom, x, ytop[x], cya-1, 0x111111 ,0x222222,0x111111);
				/* Render floor: tout en dessous de la hauteur de plancher de ce secteur. */
				ft_print_x_wall2(doom, x, cyb+1, ybottom[x], 0x0000FF,0x0000AA,0x0000FF);

				/* Y a-t-il un autre secteur derrière ce bord? */
				if(neighbor >= 0)
				{
					/* Pareil pour le sol et le plafond */
					int nya = (x - x1) * (ny2a-ny1a) / (x2-x1) + ny1a, cnya = clamp(nya, ytop[x],ybottom[x]);
					int nyb = (x - x1) * (ny2b-ny1b) / (x2-x1) + ny1b, cnyb = clamp(nyb, ytop[x],ybottom[x]);
					/* Si notre plafond est plus élevé que leur plafond, rendez mur supérieur */
					unsigned r1 = 0x010101 * (255-z), r2 = 0x040007 * (31-z/8);
					ft_print_x_wall2(doom, x, cya, cnya-1, 0, x==x1||x==x2 ? 0 : r1, 0); // Entre notre et leur plafond
					ytop[x] = clamp(max(cya, cnya), ytop[x], WIN_H-1);   // Réduire la fenêtre restante au-dessous de ces plafonds
					/* If our floor is lower than their floor, render bottom wall */
					ft_print_x_wall2(doom, x, cnyb+1, cyb, 0, x==x1||x==x2 ? 0 : r2, 0); // Between their and our floor
					ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]); // Shrink the remaining window above these floors
				}
				else
				{
					/* Il n'y a pas de voisin. Rendu du mur du haut (cya = niveau du plafond) vers le bas (cyb = niveau du sol). */
					unsigned r = 0x010101 * (255-z);
					ft_print_x_wall2(doom, x, cya, cyb, 0, x==x1||x==x2 ? 0 : r, 0);
				}
			}
			/* Schedule the neighboring sector for rendering within the window formed by this wall. */
			if(neighbor >= 0 && endx >= beginx && (head+MaxQueue+1-tail)%MaxQueue)
			{
				*head = (struct item) { neighbor, beginx, endx };
				if(++head == queue+MaxQueue) head = queue;
			}
		} // for s in sector's edges
		++renderedsectors[now.sectorno];
    } while(head != tail); // rendre tous les autres secteurs en file d'attente
}



void	ft_draw_sectors(t_doom *doom, t_raycasting *r, int *render_sector)
{
	while(r->head != r->tail)
	{
		/* Choisissez un secteur et une tranche dans la file d'attente pour dessiner */
		r->now = *r->tail;
		if (++r->tail == r->wait + MAX_WAIT)
			r->tail = r->wait;
		// Odd = toujours rendu, 0x20 = abandonner
		if (render_sector[r->now.sector] & 0x21)
			continue;
		++render_sector[r->now.sector];
		r->sect = &doom->sectors[r->now.sector];
		/* Rendu chaque mur de ce secteur qui fait face au joueur. */
		r->i = -1;
		// pour r.i dans les bords du secteur
		while (++r->i < r->sect->pts)
		{
			/* Acquérir les coordonnées x, y des deux extrémités (sommets) de cette arête du secteur */
			r->v1.x = r->sect->vertex[r->i].x - doom->player.where.x;
			r->v1.y = r->sect->vertex[r->i].y - doom->player.where.y;
			r->v2.x = r->sect->vertex[r->i + 1].x - doom->player.where.x;
			r->v2.y = r->sect->vertex[r->i + 1].y - doom->player.where.y;
			/* Faites-les pivoter autour de la vue du joueur */
			r->p_cos = doom->player.anglecos;
			r->p_sin = doom->player.anglesin;
			r->t1.x = r->v1.x * r->p_sin - r->v1.y * r->p_cos;
			r->t1.y = r->v1.x * r->p_cos + r->v1.y * r->p_sin;
			r->t2.x = r->v2.x * r->p_sin - r->v2.y * r->p_cos;
			r->t2.y = r->v2.x * r->p_cos + r->v2.y * r->p_sin;
			/* Le mur est-il au moins partiellement devant le joueur? */
			if(r->t1.y <= 0 && r->t2.y <= 0)
				continue;
			/* Le mur est-il au moins partiellement devant le joueur? */
			if(r->t1.y <= 0 || r->t2.y <= 0)
			{
				// Trouver une intersection entre le mur et les bords approximatifs de la vue du joueur
				r->near.x = -0.00001;
				r->near.y = 0.0001;
				r->far.x = -20.0;
				r->far.y = 5.0;
				r->i1 = ft_intersect_lines(r->t1, r->t2, r->near, r->far);r->near.x *= -1;
				r->far.x *= -1;
				r->i2 = ft_intersect_lines(r->t1, r->t2, r->near, r->far);
				if (r->t1.y < r->near.y)
				{
					if (r->i1.y > 0)
					{
						r->t1.x = r->i1.x;
						r->t1.y = r->i1.y;
					}
					else
					{
						r->t1.x = r->i2.x;
						r->t1.y = r->i2.y;
					}
				}
				if (r->t2.y < r->near.y)
				{
					if (r->i1.y > 0)
					{
						r->t2.x = r->i1.x;
						r->t2.y = r->i1.y;
					}
					else
					{
						r->t2.x = r->i2.x;
						r->t2.y = r->i2.y;
					}
				}
			}
			/* Faire la transformation de perspective */
			r->scale1.x = ANGLE_H / r->t1.y;
			r->scale1.y = ANGLE_V / r->t1.y;
			r->scale2.x = ANGLE_H / r->t2.y;
			r->scale2.y = ANGLE_V / r->t2.y;
			r->lim_x.x = (WIN_W / 2) - (int)(r->t1.x * r->scale1.x);
			r->lim_x.y = (WIN_W / 2) - (int)(r->t2.x * r->scale2.x);
			// Rendre seulement si c'est visible
			if(r->lim_x.x >= r->lim_x.y || r->lim_x.x > r->now.x2 || r->lim_x.y < r->now.x1)
				continue;
			/* Acquérir les hauteurs de plancher et de plafond, par rapport à la vue du joueur */
			r->y_ceil = r->sect->ceil - doom->player.where.z;
			r->y_floor = r->sect->floor - doom->player.where.z;
			/* Vérifiez le type de bord. voisin = -1 signifie mur, autre = frontière entre deux secteurs. */
			r->neighbor = r->sect->neighbors[r->i];
			r->ny_ceil = 0;
			r->ny_floor = 0;
			// Un autre secteur apparaît-il sur ce portail?
			if(r->neighbor >= 0)
			{
				r->ny_ceil  = doom->sectors[r->neighbor].ceil  - doom->player.where.z;
				r->ny_floor = doom->sectors[r->neighbor].floor - doom->player.where.z;
			}
			/* Projeter nos hauteurs de plafond et de plancher en coordonnées d'écran (coordonnée en Y) */
			r->y1.x = (WIN_H / 2) - (int)((doom->player.yaw * r->t1.y + r->y_ceil) * r->scale1.y);
			r->y1.y = (WIN_H / 2) - (int)((doom->player.yaw * r->t1.y + r->y_floor) * r->scale1.y);
			r->y2.x = (WIN_H / 2) - (int)((doom->player.yaw * r->t2.y + r->y_ceil) * r->scale2.y);
			r->y2.y = (WIN_H / 2) - (int)((doom->player.yaw * r->t2.y + r->y_floor) * r->scale2.y);
			/* Même chose pour le secteur voisin */
			r->n_y1.x = (WIN_H / 2) - (int)((doom->player.yaw * r->t1.y + r->ny_ceil) * r->scale1.y);
			r->n_y1.y = (WIN_H / 2) - (int)((doom->player.yaw * r->t1.y + r->ny_floor) * r->scale1.y);
			r->n_y2.x = (WIN_H / 2) - (int)((doom->player.yaw * r->t2.y + r->ny_ceil) * r->scale2.y);
			r->n_y2.y = (WIN_H / 2) - (int)((doom->player.yaw * r->t2.y + r->ny_floor) * r->scale2.y);
			/* Rendu du mur */
			r->x_start_end.x = (r->lim_x.x > r->now.x1) ? r->lim_x.x : r->now.x1;
			r->x_start_end.y = (r->lim_x.y < r->now.x2) ? r->lim_x.y : r->now.x2;
			r->x = r->x_start_end.x - 1;
			while (++r->x <= r->x_start_end.y)
			{
				/* Calculez la coordonnée Z pour ce point. (Utilisé uniquement pour l'éclairage.) */
				r->z = ((r->x - r->lim_x.x) * (r->t2.y-r->t1.y) / (r->lim_x.y-r->lim_x.x) + r->t1.y) * 8;
				/* Acquérir les coordonnées Y pour notre plafond et le sol pour cette coordonnée X. Les pince. */
				// top
				r->y.x = (r->x - r->lim_x.x) * (r->y2.x - r->y1.x) / (r->lim_x.y - r->lim_x.x) + r->y1.x;
				r->c_y.x = ft_clamp(r->y.x, r->y_top[r->x], r->y_bot[r->x]);
				// bottom
				r->y.y = (r->x - r->lim_x.x) * (r->y2.y - r->y1.y) / (r->lim_x.y - r->lim_x.x) + r->y1.y;
				r->c_y.y = ft_clamp(r->y.y, r->y_top[r->x], r->y_bot[r->x]);

				/* Render plafond: tout ce qui dépasse la hauteur de plafond de ce secteur. */
//				ft_print_x_wall2(doom, r.x, r.y_top[r.x], r.c_y.x-1, 0x111111 ,0x222222,0x111111);
				ft_print_x_wall(doom, r->x, r->y_top[r->x], r->c_y.x-1, 0x222222);

				/* Render floor: tout en dessous de la hauteur de plancher de ce secteur. */
//				ft_print_x_wall2(doom, r.x, r.c_y.y+1, r.y_bot[r.x], 0x0000FF,0x0000AA,0x0000FF);
				ft_print_x_wall(doom, r->x, r->c_y.y+1, r->y_bot[r->x], 0x0000AA);

				/* Y a-t-il un autre secteur derrière ce bord? */
				if(r->neighbor >= 0)
				{
					/* Pareil pour le sol et le plafond */
					r->n_y.x = (r->x - r->lim_x.x) * (r->n_y2.x - r->n_y1.x) / (r->lim_x.y - r->lim_x.x) + r->x;
					r->c_n_y.x = ft_clamp(r->n_y.x, r->y_top[r->x],r->y_bot[r->x]);
					r->n_y.y = (r->x - r->lim_x.x) * (r->n_y2.y-r->n_y1.y) / (r->lim_x.y-r->lim_x.x) + r->n_y1.y;
					r->c_n_y.y = ft_clamp(r->n_y.y, r->y_top[r->x],r->y_bot[r->x]);
					r->color_ceil = 0x010101 * (255 - r->z);
					r->color_floor = 0x040007 * (31 - r->z / 8);
					/* Si notre plafond est plus élevé que leur plafond, rendez mur supérieur */
					// Entre notre et leur plafond
					ft_print_x_wall(doom, r->x, r->c_y.x, r->c_n_y.x - 1, r->color_ceil);
//					ft_print_x_wall2(doom, r.x, r.c_y.x, r.c_n_y.x-1, 0, r.x==r.lim_x.x||r.x==r.lim_x.y ? 0 : r.color_ceil, 0);
					// Réduire la fenêtre restante au-dessous de ces plafonds
					if (r->c_y.x < r->c_n_y.x)
						r->c_y.x = r->c_n_y.x;
					r->y_top[r->x] = ft_clamp(r->c_y.x, r->y_top[r->x], WIN_H-1);
					/* Si notre sol est plus bas que le sol, rendez le mur du bas */
					// Entre leur et notre sol
					ft_print_x_wall(doom, r->x, r->c_n_y.y + 1, r->c_y.y, r->color_floor);
//					ft_print_x_wall2(doom, r.x, r.c_n_y.y+1, r.c_y.y, 0, r.x==r.lim_x.x||r.x==r.lim_x.y ? 0 : r.color_floor, 0);
					//Réduire la fenêtre restante au-dessus de ces sol
					if (r->c_y.y > r->c_n_y.y)
						r->c_y.y = r->c_n_y.y;
					r->y_bot[r->x] = ft_clamp(r->c_y.y, 0, r->y_bot[r->x]);
				}
				else
				{
					/* Il n'y a pas de voisin. Rendu du mur du haut (cya = niveau du plafond) vers le bas (cyb = niveau du sol). */
					r->color_wall = 0x010101 * (255 - r->z);
					ft_print_x_wall(doom, r->x, r->c_y.x, r->c_y.y, r->color_wall);
//					ft_print_x_wall2(doom, r.x, r.c_y.x, r.c_y.y, 0, r.x==r.lim_x.x||r.x==r.lim_x.y ? 0 : t, 0);
				}
			}
			/* Planifiez le rendu du secteur voisin dans la fenêtre formée par ce mur. */
			if (r->neighbor >= 0 && r->x_start_end.y >= r->x_start_end.x && (r->head + MAX_WAIT + 1 - r->tail) % MAX_WAIT)
			{
				*r->head = (t_window){r->neighbor, r->x_start_end.x, r->x_start_end.y};
				if (++r->head == r->wait + MAX_WAIT)
					r->head = r->wait;
			}
		}
		++render_sector[r->now.sector];
    }
}