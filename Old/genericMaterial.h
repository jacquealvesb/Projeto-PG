#ifndef GENERICMATERIALH
#define GENERICMATERIALH 

struct hit_record;

#include "ray.h"
#include "hitable.h"

class Material{
    private:
        double emissiveFactor;
        double diffuseFactor;
        double specularFactor;
        double rugosityCoefficient;
        vec3 color; //using the vec3 as a 3-uple for RGB color

    public:
        Material(vec3 rgbColor, double ke, double kd, double ks, double alpha){
            this->emissiveFactor = ke;
            this->diffuseFactor = kd;
            this->specularFactor = ks;
            this->rugosityCoefficient = alpha;
            this->color = rgbColor;
        }

        vec3 color(){
            return this->color;
        }

        double ke(){
            return this->emissiveFactor;
        }

        double ks(){
            return this->specularFactor;
        }

        double kd(){
            return this->diffuseFactor;
        }

        double alpha(){
            return this->rugosityCoefficient;
        }
};

#endif