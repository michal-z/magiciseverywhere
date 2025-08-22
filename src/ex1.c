#include "precomp.h"

void ex1_run(void)
{
  exn_create_window(2048, 2048, "magiciseverywhere: ex1");
  do {
    glClearBufferfv(GL_COLOR, 0, (float[]){ 0.2f, 0.4f, 0.8f, 1.0 });
  } while (exn_update_window("magiciseverywhere: ex1"));
  exn_destroy_window();
}
