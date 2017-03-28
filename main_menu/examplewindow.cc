/* gtkmm example Copyright (C) 2002 gtkmm development team
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "examplewindow.h"
#include <iostream>

ExampleWindow::ExampleWindow()
    : Gtk::ApplicationWindow(),
      m_Box(Gtk::ORIENTATION_VERTICAL)
{
    set_title("Main menu example");
    set_default_size(300, 100);

    // ExampleApplication displays the menubar. Other stuff, such as a toolbar,
    // is put into the box.
    add(m_Box);

    // Create actions for menus and toolbars.
    // We can use add_action() because Gtk::ApplicationWindow derives from Gio::ActionMap.
    // This Action Map uses a "win." prefix for the actions.
    // Therefore, for instance, "win.copy", is used in ExampleApplication::on_startup()
    // to layout the menu.

    //Edit menu:
    add_action("copy", sigc::mem_fun(*this, &ExampleWindow::on_menu_others));
    add_action("paste", sigc::mem_fun(*this, &ExampleWindow::on_menu_others));
    add_action("something", sigc::mem_fun(*this, &ExampleWindow::on_menu_others));

    //Help menu:
    add_action("about", sigc::mem_fun(*this, &ExampleWindow::on_menu_others));

    //Create the toolbar and add it to a container widget:

    m_refBuilder = Gtk::Builder::create();

    Glib::ustring ui_info =
        "<!-- Generated with glade 3.18.3 -->"
        "<interface>"
        "  <requires lib='gtk+' version='3.4'/>"
        "  <object class='GtkToolbar' id='toolbar'>"
        "    <property name='visible'>True</property>"
        "    <property name='can_focus'>False</property>"
        "    <child>"
        "      <object class='GtkToolButton' id='toolbutton_new'>"
        "        <property name='visible'>True</property>"
        "        <property name='can_focus'>False</property>"
        "        <property name='tooltip_text' translatable='yes'>New Standard</property>"
        "        <property name='action_name'>app.newstandard</property>"
        "        <property name='icon_name'>document-new</property>"
        "      </object>"
        "      <packing>"
        "        <property name='expand'>False</property>"
        "        <property name='homogeneous'>True</property>"
        "      </packing>"
        "    </child>"
        "    <child>"
        "      <object class='GtkToolButton' id='toolbutton_quit'>"
        "        <property name='visible'>True</property>"
        "        <property name='can_focus'>False</property>"
        "        <property name='tooltip_text' translatable='yes'>Quit</property>"
        "        <property name='action_name'>app.quit</property>"
        "        <property name='icon_name'>application-exit</property>"
        "      </object>"
        "      <packing>"
        "        <property name='expand'>False</property>"
        "        <property name='homogeneous'>True</property>"
        "      </packing>"
        "    </child>"
        "  </object>"
        "</interface>";

    try
    {
        m_refBuilder->add_from_string(ui_info);
    }
    catch (const Glib::Error& ex)
    {
        std::cerr << "Building toolbar failed: " <<  ex.what();
    }

    Gtk::Toolbar* toolbar = nullptr;
    m_refBuilder->get_widget("toolbar", toolbar);
    if (!toolbar)
        g_warning("GtkToolbar not found");
    else
        m_Box.pack_start(*toolbar, Gtk::PACK_SHRINK);
}


ExampleWindow::~ExampleWindow()
{
}


void ExampleWindow::on_menu_others()
{
    std::cout << "A menu item was selected." << std::endl;
}

