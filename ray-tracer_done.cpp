#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cmath>
// #include <iostream>

using namespace std;

struct Vector3
{
  float x, y, z;
  Vector3 operator+(Vector3 b)
  {
    return {x + b.x, y + b.y, z + b.z};
  }
  Vector3 sub(Vector3 b)
  {
    return {x - b.x, y - b.y, z - b.z};
  }
  Vector3 scale(float s)
  {
    return {x * s, y * s, z * s};
  }
  float dot(Vector3 b)
  {
    return x * b.x + y * b.y + z * b.z;
  }
  Vector3 cross(Vector3 b)
  {
    return {y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - b.x * y};
  }
  float length()
  {
    return sqrt(x * x + y * y + z * z);
  }
  Vector3 normalize()
  {
    return {x / length(), y / length(), z / length()};
  }
  bool inTriangle(Vector3 p0, Vector3 p1, Vector3 p2)
  {
    return p0.sub(*this).cross(p0.sub(p1)).z >= 0 &&
           p1.sub(*this).cross(p1.sub(p2)).z >= 0 &&
           p2.sub(*this).cross(p2.sub(p0)).z >= 0;
  }
  float* getBarycentric(Vector3 p0, Vector3 p1, Vector3 p2){
    Vector3 p0p1 = p1.sub(p0);
    Vector3 p0p2 = p2.sub(p0);
    Vector3 subp0 = sub(p0);
    Vector3 subp1 = sub(p1);
    Vector3 subp2 = sub(p2);

    float area = p0p1.cross(p0p2).length()/2;
    float areap0p1 = subp0.cross(subp1).length()/2;
    float areap1p2 = subp1.cross(subp2).length()/2;
    float areap2p0 = subp2.cross(subp0).length()/2;

    float i = areap0p1 / area;
    float j = areap1p2 / area;
    float k = areap2p0 / area;


    return new float[]{i, j, k};
  }
};

int main()
{

  const int w=640;
  const int h = 640;

  Vector3 p0 = {-1, -1, -1};
  Vector3 p1 = {-1, 1, -1};
  Vector3 p2 = {1, 1, -1};


  unsigned char pixels[w * h * 3];

  for (float y = 0; y < h; y++)
  {
    for (float x = 0; x < w; x++)
    {
      float tempX = x/w * 2 -1;
      float tempY = -1 * (y/h*2-1);
      Vector3 target = {tempX, tempY, -1};
      Vector3 camera_origin = {0,0,0};
      Vector3 ray_direction = target.sub(camera_origin).normalize();

      Vector3 plane_normal = {0,0,1};
      float plane_distance_from_origin = -plane_normal.dot(p0);
      float distance_to_plane_collision = (-plane_distance_from_origin-plane_normal.dot(camera_origin))/plane_normal.dot(ray_direction);
      Vector3 plane_collision = camera_origin + (ray_direction.scale(distance_to_plane_collision));

      int idx = (y * w + x) * 3;
      float* ijk = plane_collision.getBarycentric(p0, p1, p2);
      bool white = abs(1-(ijk[0] + ijk[1] + ijk[2])) < .001;
      // bool white = plane_collision.inTriangle(p0, p1, p2);
      unsigned char color = white ? 255 : 0;
      pixels[idx] = color;
      pixels[idx + 1] = color;
      pixels[idx + 2] = color;
    }
  }

  stbi_write_png("image.png", w, h, 3, pixels, w * 3);
  return 0;
}
