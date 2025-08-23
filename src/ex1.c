#include "precomp.h"

#define VIEWPORT_W 1024
#define VIEWPORT_H 1024
#define NAME "magiciseverywhere: ex1"

void ex1_run(void)
{
  exn_create_window(VIEWPORT_W, VIEWPORT_H, NAME, 0);
  do {
    glClearBufferfv(GL_COLOR, 0, (float[]){ 0.2f, 0.4f, 0.8f, 1.0 });
  } while (exn_update_window(NAME));
  exn_destroy_window();
}
