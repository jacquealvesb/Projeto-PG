#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "sphere.h"
#include "hitablelist.h"
#include "material.h"
#include "float.h"
#include "camera.h"

#define PI 3.1415

vec3 color(const ray& r, hitable *world, int depth){
    hit_record rec;

  	if(world->hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat->scatter(r, rec, attenuation, scattered)) {
            return attenuation*color(scattered, world, depth+1);
        }
        else {
            return vec3(0,0,0);
        }
    } 
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

void setup(char path[100], int *width, int *height, camera *cam) {
    char line[5000];
    char command[100];

    FILE *file;

    file = fopen(path, "r");

    while(fscanf(file, " %s", command) != EOF) {
        if(strcmp(command, "res") == 0) {
            fscanf(file, "%d %d", width, height);

        } else if(strcmp(command, "camera") == 0) {
            int px, py, pz, tx, ty, tz, ux, uy, uz, fov, f;

            fscanf(file, " %d %d %d %d %d %d %d %d %d %d %d", &px, &py, &pz, &tx, &ty, &tz, &ux, &uy, &uz, &fov, &f);

            double fov_in_rad = PI * (fov/2.0)/180.0;
            double screen_ratio = (double)(*(height)) / *(width);

            double half_fovW = abs(tan(fov_in_rad));
            double half_fovH = abs(screen_ratio * half_fovW);

            cam->origin = vec3(px, py, pz);
            cam->lower_left_corner = vec3((-1)*half_fovW, (-1)*half_fovH, 0.0);
            cam->horizontal = vec3( half_fovW*2, 0.0, 0.0);
            cam->vertical = vec3(0.0, half_fovH*2, 0.0);

            // std::cout << cam->horizontal.x() << " " << cam->vertical.y();

        } else if(strcmp(command, "material") == 0) {
            char name[20];
            int r, g, b, kd, ks, ke, alpha;

            fscanf(file, " %s %d %d %d %d %d %d %d", name, &r, &g, &b, &kd, &ks, &ke, &alpha);

        } else if(strcmp(command, "sphere")) {
            //puts("to do");
        }
    }
}

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 100;

    hitable *list[4];

    list[0] = new sphere(vec3(0, 0, -1)      , 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(vec3(0, -100.5, -1 ), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1, 0, -1)      , 0.5, new metal(vec3(1.0, 0.0, 0.0), 0.1));
    list[3] = new sphere(vec3(-1, 0, -1)     , 0.5, new metal(vec3(0.8, 0.8, 0.8), 0.7));
    
    hitable *world = new hitable_list(list, 4);

    camera cam;

    char filePath[100] = "scene.txt";

    setup(filePath, &nx, &ny, &cam);
    
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for(int s = 0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);

                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 0);
            }

            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}