// generated by Fast Light User Interface Designer (fluid) version 1.0300

#include "test.h"

Fl_Double_Window* FancyUI::make_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(529, 861);
    w = o;
    o->user_data((void*)(this));
    { ffffltk::Dial* o = new ffffltk::Dial(50, 20, 130, 270, "Fancyness");
      o->box(FL_NO_BOX);
      o->color(FL_BACKGROUND_COLOR);
      o->selection_color(FL_INACTIVE_COLOR);
      o->labeltype(FL_NORMAL_LABEL);
      o->labelfont(0);
      o->labelsize(14);
      o->labelcolor(FL_FOREGROUND_COLOR);
      o->align(Fl_Align(FL_ALIGN_BOTTOM));
      o->when(FL_WHEN_CHANGED);
      o->drawing_h = cairo_code_draw_vintagedial_get_height(); o->drawing_w = cairo_code_draw_vintagedial_get_width(); o->drawing_f = &cairo_code_draw_vintagedial_render;
    } // ffffltk::Dial* o
    o->show();
    o->end();
  } // Fl_Double_Window* o
  return w;
}