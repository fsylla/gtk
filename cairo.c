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


void draw_line(cairo_t *cr, double x1, double y1, double x2, double y2)
{
  cairo_move_to(cr, x1, y1);
  cairo_line_to(cr, x2, y2);
  cairo_stroke(cr);
}


int draw_arc(cairo_t *cr, double x1, double y1, double x2, double y2, double r)
{
    double xc;
    double yc;

    double xm   = (x1 + x2) / 2;
    double ym   = (y1 + y2) / 2;
    
    double a1;
    double a2;
    
    double g;                           // distance (P2 - P1) / 2
    double gg   = (x2 - xm) * (x2 - xm) + (y2 - ym) * (y2 - ym);
    double h;                           // distance (P2 - PM)
    double rr   = r * r;

    int rc      = 0;

    if (rr < gg) {
        printf("draw_arc: radius %f too small\n", r);
        rc      = 1;
    } else {
        h       = sqrt(rr - gg);
        g       = sqrt(gg);

        xc      = xm + h * (y2 - ym) / g;
        yc      = ym + h * (x2 - xm) / g;

        a1      = atan2(y1 - yc, x1 - xc);
        a2      = atan2(y2 - yc, x2 - xc);

        printf("draw_arc: a1 = %f a2 = %f\n", a1, a2);
        printf("draw_arc: xc = %f yc = %f\n", xc, yc);
 
        if (r > 0) {
            cairo_arc(cr, xc, yc, r, a1, a2);
        } else {
            cairo_arc_negative(cr, xc, yc, -r, a1, a2);
        }

        cairo_stroke(cr);
    }

    return(rc);
}


static void do_drawing(cairo_t *cr, GtkWidget *widget)
{
  GtkWidget *win = gtk_widget_get_toplevel(widget);
  
  int width, height;
  gtk_window_get_size(GTK_WINDOW(win), &width, &height);
  
  cairo_set_line_width(cr, 4);  
  cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
  
  draw_line(cr, 220, 100, 580, 100);
  draw_line(cr, 220, 500, 580, 500);

  draw_arc(cr, 220, 100, 220, 500, -200);
  draw_arc(cr, 580, 100, 580, 500, 200);
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


