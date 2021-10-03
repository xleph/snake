extern struct cache {
char t;
char b;
int txt;
int x;
int y;
};
 
extern unsigned long LHEX(char v[7]); /* These could be regular longs */
extern unsigned long HEX(char v[7]);  /* but don't want to change now */
extern unsigned long RGB(int r, int g, int b);

extern void XI(char root, const char *title, const char *subtitle, int height, int width, int sx, int sy, char d);
extern void Clean(char d);

extern void RegionFill(int x, int y, int h, int w, unsigned long color, char d);
extern void RegionScarf(int x, int y, int h, int w, unsigned long color, char d);
extern void Eve(struct cache *cc, char d);
extern unsigned int WW(char d);
extern unsigned int WH(char d);

extern int Pend(char d);

extern void XI_(void);
extern void XX(char op);
