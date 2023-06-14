#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

uniform vec2 resolution;

float ra = 21;
float alpha_n = 0.028;
float alpha_m = 0.147;
float b1 = 0.257;
float b2 = 0.336;
float d1 = 0.365;
float d2 = 0.549;
float dt = 1.0;

float sigma(float x, float a, float alpha)
{
  return 1.0/(1.0 + exp(-(x - a)*4.0/alpha));
}

float sigma_n(float x, float a, float b)
{
  return sigma(x, a, alpha_n)*(1.0 - sigma(x, b, alpha_n));
}

float sigma_m(float x, float y, float m) 
{
  return x*(1.0 - sigma(m, 0.5, alpha_m)) + y*sigma(m, 0.5, alpha_m);
}

float s(float n, float m)
{
  return sigma_n(n, sigma_m(b1, d1,m),sigma_m(b2,d2,m));
}

float grid(float x, float y)
{
  float tx = x/resolution.x;
  float ty = y/resolution.y;
  vec4 t = texture(texture0, vec2(tx, ty));
  return max(max(t.x, t.y), t.z);
}

#define PI 3.14159265359

void main()
{
  float cx = fragTexCoord.x*resolution.x;
  float cy = (1 - fragTexCoord.y)*resolution.y;
  float ri = ra/3.0;
  float m = 0;
  float n = 0;
  float M = PI*ri*ri;
  float N = PI*ra*ra - M;

  for (float dy = -ra; dy <= ra; dy += 1.0) {
    for (float dx = -ra; dx <= ra; dx += 1.0) {
//      int x = emod(cx + dx, int(resolution.x));
//      int y = emod(cy + dy, int(resolution.y));
        float x = cx + dx;
        float y = cy + dy;
      if (dx*dx + dy*dy <= ri*ri) { 
        m += grid(x,y);
      } else if (dx*dx + dy*dy <= ra*ra) {
        n += grid(x,y);
      }
    }
  }
  m /= M;
  n /= N;
  float q = s(n,m);
  float diff = 2.0*q - 1.0;
  float v = clamp(grid(cx,cy) + dt*diff, 0.0, 1.0);
  finalColor = vec4(v, v, v, 1);
}
