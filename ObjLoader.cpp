#ifndef OBJ_LOADER
#define OBJ_LOADER

#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>

/*

//headers
//#include<GL/gl.h>
#include<GL/freeglut.h>
#include <cstdio>

//globals
GLuint elephant;
float elephantrot;
char ch = '1';
//other functions and main
//wavefront .obj loader code begins
void loadObj(char* fname) {
    FILE* fp;
    int read;
    GLfloat x, y, z;
    char ch;
    elephant = glGenLists(1);
    fopen_s(&fp, fname, "r");
    if (!fp)
    {
        printf("can't open file %s\n", fname);
        exit(1);
    }
    glPointSize(2.0);
    glNewList(elephant, GL_COMPILE);
    {
        glPushMatrix();
        glBegin(GL_QUADS);
        while (!(feof(fp))) {
            read = fscanf_s(fp, "%c", &ch, 1);
            read += fscanf_s(fp, "%f", &x);
            read += fscanf_s(fp, "%f", &y);
            read += fscanf_s(fp, "%f", &z);
            if (read == 4 && ch == 'v') {
                glVertex3f(x, y, z);
            }
        }
        glEnd();
    }
    glPopMatrix();
    glEndList();
    fclose(fp);
}
//wavefront .obj loader code ends here



void drawElephant() {
    glPushMatrix();
    glTranslatef(0, -40.00, -105);
    glColor3f(1.0, 0.23, 0.27);
    glScalef(0.1, 0.1, 0.1);
    glRotatef(elephantrot, 0, 1, 0);
    glCallList(elephant);
    glPopMatrix();
    elephantrot = elephantrot + 0.6f;
    if (elephantrot > 360)elephantrot = elephantrot - 360;
}

/*
void reshape_2(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
    //glOrtho(-25,25,-2,2,0.1,100);
    glMatrixMode(GL_MODELVIEW);
}

void display_2(void){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawElephant();
    glutSwapBuffers(); //swap the buffers
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 450);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("ObjLoader");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    loadObj("data/elepham.obj");//replace elepham.obj withp orsche.obj or radar.obj or any other .obj to display it
    glutMainLoop();
    return 0;
}*/


struct Vertex{
    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec3 normal;
};

struct VertRef{
    VertRef(int v, int vt, int vn) : v(v), vt(vt), vn(vn) { }
    int v, vt, vn;
};

std::vector< Vertex > LoadOBJ(std::istream& in){
    std::vector< Vertex > verts;

    std::vector< glm::vec4 > positions(1, glm::vec4(0, 0, 0, 0));
    std::vector< glm::vec3 > texcoords(1, glm::vec3(0, 0, 0));
    std::vector< glm::vec3 > normals(1, glm::vec3(0, 0, 0));
    std::string lineStr;
    while (std::getline(in, lineStr)) {
        std::istringstream lineSS(lineStr);
        std::string lineType;
        lineSS >> lineType;

        // vertex
        if (lineType == "v"){
            float x = 0, y = 0, z = 0, w = 1;
            lineSS >> x >> y >> z >> w;
            positions.push_back(glm::vec4(x, y, z, w));
        }

        // texture
        if (lineType == "vt"){
            float u = 0, v = 0, w = 0;
            lineSS >> u >> v >> w;
            texcoords.push_back(glm::vec3(u, v, w));
        }

        // normal
        if (lineType == "vn"){
            float i = 0, j = 0, k = 0;
            lineSS >> i >> j >> k;
            normals.push_back(glm::normalize(glm::vec3(i, j, k)));
        }

        // polygon
        if (lineType == "f"){
            std::vector< VertRef > refs;
            std::string refStr;
            while (lineSS >> refStr){
                std::istringstream ref(refStr);
                std::string vStr, vtStr, vnStr;
                std::getline(ref, vStr, '/');
                std::getline(ref, vtStr, '/');
                std::getline(ref, vnStr, '/');
                int v = atoi(vStr.c_str());
                int vt = atoi(vtStr.c_str());
                int vn = atoi(vnStr.c_str());
                v = (v >= 0 ? v : positions.size() + v);
                vt = (vt >= 0 ? vt : texcoords.size() + vt);
                vn = (vn >= 0 ? vn : normals.size() + vn);
                refs.push_back(VertRef(v, vt, vn));
            }

            // triangulate, assuming n>3-gons are convex and coplanar
            for (size_t i = 1; i + 1 < refs.size(); ++i){
                const VertRef* p[3] = { &refs[0], &refs[i], &refs[i + 1] };

                // http://www.opengl.org/wiki/Calculating_a_Surface_Normal
                glm::vec3 U(positions[p[1]->v] - positions[p[0]->v]);
                glm::vec3 V(positions[p[2]->v] - positions[p[0]->v]);
                glm::vec3 faceNormal = glm::normalize(glm::cross(U, V));

                for (size_t j = 0; j < 3; ++j)
                {
                    Vertex vert;
                    vert.position = glm::vec3(positions[p[j]->v]);
                    vert.texcoord = glm::vec2(texcoords[p[j]->vt]);
                    vert.normal = (p[j]->vn != 0 ? normals[p[j]->vn] : faceNormal);
                    verts.push_back(vert);
                }
            }
        }
    }

    return verts;
}

#endif