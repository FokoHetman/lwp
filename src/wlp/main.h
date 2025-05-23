#ifndef MAIN_H
#define MAIN_H

#include "../platform_guard.h"

#ifdef _MSC_VER
#define PATH_MAX MAX_PATH
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <signal.h>

#ifdef __WIN32
#include <stdio.h>
#include <windows.h>
#elif __LINUX
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <linux/limits.h>
#include <pwd.h>
#include <unistd.h>
#endif

#include "../common.h"

typedef struct
{
  float x;
  float y;
} Point;

typedef struct
{
  SDL_Texture* tex;
} Layer;

typedef struct
{
  WallpaperInfo info;
  int           originalW;
  int           originalH;
  SDL_Texture*  tex;
  Layer*        layers;
} Wallpaper;

typedef struct
{
  MonitorInfo   info;
  SDL_Texture*  tex;
  Wallpaper     wlp;
  SDL_Window*   window;
  SDL_Renderer* renderer;
  Point         currentPoint;
  int           aborted;
} Monitor;

typedef struct
{
  AppConfig config;
  int       monitorsCount;
  Monitor*  monitors;

#ifdef __LINUX
  Display* display;
#endif

} App;

void initWindow(App* app, Monitor* monitor);
void runWallpaperLoop(App* app);

void getTargetPoint(App* app, Point* p);

#endif  // MAIN_H
