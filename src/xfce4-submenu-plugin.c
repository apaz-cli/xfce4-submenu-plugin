#include "submenu.h"

/* xfce_textdomain() constants */
#include "config.h"

/* This is the entry point, equivalent to main(). The macro below expands to main(). */
static void enter_panel(XfcePanelPlugin* plugin) {
    xfce_textdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR, "UTF-8");
    
    SubmenuPlugin this;
    create_plugin(&this, plugin);
}
XFCE_PANEL_PLUGIN_REGISTER(enter_panel);
