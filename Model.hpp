#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec3 normal;
};

struct VertRef{
    int v, vt, vn;
    VertRef(int v, int vt, int vn) : v(v), vt(vt), vn(vn) { }
};

class Model {
public:
    Model(){
        positions = std::vector<glm::vec4>(1, glm::vec4(0, 0, 0, 0));
        texcoords = std::vector<glm::vec3>(1, glm::vec3(0, 0, 0));
        normals = std::vector<glm::vec3>(1, glm::vec3(0, 0, 0));
    }

    std::vector< Vertex > verts;
    std::vector< glm::vec4 > positions;// (1, glm::vec4(0, 0, 0, 0));
    std::vector< glm::vec3 > texcoords;// (1, glm::vec3(0, 0, 0));
    std::vector< glm::vec3 > normals;// (1, glm::vec3(0, 0, 0));
    
    void loadOBJ(std::istream& in);

    void init();
    void draw();
};

#endif