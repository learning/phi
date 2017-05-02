#include "../drawing.h"

PtkCanvas *_canvas;
Color _draw_color(128, 0, 0, 0);

void ptk_set_canvas(PtkCanvas *canvas) {
  _canvas = canvas;
}

void ptk_move_to(int x, int y) {

}

void ptk_set_draw_color(int r, int g, int b, double alpha) {
  _draw_color.SetValue(Color::MakeARGB(alpha * 255, r, g, b));
}

void ptk_draw_rectangle(int x, int y, int width, int height) {
  Graphics graphics(_canvas);
  SolidBrush brush(_draw_color);
  graphics.FillRectangle(&brush, x, y, width, height);
}

void ptk_draw_line(int from_x, int from_y, int to_x, int to_y) {
  Graphics graphics(_canvas);
  Pen pen(_draw_color);
  graphics.DrawLine(&pen, from_x, from_y, to_x, to_y);
}
