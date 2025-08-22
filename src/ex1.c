#include "precomp.h"
#include "common.h"

static void init(void)
{
}

static void update(void)
{
  glClearBufferfv(GL_COLOR, 0, (float[]){ 0.2f, 0.4f, 0.8f, 1.0 });
}

ExperimentEntry ex1_entry(void)
{
  return (ExperimentEntry){
    .init = init,
    .update = update,
  };
}
