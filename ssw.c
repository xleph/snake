#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>

struct cxt {
Display *dis;
int screen;
Window win;
GC gc;

XEvent event;
KeySym key;
char text[255];
};

struct cxt context[20];

unsigned long LHEX(char v[7]){
int r, g, b;
r = 16*(v[1] - 48 - (((v[1] - 48)>>5)*39)) + v[2] - 48 - (((v[2] - 48)>>5)*39);
g = 16*(v[3] - 48 - (((v[3] - 48)>>5)*39)) + v[4] - 48 - (((v[4] - 48)>>5)*39);
b = 16*(v[5] - 48 - (((v[5] - 48)>>5)*39)) + v[6] - 48 - (((v[6] - 48)>>5)*39);
return b + (g<<8) + (r<<16);
}

unsigned long HEX(char v[7]){
int r, g, b;
r = 16*(v[1] - 48 - (((v[1] - 48)>>4)*7)) + v[2] - 48 - (((v[2] - 48)>>4)*7);
g = 16*(v[3] - 48 - (((v[3] - 48)>>4)*7)) + v[4] - 48 - (((v[4] - 48)>>4)*7);
b = 16*(v[5] - 48 - (((v[5] - 48)>>4)*7)) + v[6] - 48 - (((v[6] - 48)>>4)*7);
return b + (g<<8) + (r<<16);
}

unsigned long RGB(int r, int g, int b){
return b + (g<<8) + (r<<16);
}

struct cache {
char t;
char b;
int txt;
int x;
int y;
};

void XI(char root, const char *title, 
					   const char *subtitle, 
					   int height, int width,
					   int sx, int sy, char d) {
context[d].dis=XOpenDisplay((char *)0);
context[d].screen=DefaultScreen(context[d].dis);

	if (root) {
	context[d].win=RootWindow(context[d].dis, context[d].screen);
	} else {
	context[d].win=XCreateWindow(context[d].dis, DefaultRootWindow(context[d].dis), sx, sy, height, width, 
	5, 0, 0, 0, 0, (XSetWindowAttributes *)0);
	
	XSetStandardProperties(context[d].dis, context[d].win, title, subtitle, None, NULL, 0, NULL);
	XSelectInput(context[d].dis, context[d].win, ExposureMask|ButtonPressMask|KeyPressMask);
	}

context[d].gc=XCreateGC(context[d].dis, context[d].win, 0, 0);
XClearWindow(context[d].dis, context[d].win);
XMapRaised(context[d].dis, context[d].win);
}

void Clean(char d){
XFreeGC(context[d].dis, context[d].gc);
XDestroyWindow(context[d].dis, context[d].win);
XCloseDisplay(context[d].dis);
}

void RegionFill(int x, int y, int h, int w, unsigned long color, char d){
XSetForeground(context[d].dis, context[d].gc, color);
XFillRectangle(context[d].dis, context[d].win, context[d].gc, x , y, h, w);
}

void RegionScarf(int x, int y, int h, int w, unsigned long color, char d){
XSetForeground(context[d].dis, context[d].gc, color);
XDrawRectangle(context[d].dis, context[d].win, context[d].gc, x-1, y-1, h, w);
}

void Point(int x, int y, unsigned long color, char d) {
XSetForeground(context[d].dis, context[d].gc, color);
XDrawPoint(context[d].dis, context[d].win, context[d].gc, x, y);
}

void Eve(struct cache *cc, char d){
char kill = 0; 

cc->t =   0;
cc->b =   0;
cc->txt = 0;
cc->x =   0;
cc->y =   0;

XNextEvent(context[d].dis, &context[d].event);
	if (context[d].event.type==Expose) {
	cc->t = 3;
	}
        if (context[d].event.type==ButtonPress) {
        cc->t = 2;
        cc->b = context[d].event.xbutton.button;
        cc->x = context[d].event.xbutton.x;
        cc->y = context[d].event.xbutton.y;
        }
        if (context[d].event.type==2) {
	XLookupString(&context[d].event.xkey,context[d].text,255,&context[d].key,0);
                if (context[d].text[0]==27) { // failsafe quit
                        kill = 1;
                } else {
                cc->t = 1;
                cc->txt = context[d].key;
                }
        }
	if (kill){
	Clean(d);
	exit(0);
	}
}

unsigned int WW(char d) {
XWindowAttributes attr;
XGetWindowAttributes(context[d].dis, context[d].win, &attr);
return attr.width;
}

unsigned int WH(char d) {
XWindowAttributes attr;
XGetWindowAttributes(context[d].dis, context[d].win, &attr);
return attr.height;
}

/*struct options {
float t;
int x;
int y;
char d;
}

int white(struct options i) {
XSetForeground(context[i.d].dis, context[i.d].gc, color);
XDrawPoint(context[i.d].dis, context[i.d].win, context[i.d].gc, x, y);
}

int black(struct options i) {
XSetForeground(context[i.d].dis, context[i.d].gc, color);
XDrawPoint(context[i.d].dis, context[i.d].win, context[i.d].gc, x, y);
} 

come back to this
use void p = (void)function(struct options input);
to garner input from any function and return a color value
*/ 

int Pend(char d){
return XPending(context[d].dis);
}

void XI_(void){
XInitThreads();
}

void XX(char op) {
exit(op);
}
