#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

float rand_float(void)
{
  return (float)rand()/(float)RAND_MAX;
}

int main(void) 
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SmoothLife");
  SetTargetFPS(60);

  Image image = GenImagePerlinNoise(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 5.0f);
  //Image image = GenImageWhiteNoise(SCREEN_WIDTH, SCREEN_HEIGHT,0.9f);
  //Image image = GenImageCellular(SCREEN_WIDTH, SCREEN_HEIGHT, 10);
 // Image image = GenImageColor(SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
 // for (int y = 0; y < SCREEN_HEIGHT/4; ++y) {
 //   for (int x = 0; x < SCREEN_WIDTH/4; ++x) {
 //     uint8_t v = rand_float()*255.0f;
 //     Color color = { v, v, v, 255 };
 //     ImageDrawPixel(&image, x, y, color);
 //   }
 // }

  RenderTexture2D state[2];

  state[0] = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
  SetTextureWrap(state[0].texture, TEXTURE_WRAP_REPEAT);
  UpdateTexture(state[0].texture, image.data);

  state[1] = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
  SetTextureWrap(state[1].texture, TEXTURE_WRAP_REPEAT);

  Shader shader = LoadShader(NULL, "./smoothlife.fs");
  Vector2 resolution = {SCREEN_WIDTH, SCREEN_HEIGHT};
  int resolution_loc = GetShaderLocation(shader, "resolution");
  SetShaderValue(shader, resolution_loc, &resolution, SHADER_UNIFORM_VEC2);

  size_t i = 0;
  while (!WindowShouldClose()) {
    BeginTextureMode(state[1 - i]);
    ClearBackground(BLACK);
    BeginShaderMode(shader);
    DrawTexture(state[i].texture, 0, 0, WHITE);
    EndShaderMode();
    EndTextureMode();

    i = 1 - i;
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(state[i].texture, 0, 0, WHITE);
    EndDrawing();

  }

  CloseWindow();
  return 0;
}
