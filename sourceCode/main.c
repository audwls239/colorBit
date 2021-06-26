#include "../headerFile/header.h"


void setup(void) {
	char fileName[100] = "./image.jpg";
	
	GtkWidget* window;
	GtkWidget* mainContainer;
	GtkWidget* imgWidget;

	{
		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		mainContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
		gtk_container_add(GTK_CONTAINER(window), mainContainer);
	}
	
	GdkPixbuf* src;
	GdkPixbuf* buf;

	{
		src = gdk_pixbuf_new_from_file_at_size(fileName, 400, 400, NULL);
	}
	
	buf = imageDownSampling(src, 2);
	imgWidget = gtk_image_new_from_pixbuf(buf);
	gtk_container_add(GTK_CONTAINER(mainContainer), imgWidget);

	buf = imageDownSampling(src, 3);
	imgWidget = gtk_image_new_from_pixbuf(buf);
	gtk_container_add(GTK_CONTAINER(mainContainer), imgWidget);

	buf = imageDownSampling(src, 4);
	imgWidget = gtk_image_new_from_pixbuf(buf);
	gtk_container_add(GTK_CONTAINER(mainContainer), imgWidget);

	gtk_widget_show_all(window);
}

int main(int argc, char** args) {
	gtk_init(&argc, &args);
	
	setup();
	
	gtk_main();
	return 0;
}