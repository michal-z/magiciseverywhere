#pragma once

typedef struct
{
  void (*init)(void);
  void (*update)(void);
  void (*shutdown)(void);
} ExperimentEntry;

ExperimentEntry ex1_entry(void);

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
