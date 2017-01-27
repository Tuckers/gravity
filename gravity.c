#include <simple2d.h>

int height = 960;
int width = 540;

void on_key(S2D_Event e, const char *key) {
  switch (e) {
    case S2D_KEYDOWN:
        printf("Key %s pressed\n", key);
      break;

    case S2D_KEY:
      printf("Key %s held down\n", key);
      break;

    case S2D_KEYUP:
      printf("Key %s released\n", key);
      break;
  }
}

void render() {
  S2D_DrawTriangle(
    320,  50, 1, 0, 0, 1,
    540, 430, 0, 1, 0, 1,
    100, 430, 0, 0, 1, 1
  );
}

int main() {

  S2D_Diagnostics(true);
  S2D_Window *window = S2D_CreateWindow(
    "Gravity", width, height, NULL, render, 0
  );

  // Cap the frame rate, 60 frames per second by default
  window->fps_cap = 60;

  // Set the window background color, black by default
  window->background.r = 1.0;
  window->background.g = 0.5;
  window->background.b = 0.8;
  window->on_key = on_key;

  S2D_Show(window);
  S2D_FreeWindow(window);
  return 0;
}
