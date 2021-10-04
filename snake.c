#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "ssw.h"
#include "bezier.h"
 
int main() {
int seed, add;
seed = (int)&add;
srand(seed);
struct cache c;
char xsnake[255];
char ysnake[255];
int xsnak[255];
int ysnak[255];
char dir = 3;
int i, j, secsize;
xsnake[0] = 19;
ysnake[0] = 15;
xsnake[1] = 20;
ysnake[1] = 15;
xsnake[2] = 0;
ysnake[2] = 0;
char xp = rand()%38 + 1;
char yp = rand()%28 + 1;
XI(0, "Snek", "Snek", 400, 300, 0, 0, 0);
Eve(&c, 0);
RegionFill(0, 0, WW(0), WH(0), RGB(0, 0, 0), 0);

	while (1) {

	RegionFill(0, 0, WW(0), WH(0), RGB(0, 0, 0), 0);
	usleep(100000);	
	secsize = WW(0)/40;
	RegionScarf(secsize, secsize, WW(0)-2*secsize, WW(0)*3/4-2*secsize, RGB(255, 255, 255), 0);

		while (Pend(0)) {
		Eve(&c, 0);
		}

		if (c.t==1) {

			if (c.txt==65362&&dir!=0&&dir!=2) {
			dir = 0;
			}
			if (c.txt==65363&&dir!=1&&dir!=3) {
			dir = 1;
			}
			if (c.txt==65364&&dir!=0&&dir!=2) {
			dir = 2;
			}
			if (c.txt==65361&&dir!=1&&dir!=3) {
			dir = 3;
			}

		}

		i = 2;
		
		while (xsnake[i]) {
		i++;
		}

		while (i - 1) {
		i--;
		xsnake[i] = xsnake[i - 1];
		ysnake[i] = ysnake[i - 1];
		}

		if (dir==0) {
		ysnake[0]--;
		}
		if (dir==1) {
		xsnake[0]++;
		}
		if (dir==2) {
		ysnake[0]++;
		}
		if (dir==3) {
		xsnake[0]--;
		}

		if (!xsnake[0]||!ysnake[0]||xsnake[0]>38||ysnake[0]>28) {
		goto gg;
		}

		i = 2;

		while (xsnake[i]) {
		i++;
		}

		j = i;

		while (i) {
			if (xsnake[0]==xsnake[i]&&ysnake[0]==ysnake[i]) {
			goto gg;
			}
		i--;
		}

		if (xsnake[0]==xp&&ysnake[0]==yp) {
			while (i < j) {
				xp = rand()%38 + 1;
				yp = rand()%28 + 1;
				i = 0;
				while (xsnake[i++]) {
					if (xsnake[i]==xp&&ysnake[i]==yp) {
					break;
					}
				}
				
			}
				
		i = 2;
			while (xsnake[i]) {
			i++;
			}
		xsnake[i] = xsnake[i - 1];
		ysnake[i] = ysnake[i - 1];
		xsnake[i + 1] = 0;
		ysnake[i + 1] = 0;
		}
		
		for (i = 0; xsnake[i]; i++) {
		xsnak[i] = xsnake[i] * secsize;
		ysnak[i] = ysnake[i] * secsize;
		}

	xsnak[i + 1] = 0;
	ysnak[i + 1] = 0;

		for (i = 0; xsnake[i]; i++) {
		xsnak[i]+=secsize/2;
		ysnak[i]+=secsize/2;
		}
	drawcurve(RGB(0, 255, 255), xsnak, ysnak, i, secsize, (i*secsize)>>1, 0);
	RegionFill(xp*secsize, yp*secsize, secsize, secsize, RGB(255, 255, 255), 0);
	}
gg:
Clean(0);
printf("In this world, nothing can be said to be certain... \n");
usleep(1000000);
printf("Except Death and Taxes\n");
XX(0);
}
