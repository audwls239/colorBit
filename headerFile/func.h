#ifndef _FUNC_
#define _FUNC_

void put_pixel(GdkPixbuf *pixbuf, int x, int y, guchar red, guchar green, guchar blue, guchar alpha);

guchar* get_pixel(GdkPixbuf *pixbuf, int x, int y);

typedef enum {
	ROTATE_90,
	ROTATE_180,
	ROTATE_270
} rotateOption;

GdkPixbuf* rotateImage(GdkPixbuf* src, rotateOption input);

GdkPixbuf* imageDownSampling(GdkPixbuf* src, int scale);

typedef enum {
	SIZE_SINGLE,
	SIZE_DOUBLE,
} sizeList;

GdkPixbuf* imageScailing(GdkPixbuf* src, sizeList size);

#endif