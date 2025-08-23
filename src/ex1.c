#include "precomp.h"

void ex1_run(void)
{
  exn_create_window(1024, 1024, "magiciseverywhere: ex1", 0);
  do {
    glClearBufferfv(GL_COLOR, 0, (float[]){ 0.2f, 0.4f, 0.8f, 1.0 });
  } while (exn_update_window("magiciseverywhere: ex1"));
  exn_destroy_window();
}
