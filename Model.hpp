#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <iostream>
#include "Texture.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec3 normal;
};

struct VertRef{
    int v, vt, vn;
    VertRef(int v, int vt, int vn) : v(v), vt(vt), vn(vn) { }
};

class Mesh{
public:
    Mesh(std::string id) :mesh_id(id) {}
    std::string mesh_id;
    std::string material_id;
    std::vector< Vertex > verts;
};

class Model {
private:
    static std::vector<Model*> model_list;

public:
    static void End(){
        for (int i = 0; i < model_list.size(); i++)
            delete model_list[i];
    }
    Model(){
        positions = std::vector<glm::vec4>(1, glm::vec4(0, 0, 0, 0));
        texcoords = std::vector<glm::vec3>(1, glm::vec3(0, 0, 0));
        normals = std::vector<glm::vec3>(1, glm::vec3(0, 0, 0));
    }
    Model(const char* name){
        positions = std::vector<glm::vec4>(1, glm::vec4(0, 0, 0, 0));
        texcoords = std::vector<glm::vec3>(1, glm::vec3(0, 0, 0));
        normals = std::vector<glm::vec3>(1, glm::vec3(0, 0, 0));
        std::ifstream in(name);
        std::cout << "file loaded";
        meshes.push_back(new Mesh("default_mesh"));
        this->loadOBJ(in);
    }
    ~Model() {
        for (Mesh* m : meshes)
            delete m;
    }
    
    //Texture* texture;
    //std::vector<std::string> materials;
    //std::vector< Vertex > verts;

    bool mat_lib_defined;
    bool mesh_defined;
    std::vector<Mesh*> meshes;
    int current_mesh = meshes.size();

    std::vector< glm::vec4 > positions;// (1, glm::vec4(0, 0, 0, 0));
    std::vector< glm::vec3 > texcoords;// (1, glm::vec3(0, 0, 0));
    std::vector< glm::vec3 > normals;// (1, glm::vec3(0, 0, 0));
    
    void loadOBJ(std::istream& in);
    //void setTexture(Texture* t);
    void enableTextures(bool);
    void enableMaterials(bool);
    void loadMatLibrary(std::string);

    virtual void init();
    virtual void render();
};

#endif