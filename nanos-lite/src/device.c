#include "common.h"
#include <amdev.h>

size_t serial_write(const void *buf, size_t offset, size_t len) {
  for (size_t i = 0; i < len; ++i)
    _putc(((char *)buf)[i]);
  return len;
}

#define NAME(key) \
  [_KEY_##key] = #key,

static const char *keyname[256] __attribute__((used)) = {
  [_KEY_NONE] = "NONE",
  _KEYS(NAME)
};

#define KEYDOWN_MASK 0x8000

size_t events_read(void *buf, size_t offset, size_t len) {
  int keycode = read_key();
  if ((keycode & ~KEYDOWN_MASK) == _KEY_NONE) {
    sprintf(buf, "t %d\n", uptime());
  } 
  else if (keycode & KEYDOWN_MASK) {
    sprintf(buf, "kd %s\n", keyname[keycode & ~KEYDOWN_MASK]);
  } 
  else {
    sprintf(buf, "ku %s\n", keyname[keycode & ~KEYDOWN_MASK]);
  }
  return strlen(buf);
}

static char dispinfo[128] __attribute__((used)) = {};

size_t get_dispinfo_size() {
  return strlen(dispinfo);
}

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  strncpy(buf, dispinfo + offset, len);
  return len;
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  int x, y;
  int w = screen_width();
  x = (offset / 4) % w;
  y = (offset / 4) / w;
  draw_rect((void *)buf, x, y, len / 4, 1);
  return len;
}

size_t fbsync_write(const void *buf, size_t offset, size_t len) {
  draw_sync();
  return len;
}

void init_device() {
  Log("Initializing devices...");
  _ioe_init();

  // TODO: print the string to array `dispinfo` with the format
  // described in the Navy-apps convention
  int screen_h = screen_height();
  int screen_w = screen_width();
  sprintf(dispinfo, "WIDTH:%d\nHEIGHT:%d\n", screen_w, screen_h);
}
