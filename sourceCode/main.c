#include "../headerFile/header.h"

void setup(void) {
	GtkWidget* window;
	GtkWidget* mainContainer;
	GtkWidget* imgWidget;
	
	GdkPixbuf* bitMap;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	mainContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	
	bitMap = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, 20, 20);
	
	int i, j;
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++) {
			put_pixel(bitMap, i, j, 255, 0, 0, 0);
		}
	}
	
	imgWidget = gtk_image_new_from_pixbuf(bitMap);
	
	gtk_container_add(GTK_CONTAINER(window), mainContainer);
	gtk_container_add(GTK_CONTAINER(mainContainer), imgWidget);

	gtk_widget_show_all(window);
}

int main(int argc, char** args) {
	gtk_init(&argc, &args);
	
	setup();
	
	gtk_main();
	return 0;
}