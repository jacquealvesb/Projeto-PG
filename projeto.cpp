#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "sphere.h"
#include "hitablelist.h"
#include "genericMaterial.h"
#include "float.h"
#include "camera.h"

#define PI 3.1415

vec3 color(const ray& r, hitable *world, int depth, vec3 light){
    hit_record rec;

  	if(world->hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 2 && rec.mat->scatter(r, rec, attenuation, scattered, light)) {
            //exit(1);
            return attenuation*color(scattered, world, depth+1, light);
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
    char command[100];

    FILE *file;

    file = fopen(path, "r");

    while(fscanf(file, " %s", command) != EOF) {
        if(strcmp(command, "res") == 0) {
            fscanf(file, "%d %d", width, height);

        } else if(strcmp(command, "camera") == 0) {
            int px, py, pz, tx, ty, tz, ux, uy, uz, fov, f;

            fscanf(file, " %d %d %d %d %d %d %d %d %d %d %d", &px, &py, &pz, &tx, &ty, &tz, &ux, &uy, &uz, &fov, &f);

            // px, py, pz = lookFrom - "where the camera is"
            // tx, ty, tz = lookAt - "where the camera is pointing to" or "target point/direction coordinates"
            // ux, uy, uz = rotation - the rotation happens around the lookFrom-lookAt axis. It's like looking to a fixed place but tilting your head around your nose.
            // fov = Field of View - (in degrees) how much can you see through the window

            vec3 lookFrom = vec3(float(px), float(py), float(pz));
            vec3 lookAt = vec3(float(tx), float(ty), float(tz));
            vec3 vup = vec3(float(ux), float(uy), float(uz));

            vec3 w = unit_vector(lookFrom - lookAt);
            vec3 u = unit_vector(cross(vup, w));
            vec3 v = cross(w, u);


            double fov_in_rad = PI * (fov/2.0)/180.0;
            double screen_ratio = (double)(*(height)) / *(width);

            double half_wid = abs(tan(fov_in_rad));
            double half_hei = abs(screen_ratio * half_wid);

            cam->origin = lookFrom;
            cam->lower_left_corner = vec3((-1)*half_wid, (-1)*half_hei, -1.0);
            cam->lower_left_corner = cam->origin - half_wid*u - half_hei*v - w;
            cam->horizontal = 2*half_wid*u;
            cam->vertical = 2*half_hei*v;

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

    hitable *list[5];

    list[0] = new sphere(vec3(0, -100.5, -1 ), 100, new Material(vec3(0.9, 0.9, 0.9), 0.5, 1.0, 1.0, 0.2) );
    list[1] = new sphere(vec3(0, 0, -1)      , 0.5, new Material(vec3(0.8, 0.3, 0.3), 0.5, 0.0, 1.0, 0.1) );
    list[2] = new sphere(vec3(2, 0, -1)      , 0.5, new Material(vec3(1.0, 0.0, 0.0), 0.5, 0.5, 0.0, 0.3) );
    list[3] = new sphere(vec3(-2, 0, -1)     , 0.5, new Material(vec3(0.8, 0.8, 0.8), 0.5, 0.0, 0.5, 0.0) );
    list[4] = new sphere(vec3(0, 0,  -3)     , 0.5, new Material(vec3(0.8, 0.8, 0.8), 0.5, 0.0, 0.5, 1.0) );
    
    hitable *world = new hitable_list(list, 5);

    camera cam;

    char filePath[100] = "scene.txt";

    setup(filePath, &nx, &ny, &cam);
    
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 light = vec3(0, 50, -5);

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for(int s = 0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);

                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 0, light);
            }

            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            if(ir < 0 ) ir = 255.0;
            if(ig < 0 ) ig = 255.0;
            if(ib < 0 ) ib = 255.0;

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}