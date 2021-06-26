#include "../headerFile/header.h"

void put_pixel(GdkPixbuf* pixbuf, int x, int y, guchar red, guchar green, guchar blue, guchar alpha)
{
    int width, height, rowstride, n_channels;
    guchar *pixels, *p;

    n_channels = gdk_pixbuf_get_n_channels(pixbuf);

    g_assert(gdk_pixbuf_get_colorspace(pixbuf) == GDK_COLORSPACE_RGB);
    g_assert(gdk_pixbuf_get_bits_per_sample(pixbuf) == 8);
    g_assert(gdk_pixbuf_get_has_alpha(pixbuf));
    g_assert(n_channels == 4);

    width = gdk_pixbuf_get_width(pixbuf);
    height = gdk_pixbuf_get_height(pixbuf);

    g_assert(0 <= x && x < width);
    g_assert(0 <= y && y < height);

    rowstride = gdk_pixbuf_get_rowstride(pixbuf);
    pixels = gdk_pixbuf_get_pixels(pixbuf);

    p = pixels + y * rowstride + x * n_channels;
    p[0] = red;
    p[1] = green;
    p[2] = blue;
    p[3] = alpha;
}

guchar* get_pixel(GdkPixbuf* pixbuf, int x, int y) {
    int width, height, rowstride, n_channels;
    guchar *pixels, *p;

    n_channels = gdk_pixbuf_get_n_channels(pixbuf);

    g_assert(gdk_pixbuf_get_colorspace(pixbuf) == GDK_COLORSPACE_RGB);
    g_assert(gdk_pixbuf_get_bits_per_sample(pixbuf) == 8);

    width = gdk_pixbuf_get_width(pixbuf);
    height = gdk_pixbuf_get_height(pixbuf);

    g_assert(0 <= x && x < width);
    g_assert(0 <= y && y < height);

    rowstride = gdk_pixbuf_get_rowstride(pixbuf);
    pixels = gdk_pixbuf_get_pixels(pixbuf);

    p = pixels + y * rowstride + x * n_channels;

    guchar* returnPixel;
    returnPixel = malloc(sizeof(guchar) * 4);

    returnPixel[0] = p[0];
    returnPixel[1] = p[1];
    returnPixel[2] = p[2];
	if (n_channels == 4) {
    	returnPixel[3] = p[3];
	}
	else {
		returnPixel[3] = 255;
	}

    return returnPixel;
}

GdkPixbuf* rotateImage(GdkPixbuf* src, rotateOption input) {
	int width, height;
	int x_pos, y_pos;
	guchar* pixel;
	
	width = 200;
	height = 200;
	
	GdkPixbuf* dest;
	dest = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, width, height);
	
	switch (input) {
		case ROTATE_90:
			for (y_pos = 0; y_pos < height; y_pos++) {
				for (x_pos = 0; x_pos < width; x_pos++) {
					pixel = get_pixel(src, x_pos, y_pos);
					put_pixel(dest, (height - 1) - y_pos, x_pos,
							  pixel[0],
							  pixel[1],
							  pixel[2],
							  pixel[3]);
				}
			}
			break;
		case ROTATE_180:
			for (y_pos = 0; y_pos < height; y_pos++) {
				for (x_pos = 0; x_pos < width; x_pos++) {
					pixel = get_pixel(src, x_pos, y_pos);
					put_pixel(dest, (width - 1) - x_pos, (height - 1) - y_pos,
							  pixel[0],
							  pixel[1],
							  pixel[2],
							  pixel[3]);
				}
			}
			break;
		case ROTATE_270:
			for (y_pos = 0; y_pos < height; y_pos++) {
				for (x_pos = 0; x_pos < width; x_pos++) {
					pixel = get_pixel(src, x_pos, y_pos);
					put_pixel(dest, (width - 1) - y_pos, (height - 1) - x_pos,
							  pixel[0],
							  pixel[1],
							  pixel[2],
							  pixel[3]);
				}
			}
			break;
	}
	return dest;
}

GdkPixbuf* imageDownSampling(GdkPixbuf* src, int scale) {
	int width, height;
	int x_pos, y_pos;

	GdkPixbuf* dest;
	guchar** result;
	guchar* color;
	
	width  = gdk_pixbuf_get_width(src);
	height = gdk_pixbuf_get_height(src);
	
	dest = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, width / scale, height / scale);
	result = malloc(sizeof(guchar*) * scale * scale);
	color = malloc(sizeof(guchar) * 4);
	
	for (y_pos = 0; y_pos < height / scale; y_pos++) {
		for (x_pos = 0; x_pos < width / scale; x_pos++) {
			int i, j;
			int num, average;
			
			for (num = 0; num < scale * scale; num++) {
				for (i = 0; i < scale; i++) {
					for (j = 0; j < scale; j++) {
						result[num] = get_pixel(src, x_pos * scale + i, y_pos * scale + j);
					}
				}
			}
			
			for (i = 0; i < scale * scale; i++) {
				for (j = 0; j < scale * scale; j++) {
					average = result[j][i];
				}
				average / scale * scale;
				color[i] = (guchar)average;
			}
			put_pixel(dest, x_pos, y_pos, color[0], color[1], color[2], color[3]);
			
			for (i = 0; i < scale * scale; i++) {
				free(result[i]);
			}
		}
	}
	free(color);
	return dest;

}

GdkPixbuf* imageScailing(GdkPixbuf* src, sizeList size) {
	int width, height;
	int x_pos, y_pos;
	GdkPixbuf* dest;
	guchar* color;

	width  = 200;
	height = 200;
	
	switch (size) {
		case SIZE_SINGLE:
			return src;
		case SIZE_DOUBLE:
			dest = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, width * 2, height * 2);
			
			for (y_pos = 0; y_pos < height; y_pos++) {
				for (x_pos = 0; x_pos < width; x_pos++) {
					color = get_pixel(src, x_pos, y_pos);
					put_pixel(dest, 
							  x_pos * 2, 
							  y_pos * 2, 
							  color[0], color[1], color[2], color[3]);
					put_pixel(dest, 
							  x_pos * 2 + 1, 
							  y_pos * 2, 
							  color[0], color[1], color[2], color[3]);
					put_pixel(dest, 
							  x_pos * 2, 
							  y_pos * 2 + 1, 
							  color[0], color[1], color[2], color[3]);
					put_pixel(dest, 
							  x_pos * 2 + 1, 
							  y_pos * 2 + 1, 
							  color[0], color[1], color[2], color[3]);
					free(color);
				}
			}
			return dest;
	}
}