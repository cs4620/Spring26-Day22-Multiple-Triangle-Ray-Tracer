#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "vector3.hpp"
#include "triangle.hpp"
#include <cmath>
#include <vector>
// #include <iostream>

using namespace std;

vector<float> green_shader()
{
  return {0.0f, 1.0f, 0.0f};
}

vector<float> orange_shader()
{
  return {.8f, .8f, 0.0f};
}

int main()
{

  Vector3 camera_origin = {0, 0, 0};

  Vector3 p0 = {-1, 1, -1};
  Vector3 p1 = {-1, -1, -1};
  Vector3 p2 = {1, 1, -1};

  Triangle triangle1 = {p0, p1, p2, green_shader};
  Triangle triangle2 = {{1, 1, -2}, {-1, 1, -2}, {1, -1, -2}, orange_shader};

  vector<Triangle> triangles;
  triangles.push_back(triangle1);
  triangles.push_back(triangle2);

  vector<float> background_color = {0.0f, 0.0f, 1.0f};

  const int w = 640;
  const int h = 640;

  unsigned char pixels[w * h * 3];

  for (float y = 0; y < h; y++)
  {
    for (float x = 0; x < w; x++)
    {
      float closest_hit = INFINITY;
      vector<float> closest_pixel;
      for (const auto &triangle : triangles)
      {
        // if(x==100&&y==100){
        //   int a = 0;
        // }
        float _x = x / w * 2 - 1;
        float _y = -(y / h * 2 - 1);

        Vector3 target = {_x, _y, -1};
        Vector3 ray_direction = (Vector3{_x, _y, -1}.sub(camera_origin)).normalized();

        Vector3 p0 = triangle.p0;
        Vector3 p1 = triangle.p1;
        Vector3 p2 = triangle.p2;

        Vector3 leg1 = p1.sub(p0);
        Vector3 leg2 = p2.sub(p1);
        Vector3 normal = leg1.cross(leg2);
        float d = -normal.dot(p0);

        // Where do we hit the plane?
        float t = (-d - camera_origin.dot(normal)) / (normal.dot(ray_direction));

        if (t < closest_hit)
        {
          // closest_hit = t;
        }
        else
        {
          continue;
        }

        Vector3 plane_collission = camera_origin.add(ray_direction.times(t));

        // Find out whether the point on the plane is in the triangle
        float area_triangle = leg1.cross(leg2).length() / 2;

        Vector3 p_p0 = plane_collission.sub(p0);
        Vector3 p_p1 = plane_collission.sub(p1);
        Vector3 p_p2 = plane_collission.sub(p2);

        float area_opposite_p0 = p_p1.cross(p_p2).length() / 2;
        float area_opposite_p1 = p_p0.cross(p_p2).length() / 2;
        float area_opposite_p2 = p_p0.cross(p_p1).length() / 2;

        float barycentric_p0 = area_opposite_p0 / area_triangle;
        float barycentric_p1 = area_opposite_p1 / area_triangle;
        float barycentric_p2 = area_opposite_p2 / area_triangle;

        float tolerance = .00001;

        bool in_triangle = abs(1 - (barycentric_p0 + barycentric_p1 + barycentric_p2)) < tolerance;

        if (!in_triangle)
          continue;
        closest_hit = t;
        closest_pixel = triangle.shader();
        // vector<float> final_color = in_triangle ? triangle.shader() : background_color;

        // Write either the triangle color or the background to the image buffer
      }
      int idx = (y * w + x) * 3;
      vector<float> final_color = closest_hit != INFINITY ? closest_pixel : background_color;

      pixels[idx] = (unsigned char)(255 * final_color[0]);
      pixels[idx + 1] = (unsigned char)(255 * final_color[1]);
      pixels[idx + 2] = (unsigned char)(255 * final_color[2]);
    }
  }

  stbi_write_png("image.png", w, h, 3, pixels, w * 3);
  return 0;
}
