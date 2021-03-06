#ifndef __PTK_DRAWING__
#define __PTK_DRAWING__

#include "target/types.h"

/* Drawing */
void ptk_set_canvas(PtkCanvas *canvas);
void ptk_set_draw_color(int r, int g, int b, double alpha);
void ptk_draw_line(int from_x, int from_y, int to_x, int to_y);
void ptk_draw_rectangle(int x, int y, int width, int height);
void ptk_redraw(PtkWindow *window, int x, int y, int width, int height);

/* Text */
void ptk_draw_text(char text[], unsigned int length);
#endif

