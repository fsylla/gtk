#include <cairo.h>
#include <gtk/gtk.h>

static void do_drawing(cairo_t *, GtkWidget *widget);

struct {
  cairo_surface_t *image;  
} glob;

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{      
  do_drawing(cr, widget);  

  return FALSE;
}

static void do_drawing(cairo_t *cr, GtkWidget *widget)
{
  cairo_set_source_surface(cr, glob.image, 10, 10);
  cairo_paint(cr);
}

static void load_image()
{        
  glob.image = cairo_image_surface_create_from_png("banner175.png"); 
}

static void draw_mark() 
{ 
  cairo_t *ic;
  ic = cairo_create(glob.image);
  cairo_set_font_size(ic, 11);
  
  cairo_set_source_rgb(ic, 0.9 , 0.9 , 0.9);
  cairo_move_to(ic, 20, 30);
  cairo_show_text(ic, " Beckov 2012 , (c) Jan Bodnar ");
  cairo_stroke(ic);   
}

int main (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *darea;
  
  load_image();
  draw_mark();

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), darea);

  g_signal_connect(G_OBJECT(darea), "draw", 
      G_CALLBACK(on_draw_event), NULL); 
  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 350, 250); 
  gtk_window_set_title(GTK_WINDOW(window), "Watermark");

  gtk_widget_show_all(window);

  gtk_main();
  
  cairo_surface_destroy(glob.image);

  return 0;
}

