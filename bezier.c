#include <ssw.h>

#define uint unsigned int
#define uchar unsigned char


float FISR(float n) { // this is not my code
	float xhalf = 0.5f * n;
	int i = *(int*)&n;            // store floating-point bits in integer
	i = 0x5f375a85 - (i >> 1);    // initial guess for Newton's method
	n = *(float*)&i;              // convert new bits into float
	n = n*(1.5f - xhalf*n*n);     // One round of Newton's method
	return n;
} // this is not my code

int adjpow(uint n) {
int p;
char i = sizeof(p)*8-1;
	while ((n&((~0)<<i))==0) {
	i--;
	}
i--;
return ((n>>i)+((n>>i)&1))<<i;
}

void drawcurve(unsigned long rgb, uint *x, uint *y, uchar n, int sec, int size, char win) {
uchar i, j;
uint slice[n + 1];
float t, tc, snbl, totx, toty;
tc = (float)1.0/adjpow(size);
int xc;
int yc;
snbl = 1;

slice[0] = 1;
	for (i = 1; i < (n + 1)/2; i++) {
	slice[i] = slice[i - 1] * (n - i)/i;
	}

	for (i = n - 1; i > (n - 1)/2; i--) {
	slice[i] = slice[n - i - 1];
	}

	for (t = 0; (uint)t==0; t+=tc+tc*(t>0.25||t>0.75)) {
		totx=0;
		toty=0;
		i  = 0;
		while (i < n) { // n-1 times (for each term)
		snbl = 1;
			for (j = 0; j < n - i - 1; j++) {
			snbl*=(1 - t);
			}
			for (j = 0; j < i; j++) {
			snbl*=t;
			}

		snbl*=slice[i];

		totx+=x[i]*snbl;
		toty+=y[i]*snbl;
		i++;
		}
		
		xc = -1*sec/2;
		while (xc < sec/2) {
		yc = (sec*sec/4-xc*xc)*FISR(sec*sec/4-xc*xc);
		RegionFill((uint)totx+xc, (uint)toty+yc, 1, 1, rgb, win);
		RegionFill((uint)totx+xc, (uint)toty-yc, 1, 1, rgb, win);
		xc++;
		}
	}
}
