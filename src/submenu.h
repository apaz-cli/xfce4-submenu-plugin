#include <gtk/gtk.h>
#include <libxfce4panel/libxfce4panel.h>
#include <libxfce4util/libxfce4util.h>

#include "debug.h"

/* EXTERN "C" */
G_BEGIN_DECLS

/**********************/
/* Struct Definitions */
/**********************/

struct SubmenuSettings {
};
typedef struct SubmenuSettings SubmenuSettings;

#define MENUBLOCK_ICON_READ_FORMAT "mb_%i_icon"
#define MENUBLOCK_FORMAT_READ_FORMAT "mb_%i_format"

struct MenuBlock {
    void* icon;           // First a char* path, then is loaded and cast as gtk object.
    gchar* format_text;   // Loaded in "printf" format from settings
    gchar* current_text;  // The above, but filled.
};
typedef struct MenuBlock MenuBlock;

struct PositionalInformation {
    GtkOrientation orientation;
};
typedef struct PositionalInformation PositionalInformation;

struct SubmenuPlugin {
    XfcePanelPlugin* plugin;
    SubmenuSettings settings;
    PositionalInformation posinfo;
    MenuBlock blocks[30];
    size_t num_blocks;
};
typedef struct SubmenuPlugin SubmenuPlugin;

/***************************/
/* Constructor Definitions */
/***************************/

// Invoked once, at load time. Initializes the entire plugin.
static inline void create_plugin(SubmenuPlugin* self, XfcePanelPlugin* plugin);

// These will be called by create_plugin() at load time, in order.
static inline void read_settings(SubmenuPlugin* self);
static inline void create_posinfo(SubmenuPlugin* self);
static inline void create_block(SubmenuPlugin* self, XfceRc* rc, size_t blk_num);
static inline void load_image(GtkImage* icon_path);
static inline void create_graphics(SubmenuPlugin* self);

// An action listener will invoke this.
static inline void save_settings(SubmenuPlugin* self);

/*******************************/
/* Constructor Implementations */
/*******************************/

static inline void
create_plugin(SubmenuPlugin* self, XfcePanelPlugin* plugin) {
    self = g_slice_new0(SubmenuPlugin);
    self->plugin = plugin;
    self->num_blocks = 0;

    read_settings(self);
    create_posinfo(self);
    create_graphics(self);
}

static inline void read_settings(SubmenuPlugin* self) {
    gchar* fname = xfce_panel_plugin_save_location(self->plugin, TRUE);
    if (G_UNLIKELY(fname == NULL)) {
        debug_printf("UHHHHHHHH... Couldn't read get settings file name.\n");
        return;
    }

    XfceRc* rc = xfce_rc_simple_open(fname, TRUE);
    if (G_UNLIKELY(rc == NULL)) {
        debug_printf("UHHHHHHHH... Couldn't open the xfce_rc. No blocks parsed.\n");
        return;
    }

    // Read the blocks sequentially until there are no more.
    int cont = 0;
    while (cont != -1) {
        cont = create_block(self, rc, cont);
    }

    xfce_rc_close(rc);
}

static inline int create_block(SubmenuPlugin* self, XfceRc* rc, size_t blk_num) {
    if (G_UNLIKELY(blk_num == 30)) {
        debug_printf("Cannot load more than 30 blocks. Subsequent blocks are being ignored.\n");
        return -1;
    }
    MenuBlock* current_block = (self->blocks) + blk_num;


    /* Read from rc */
    current_block->format_text = xfce_rc_read_entry(rc, "", NULL);
    current_block->icon = xfce_rc_read_entry(rc, "", NULL);

    /* If not found, we've reached the end of the blocks. */
    if ((current_block->format_text) == NULL && current_block->icon == NULL) {
        return -1;
    }

    debug_printf("Parsed block. Format: %s, Icon path: %s\n", current_block->format_text, (char*)current_block->icon);

    self->num_blocks++;
    return blk_num + 1;
}

static inline void create_posinfo(SubmenuPlugin* self) {
    self->posinfo.orientation = gtk_orientable_get_orientation(self->plugin);
}

static inline void create_graphics(SubmenuPlugin* self) {}

static inline void save_settings(SubmenuPlugin* self);
G_END_DECLS
