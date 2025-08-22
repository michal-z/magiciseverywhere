#include "precomp.h"

#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"

#pragma warning(push)
#pragma warning(disable : 4005)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma warning(pop)

__declspec(dllexport) DWORD NvOptimusEnablement = 1;

PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

PFNGLCLEARBUFFERFVPROC glClearBufferfv;
PFNGLMATRIXLOADIDENTITYEXTPROC glMatrixLoadIdentityEXT;
PFNGLMATRIXORTHOEXTPROC glMatrixOrthoEXT;
PFNGLCREATETEXTURESPROC glCreateTextures;
PFNGLGETSTRINGIPROC glGetStringi;
PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC glTextureStorage2DMultisample;
PFNGLCREATEFRAMEBUFFERSPROC glCreateFramebuffers;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
PFNGLNAMEDFRAMEBUFFERTEXTUREPROC glNamedFramebufferTexture;
PFNGLCLEARNAMEDFRAMEBUFFERFVPROC glClearNamedFramebufferfv;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
PFNGLBLITNAMEDFRAMEBUFFERPROC glBlitNamedFramebuffer;
PFNGLBLENDEQUATIONPROC glBlendEquation;
PFNGLCLEARTEXIMAGEPROC glClearTexImage;
PFNGLGETTEXTUREHANDLENVPROC glGetTextureHandleNV;
PFNGLMAKETEXTUREHANDLERESIDENTNVPROC glMakeTextureHandleResidentNV;
PFNGLCREATESHADERPROGRAMVPROC glCreateShaderProgramv;
PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC glProgramUniformHandleui64NV;
PFNGLUSEPROGRAMPROC glUseProgram;

static LRESULT CALLBACK process_window_message(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
  switch (message) {
    case WM_DESTROY: {
      PostQuitMessage(0);
      return 0;
    } break;
    case WM_KEYDOWN: {
      if (wparam == VK_ESCAPE) {
        PostQuitMessage(0);
        return 0;
      }
    } break;
  }
  return DefWindowProc(hwnd, message, wparam, lparam);
}

static double get_time(void)
{
  static LARGE_INTEGER start_counter;
  static LARGE_INTEGER frequency;
  if (start_counter.QuadPart == 0) {
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start_counter);
  }
  LARGE_INTEGER counter;
  QueryPerformanceCounter(&counter);
  return (double)(counter.QuadPart - start_counter.QuadPart) / (double)frequency.QuadPart;
}

static float update_frame_stats(HWND window, const char *name)
{
  static double previous_time = -1.0;
  static double header_refresh_time = 0.0;
  static uint32_t num_frames = 0;

  if (previous_time < 0.0) {
    previous_time = get_time();
    header_refresh_time = previous_time;
  }

  const double time = get_time();
  const float delta_time = (float)(time - previous_time);
  previous_time = time;

  if ((time - header_refresh_time) >= 1.0) {
    const double fps = num_frames / (time - header_refresh_time);
    const double ms = (1.0 / fps) * 1000.0;
    char header[128];
    snprintf(header, sizeof(header), "[%.1f fps  %.3f ms] %s", fps, ms, name);
    SetWindowText(window, header);
    header_refresh_time = time;
    num_frames = 0;
  }
  num_frames++;
  return delta_time;
}

static HWND hwnd;
static HDC hdc;
static HGLRC hglrc;

void exn_create_window(int w, int h, const char *name)
{
  SetProcessDPIAware();

  RegisterClass(&(WNDCLASSA){
    .lpfnWndProc = process_window_message,
    .hInstance = GetModuleHandle(NULL),
    .hCursor = LoadCursor(NULL, IDC_ARROW),
    .lpszClassName = name,
  });

  const DWORD style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;

  RECT rect = { .left = 0, .top = 0, .right = w, .bottom = h };
  AdjustWindowRect(&rect, style, FALSE);

  hwnd = CreateWindowEx(0, name, name, style + WS_VISIBLE, 0, 0, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, NULL, NULL);

  hdc = GetDC(hwnd);

  PIXELFORMATDESCRIPTOR pfd = {
    .nSize = sizeof(PIXELFORMATDESCRIPTOR),
    .nVersion = 1,
    .dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW,
    .iPixelType = PFD_TYPE_RGBA,
    .cColorBits = 24,
  };
  SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);

  hglrc = wglCreateContext(hdc);
  wglMakeCurrent(hdc, hglrc);

