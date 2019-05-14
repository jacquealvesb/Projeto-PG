#ifndef GENERICMATERIALH
#define GENERICMATERIALH 

struct hit_record;

#include "ray.h"
#include "hitable.h"

vec3 reflect(const vec3& v, const vec3& n) {
     return v - 2*dot(v,n)*n;
}

vec3 random_in_unit_sphere() {
    vec3 p;

    do {
        p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while(p.squared_length() >= 1.0);

    return p;
}

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

        vec3 objColor(){
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

        double power(double x, double y) {
            double temp;

            if(y == 0) {
                return 1;
            }

            temp = power(x, y/2);

            if(std::fmod(y, 2) == 0) {
                return temp*temp;
            } else {
                if(y > 0) {
                    return  x*temp*temp;
                } else {
                    return (temp*temp)/x;
                }
            }
        }

        vec3 phong(vec3 dir, vec3 normal, vec3 lightRay){
            vec3 unityRay = lightRay;
            unityRay.make_unit_vector();

            vec3 reflection = reflect(unityRay, normal);

            reflection.make_unit_vector();

            double diffuse, specular;

            diffuse = dot(lightRay, normal) * (this->kd());

            double res = pow(dot(reflection, dir), (this->alpha()));

            specular = (this->ks()) * res;

            // std::cout << reflection;
            // exit(1);

            // std::cout << reflection << "\n" << dir << "\n";

            // std::cout << dot(reflection, dir) << " elevado a " << this->alpha() << " é " << res << "\n";


            if(dot(normal, lightRay) < 0 || specular < 0){
                specular = 0;
            }

            if(diffuse < 0){
                diffuse = 0;
            }

            // light is always white
            vec3 color = vec3(1.0,1.0,1.0)*(this->color);

            // std::cout << specular << ", " << diffuse << "\n";

            return color * (specular + diffuse);

        }

        virtual vec3 scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, vec3 light){
            // scattered = ray(rec.p, (this->ks())*reflected + (this->kd())*random_in_unit_sphere());

            // attenuation = (this->color);
            // return (dot(scattered.direction(), rec.normal) > 0);

            vec3 normal = rec.normal;

            vec3 direction = r_in.direction();

            // calcula componente emissiva
            vec3 color = (vec3(1.0,1.0,1.0) * (this->objColor())) * (this->ke());

            vec3 lightRayDir = (vec3)(light - rec.p);
            lightRayDir.make_unit_vector();


            ray lightRay = ray(light, lightRayDir*(-1));

            if(dot(normal, r_in.direction()*(-1)) < 0){
                normal = normal*(-1);
            }

            attenuation = color + this->phong(direction, normal, lightRayDir);

            return attenuation;
            // return (dot(attenuation, rec.normal) > 0);
            // return true
        }

};

#endif