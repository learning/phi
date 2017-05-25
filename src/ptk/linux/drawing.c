#include <string.h>
#include "../drawing.h"

PtkCanvas *_canvas;
PangoLayout *textLayout;

void ptk_set_canvas(PtkCanvas *canvas) {
  _canvas = canvas;
}

void ptk_set_draw_color(int r, int g, int b, double alpha) {
  cairo_set_source_rgba(_canvas, r / 255.0, g / 255.0, b / 255.0, alpha);
}

void ptk_draw_line(int from_x, int from_y, int to_x, int to_y) {
  cairo_set_line_width(_canvas, 1);
  cairo_move_to(_canvas, from_x + 0.5, from_y + 0.5);
  cairo_line_to(_canvas, to_x + 0.5, to_y + 0.5);
  cairo_stroke(_canvas);
}

void ptk_draw_rectangle(int x, int y, int width, int height) {
  cairo_rectangle(_canvas, x, y, width, height);
  cairo_fill(_canvas);
}

void ptk_redraw(PtkWindow *window, int x, int y, int width, int height) {
  gtk_widget_queue_draw_area(window->drawing_area, x, y, width, height);
}

void ptk_draw_text(char text[], unsigned int length) {
  if (textLayout == NULL) {
    textLayout = pango_cairo_create_layout(_canvas);
    PangoFontDescription *desc = pango_font_description_from_string("Monospace 12");
    pango_layout_set_font_description(textLayout, desc);
    pango_font_description_free(desc);
    pango_cairo_show_layout(_canvas, textLayout);
    g_object_unref(textLayout);
  }
  pango_layout_set_text(textLayout, text, length);
  pango_cairo_update_layout(_canvas, textLayout);
  pango_cairo_show_layout(_canvas, textLayout);
}
