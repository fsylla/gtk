#include <iostream>
#include <gtkmm.h>


// Scale used for the demonstration
#define         SCALE           8.



int main(int argc, char* argv[])
{
    // Initialize gtkmm library
    Glib::RefPtr<Gtk::Application>      app     = Gtk::Application::create(argc, argv, "www.lucidarme.me");

    // Load the source image
    Glib::RefPtr<Gdk::Pixbuf>           image   = Gdk::Pixbuf::create_from_file("gtk_icon.png");
    
    int                                 width   = image->get_width();
    int                                 height  = image->get_height();

    // Create, fill and save the destination image
    Glib::RefPtr<Gdk::Pixbuf>           image2  = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, true, 8, width * SCALE, height * SCALE);

    // Scale and translate the source image
    image2->fill(0x70707070);
    image->scale(image2,
                 20, 20,
                 width * SCALE -40, height * SCALE -40,
                 -width * SCALE / 2.0, -height * SCALE / 2.0,
                 SCALE * 2, SCALE * 2,
                 Gdk::INTERP_BILINEAR);

    image2->save("output.png","png");
    std::cout << "output.png created" << std::endl;

    return 0;
}