#define GET_FUNC(type, name) \
    name = (type)wglGetProcAddress(#name); \
    assert(name)

    GET_FUNC(PFNWGLSWAPINTERVALEXTPROC, wglSwapIntervalEXT);

    GET_FUNC(PFNGLCLEARBUFFERFVPROC, glClearBufferfv);
    GET_FUNC(PFNGLMATRIXLOADIDENTITYEXTPROC, glMatrixLoadIdentityEXT);
    GET_FUNC(PFNGLMATRIXORTHOEXTPROC, glMatrixOrthoEXT);
    GET_FUNC(PFNGLCREATETEXTURESPROC, glCreateTextures);
    GET_FUNC(PFNGLGETSTRINGIPROC, glGetStringi);
    GET_FUNC(PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC, glTextureStorage2DMultisample);
    GET_FUNC(PFNGLCREATEFRAMEBUFFERSPROC, glCreateFramebuffers);
    GET_FUNC(PFNGLDELETEFRAMEBUFFERSPROC, glDeleteFramebuffers);
    GET_FUNC(PFNGLNAMEDFRAMEBUFFERTEXTUREPROC, glNamedFramebufferTexture);
    GET_FUNC(PFNGLCLEARNAMEDFRAMEBUFFERFVPROC, glClearNamedFramebufferfv);
    GET_FUNC(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer);
    GET_FUNC(PFNGLBLITNAMEDFRAMEBUFFERPROC, glBlitNamedFramebuffer);
    GET_FUNC(PFNGLBLENDEQUATIONPROC, glBlendEquation);
    GET_FUNC(PFNGLCLEARTEXIMAGEPROC, glClearTexImage);
    GET_FUNC(PFNGLGETTEXTUREHANDLENVPROC, glGetTextureHandleNV);
    GET_FUNC(PFNGLMAKETEXTUREHANDLERESIDENTNVPROC, glMakeTextureHandleResidentNV);
    GET_FUNC(PFNGLCREATESHADERPROGRAMVPROC, glCreateShaderProgramv);
    GET_FUNC(PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC, glProgramUniformHandleui64NV);
    GET_FUNC(PFNGLUSEPROGRAMPROC, glUseProgram);

#undef GET_FUNC

  printf("GL version: %s\n", (const char *)glGetString(GL_VERSION));
  printf("GL renderer: %s\n", (const char *)glGetString(GL_RENDERER));
  printf("GL vendor: %s\n", (const char *)glGetString(GL_VENDOR));

  {
    bool has_path_rendering = false;
    bool has_mesh_shader = false;

    int32_t num_extensions = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);

    for (int32_t i = 0; i < num_extensions; ++i) {
      const char *ext = (const char *)glGetStringi(GL_EXTENSIONS, i);
      if (strcmp(ext, "GL_NV_path_rendering") == 0) has_path_rendering = true;
      if (strcmp(ext, "GL_NV_mesh_shader") == 0) has_mesh_shader = true;
      if (has_path_rendering && has_mesh_shader) break;
    }

    if (has_path_rendering == false || has_mesh_shader == false) {
      MessageBox(hwnd, "Sorry but this application requires modern NVIDIA GPU with latest graphics drivers.", "Unsupported GPU", MB_OK | MB_ICONSTOP);
      ExitProcess(0);
    }
  }
  wglSwapIntervalEXT(0);
}

void exn_destroy_window(void)
{
  wglMakeCurrent(hdc, NULL);
  wglDeleteContext(hglrc);
  ReleaseDC(hwnd, hdc);
}

bool exn_update_window(const char *name)
{
  SwapBuffers(hdc);

  if (glGetError() != GL_NO_ERROR) {
    MessageBox(hwnd, "OpenGL error detected.", "Error", MB_OK | MB_ICONERROR);
    return false;
  }

  bool running = true;
  MSG msg = {0};
  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    if (msg.message == WM_QUIT) running = false;
  }
  update_frame_stats(hwnd, name);
  return running;
}
