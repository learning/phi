#include "../drawing.h"

PtkCanvas *_canvas;

void ptk_set_canvas(PtkCanvas *canvas) {
  _canvas = canvas;
}

void ptk_move_to(int x, int y) {
  CGContextMoveToPoint(_canvas, x, y);
}

void ptk_set_draw_color(int r, int g, int b, double alpha) {
  CGContextSetRGBFillColor(_canvas, r / 255.0, g / 255.0, b / 255.0, alpha);
  CGContextSetRGBStrokeColor(_canvas, r / 255.0, g / 255.0, b / 255.0, alpha);
}

void ptk_draw_line(int from_x, int from_y, int to_x, int to_y) {
  CGContextMoveToPoint(_canvas, from_x + 0.5, from_y + 0.5);
  CGContextAddLineToPoint(_canvas, to_x + 0.5, to_y + 0.5);
  CGContextStrokePath(_canvas);
}

void ptk_draw_rectangle(int x, int y, int width, int height) {
  CGContextFillRect(_canvas, CGRectMake(x, y, width, height));
}

void ptk_redraw(PtkWindow *window, int x, int y, int width, int height) {
  
}

void ptk_draw_text(char text[], unsigned int length) {
  CGAffineTransform transform = CGAffineTransformMake(1.0, 0.0, 0.0, -1.0, 0.0, 0.0);
  CGContextSetTextMatrix(_canvas, transform);
  CGContextSelectFont(_canvas, "Monaco", 12.0, kCGEncodingMacRoman);
  // CGContextSetCharacterSpacing(_canvas, 1.7);
  CGContextSetTextDrawingMode(_canvas, kCGTextFill);
  CGContextShowTextAtPoint(_canvas, 0, 10, text, length);
}
