#include <iostream>
#include "Material.hpp"
#include <GL/glew.h>

std::map<std::string, Material*> Material::materials_by_name;
Material* Material::applied;

//void Material::setMaterial() {
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialf(GL_FRONT, GL_SHININESS, *mat_shininess);
//}

void Material::create(std::string name){
	if (materials_by_name.find(name) == materials_by_name.end()) {
		materials_by_name.emplace(name,new Material());
	}
}

void Material::End(){
	for (std::pair<std::string, Material*> p : materials_by_name) {
		delete p.second;
	}
}

Material* Material::get(std::string name){
	if (materials_by_name.find(name) != materials_by_name.end())
		return materials_by_name[name];
	return NULL;
}

void Material::setAmbient(std::string mat_id, const float r, const float g, const float b,const float w){
	materials_by_name[mat_id]->mat_ambient = glm::vec4(r, g, b,w);
}

void Material::setDiffuse(std::string mat_id, const float r, const float g, const float b,const float w){
	materials_by_name[mat_id]->mat_diffuse= glm::vec4(r,g,b,w);
}

void Material::setSpecular(std::string mat_id, const float r, const float g, const float b,const float w){
	materials_by_name[mat_id]->mat_specular= glm::vec4(r,g,b,w);
}

void Material::setEmmisive(std::string mat_id, const float r, const float g, const float b,const float w){
	materials_by_name[mat_id]->mat_emmissive = glm::vec4(r,g,b,w);
}

void Material::setSpecularExp(std::string mat_id, float param){
	materials_by_name[mat_id]->specular_exp = param;
}

void Material::setTransparency(std::string mat_id, float param){
	materials_by_name[mat_id]->transparency = param;
}

void Material::setTransmission(std::string mat_id, const float r, const float g, const float b,const float w){
	materials_by_name[mat_id]->transmission = glm::vec4(r,g,b,w);
}

void Material::setOpticalDensity(std::string mat_id, float param){
	materials_by_name[mat_id]->opticalDensity = param;
}

void Material::setIllumination(std::string mat_id, int param){
	materials_by_name[mat_id]->illumination = param;
}

void Material::setDiffuseTex(std::string mat_id, std::string param){
	materials_by_name[mat_id]->t_diffuse = Texture::fetch(param);
}

void Material::apply(std::string mat_){
	Material* mat = materials_by_name[mat_];
	mat->apply();
	/*glm::vec3& mat_ambient = mat->mat_ambient;
	glm::vec3& mat_diffuse = mat->mat_diffuse;
	float& specular_exp = mat->specular_exp;
	glm::vec3& mat_specular = mat->mat_specular;

    glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular[0]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, &mat_ambient[0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse[0]);
    glMaterialf(GL_FRONT, GL_SHININESS, specular_exp);
	if (mat->t_diffuse != NULL)
		mat->t_diffuse->Bind();*/
}

void Material::apply() {
	if (applied == this)
		return;
	applied = this;
    glMaterialfv(GL_FRONT, GL_SPECULAR, &mat_specular[0]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, &mat_ambient[0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &mat_diffuse[0]);
    glMaterialf(GL_FRONT, GL_SHININESS, specular_exp);
	if (t_diffuse != NULL)
		t_diffuse->Bind(0);
}

void Material::releaseTexture(std::string mat_){
	Material* mat = materials_by_name[mat_];
	if (mat->t_diffuse!=NULL)
		mat->t_diffuse->Unbind();
}