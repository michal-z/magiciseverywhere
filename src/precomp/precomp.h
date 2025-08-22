#pragma once

#define APIENTRY __stdcall
#define WINGDIAPI __declspec(dllimport)
#include "GL/gl.h"
#include "GL/glext.h"

typedef int (APIENTRYP PFNWGLSWAPINTERVALEXTPROC) (int interval);

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "stb_perlin.h"
#include "fmod.h"

void exn_create_window(int w, int h, const char *name);
void exn_destroy_window(void);
bool exn_update_window(const char *name);

#define NL "\n"

extern PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

extern PFNGLCLEARBUFFERFVPROC glClearBufferfv;
extern PFNGLMATRIXLOADIDENTITYEXTPROC glMatrixLoadIdentityEXT;
extern PFNGLMATRIXORTHOEXTPROC glMatrixOrthoEXT;
extern PFNGLCREATETEXTURESPROC glCreateTextures;
extern PFNGLGETSTRINGIPROC glGetStringi;
extern PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC glTextureStorage2DMultisample;
extern PFNGLCREATEFRAMEBUFFERSPROC glCreateFramebuffers;
extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
extern PFNGLNAMEDFRAMEBUFFERTEXTUREPROC glNamedFramebufferTexture;
extern PFNGLCLEARNAMEDFRAMEBUFFERFVPROC glClearNamedFramebufferfv;
extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
extern PFNGLBLITNAMEDFRAMEBUFFERPROC glBlitNamedFramebuffer;
extern PFNGLBLENDEQUATIONPROC glBlendEquation;
extern PFNGLCLEARTEXIMAGEPROC glClearTexImage;
extern PFNGLGETTEXTUREHANDLENVPROC glGetTextureHandleNV;
extern PFNGLMAKETEXTUREHANDLERESIDENTNVPROC glMakeTextureHandleResidentNV;
extern PFNGLCREATESHADERPROGRAMVPROC glCreateShaderProgramv;
extern PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC glProgramUniformHandleui64NV;
extern PFNGLUSEPROGRAMPROC glUseProgram;
