#ifndef MAT_H
#define MAT_H

//#include <GL/freeglut.h>
#include <map>
#include <string>
#include <glm/glm.hpp>
#include "Texture.hpp"


class Material {
private:
    //std::vector<Material*> material_list;
    static std::map<std::string, Material*> materials_by_name;
    static Material* applied;
protected:
    glm::vec4 mat_ambient;
    glm::vec4 mat_diffuse;
    glm::vec4 mat_specular;
    glm::vec4 mat_shininess;
    glm::vec4 mat_emmissive;
    float specular_exp;
    float transparency;
    glm::vec4 transmission;
    float opticalDensity;
    int illumination;

    Texture* t_ambient;
    Texture* t_diffuse;
    Texture* t_specular;
    Texture* t_specularHighlight;
    Texture* t_alpha;
    Texture* t_bump_mapping;
    Texture* t_displacement;
    Texture* t_stencil;

    Material(float mat_ambient[], float mat_diffuse[],
        float mat_specular[], float* mat_shininess) {
        /*this->mat_ambient = mat_ambient;
        this->mat_diffuse = mat_diffuse;
        this->mat_specular = mat_specular;
        this->mat_shininess = mat_shininess;*/
    }
    Material(){}
public:
    static void create(std::string);
    static void End();
    static Material* get(std::string);
    //static void setParam(std::string mat_id, std::string param_id, float param);
    static void setAmbient(std::string mat_id,const float r, const float g, const float b,const float w);//ka
    static void setDiffuse(std::string mat_id, const float r, const float g, const float b,const float w);//kd
    static void setSpecular(std::string mat_id, const float r, const float g, const float b,const float w);//ks
    static void setEmmisive(std::string mat_id, const float r, const float g, const float b,const float w);//ke
    static void setSpecularExp(std::string mat_id,float param);//Ns
    static void setTransparency(std::string mat_id,float param);//d
    static void setTransmission(std::string mat_id, const float r, const float g, const float b,const float w);//Tf
    static void setOpticalDensity(std::string mat_id,float param);//Ni
    static void setIllumination(std::string mat_id,int param);//illum

    static void setDiffuseTex(std::string mat_id,std::string param);//map_Kd

    static void apply(std::string);
    void apply();
    static void releaseTexture(std::string);
    //virtual void setMaterial();
};

#endif