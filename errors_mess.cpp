#include "header1.h"

void RtnErrorBMP_menu()
{
    set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
    allegro_message("ERROR: Program can't load file to memory.");
    allegro_exit();
    return;
}END_OF_FUNCTION();
