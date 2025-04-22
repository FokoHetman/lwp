#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common.h"

void createUserDirs()
{
#ifdef __WIN32
  const char *format = "%s\\%s";
#else
  const char *format = "%s/%s";
#endif

  char path[PATH_MAX];
  char path2[PATH_MAX];

  getAppDir(path2, APP_DIR_USER_SETTINGS);
  sprintf(path, format, path2, "wallpapers");
  g_mkdir_with_parents(path, 484);

  getAppDir(path2, APP_DIR_USER_SETTINGS);
  sprintf(path, format, path2, "monitors");
  g_mkdir_with_parents(path, 484);
}

static void removeLastPathEntry(char *path)
{
  char *ptr = path + strlen(path) - 1;
  while (*ptr != '\\') ptr--;
  *ptr = '\0';
}

void getAppDir(char *buff, int type)
{
#ifdef __LINUX

  char prefix[PATH_MAX];

  char *prefixEnv = getenv("LWP_PREFIX");
  strcpy(prefix, prefixEnv ? prefixEnv : DEFAULT_LINUX_PREFIX);

#endif

  if (type == APP_DIR_USER_SETTINGS)
  {
#ifdef __LINUX
    sprintf(buff, "%s/.config/lwp", g_get_home_dir());
#elif __WIN32
    sprintf(buff, "%s\\lwp", g_get_user_data_dir());
#endif
  }

#ifdef __LINUX
  if (type == APP_DIR_BIN)
  {
    sprintf(buff, "%s/%s", prefix, "bin");
  }
  else if (type == APP_DIR_SHARE)
  {
    sprintf(buff, "%s/%s", prefix, "share/lwp");
  }
#elif __WIN32
  if (type == APP_DIR_BIN || type == APP_DIR_SHARE)
  {
    GetModuleFileNameA(NULL, buff, PATH_MAX);
    removeLastPathEntry(buff);
  }
#endif
}

void getMonitorCfgPath(char *buff, const char *name)
{
  char buff2[PATH_MAX];
  getAppDir(buff2, APP_DIR_USER_SETTINGS);

#ifdef __WIN32
  const char *format = "%s\\monitors\\%s.cfg";
#else
  const char *format = "%s/monitors/%s.cfg";
#endif

  
  sprintf(buff, format, buff2, name);
}

void getWlpCfgPath(char *buff, const char *dirPath)
{
#ifdef __WIN32
  const char *format = "%s\\wallpaper.cfg";
#else
  const char *format = "%s/wallpaper.cfg";
#endif

  sprintf(buff, format, dirPath);
}

void getAppCfgPath(char *buff)
{
  char buff2[PATH_MAX];
  getAppDir(buff2, APP_DIR_USER_SETTINGS);

#ifdef __WIN32
  const char *format = "%s\\lwp.cfg";
#else
  const char *format = "%s/lwp.cfg";
#endif

  sprintf(buff, format, buff2);
}

void getLogPath(char *buff)
{
  char buff2[PATH_MAX];
  getAppDir(buff2, APP_DIR_USER_SETTINGS);

#ifdef __WIN32
  const char *format = "%s\\log.txt";
#else
  const char *format = "%s/log";
#endif

  sprintf(buff, format, buff2);
}
