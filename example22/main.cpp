#include <iostream>
#include <gtkmm.h>


// Scale used for the demonstration
#define         SCALE           8.



int main(int argc, char* argv[])
{
    // Initialize gtkmm library
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "www.lucidarme.me");


    // Load the source image
    Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_file("gtk_icon.png");
    int width=image->get_width();
    int height=image->get_height();
    //image2=image; // = image->scale_simple(image->get_width()*scale,image->get_height()*scale,Gdk::INTERP_NEAREST);


    // __________________________
    // ::: Create output1.png :::

    // Create, fill and save the destination image
    Glib::RefPtr<Gdk::Pixbuf> image2 = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB,true,8,width*SCALE,height*SCALE);
    image2->fill(0x0000FFA0);
    image2->save("output1.png","png");
    std::cout << "output1.png created" << std::endl;


    // __________________________
    // ::: Create output2.png :::

    // Scale and copy the first image in the destination image with several type of scalin method
    // Top left
    image->scale(image2,
                 10,10,
                 (width*SCALE)/2.-10,(height*SCALE)/2-10,
                 0,0,
                 SCALE,SCALE,
                 Gdk::INTERP_NEAREST);
    // Top right
    image->scale(image2,
                 (width*SCALE)/2.+10,10,
                 (width*SCALE)/2.-20,(height*SCALE)/2.-10,
                 0,0,
                 SCALE,SCALE,
                 Gdk::INTERP_HYPER);
    // Bottom left
    image->scale(image2,
                 10,(height*SCALE)/2.+10,
                 (width*SCALE)/2.-10,(height*SCALE)/2.-20,
                 0,0,
                 SCALE,SCALE,
                 Gdk::INTERP_BILINEAR);
    // Bottom right
    image->scale(image2,
                 (width*SCALE)/2.+10,(height*SCALE)/2.+10,
                 (width*SCALE)/2.-20,(height*SCALE)/2.-20,
                 0,0,
                 SCALE,SCALE,
                 Gdk::INTERP_TILES);
    // Save the output image
    image2->save("output2.png","png");
    std::cout << "output2.png created" << std::endl;


    // __________________________
    // ::: Create output3.png :::

    // Scale and translate the source image
    image2->fill(0x70707070);
    image->scale(image2,
                 20,20,
                 width*SCALE-40,height*SCALE-40,
                 -width*SCALE/2.,-height*SCALE/2.,
                 SCALE*2,SCALE*2,
                 Gdk::INTERP_BILINEAR);
    image2->save("output3.png","png");
    std::cout << "output3.png created" << std::endl;

    // __________________________
    // ::: Create output4.png :::

    // Scale and translate the source image
    image2->fill(0x70707070);
    image->scale(image2,
				 image2->get_width()/2.,image2->get_height()/2.,
				 image2->get_width()/2.,image2->get_height()/2.,
				 -width*SCALE,-height*SCALE,
                 SCALE*2,SCALE*2,
                 Gdk::INTERP_TILES);
    image2->save("output4.png","png");
    std::cout << "output4.png created" << std::endl;
    return 0;
}
