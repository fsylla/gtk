/* gtkmm example Copyright (C) 2011 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "myarea.h"
#include <cairomm/context.h>
#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <glibmm/fileutils.h>
#include <iostream>

MyArea::MyArea()
{
    try
    {
        // The fractal image has been created by the XaoS program.
        // http://xaos.sourceforge.net
        m_image = Gdk::Pixbuf::create_from_file("image/fractal_image.png");
    }
    catch (const Gio::ResourceError& ex)
    {
        std::cerr << "ResourceError: " << ex.what() << std::endl;
    }
    catch (const Gdk::PixbufError& ex)
    {
        std::cerr << "PixbufError: " << ex.what() << std::endl;
    }

    // Show at least a quarter of the image.
    if (m_image)
        set_size_request(m_image->get_width() /2, m_image->get_height() /2);
}


MyArea::~MyArea()
{
}


bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Glib::RefPtr<Gdk::Pixbuf>   image2;

    if (!m_image)
        return false;

    Gtk::Allocation     allocation      = get_allocation();
    const int           width           = allocation.get_width();
    const int           height          = allocation.get_height();
    int                 dest_width;
    int                 dest_height;
    double              scale_width     = (double) width / (double) m_image->get_width();
    double              scale_height    = (double) height / (double) m_image->get_height();
    double              scale;

    if (scale_width > scale_height) {
        scale   = scale_height;
    } else {
        scale   = scale_width;
    }

    dest_width  = (int) (scale * (double) m_image->get_width());
    dest_height = (int) (scale * (double) m_image->get_height());

    image2      = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, true, 8, width, height);

    image2->fill(0x70707070);
    m_image->scale(image2, 0, 0, dest_width, dest_height,
                   0, 0, scale, scale, Gdk::INTERP_BILINEAR);
    
    Gdk::Cairo::set_source_pixbuf(cr, image2, 0, 0);
    cr->paint();

    return true;
}

