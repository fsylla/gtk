#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>

static void do_drawing(cairo_t *, GtkWidget *);

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{  
  do_drawing(cr, widget);  

  return FALSE;
}

static void do_drawing(cairo_t *cr, GtkWidget *widget)
{
  GtkWidget *win = gtk_widget_get_toplevel(widget);
  
  int width, height;
  gtk_window_get_size(GTK_WINDOW(win), &width, &height);
  
  cairo_set_line_width(cr, 4);  
  cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
 
  cairo_move_to(cr, 220, 100);
  cairo_line_to(cr, 580, 100);
  cairo_stroke(cr);

  cairo_move_to(cr, 220, 500);
  cairo_line_to(cr, 580, 500);
  cairo_stroke(cr);

  cairo_arc(cr, 220, 300, 200, 0.5 * M_PI, 1.5 * M_PI);
  cairo_stroke(cr);
  
  cairo_arc(cr, 580, 300, 200, 1.5 * M_PI, 0.5 * M_PI);
  cairo_stroke(cr);
}


int main (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *darea;
  
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER(window), darea);

  g_signal_connect(G_OBJECT(darea), "draw", 
      G_CALLBACK(on_draw_event), NULL);
  g_signal_connect(G_OBJECT(window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600); 
  gtk_window_set_title(GTK_WINDOW(window), "cairo");

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}


