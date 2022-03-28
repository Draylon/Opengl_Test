#include <GL/glew.h>

#include "Model.hpp"
#include "Material.hpp"

std::vector<Model*> Model:: model_list;

void Model::init(){}

void Model::loadOBJ(std::istream& in){
    int latest_mesh = 0;

    std::string lineStr;
    while (std::getline(in, lineStr)) {
        std::istringstream lineSS(lineStr);
        std::string lineType;
        lineSS >> lineType;

        if (lineType == "#")
            continue;

        // vertex
        if (lineType == "v") {
            float x = 0, y = 0, z = 0, w = 1;
            lineSS >> x >> y >> z >> w;
            positions.push_back(glm::vec4(x, y, z, w));
            continue;
        }

        // texture
        if (lineType == "vt") {
            float u = 0, v = 0, w = 0;
            lineSS >> u >> v;// >> w;
            //printf("%f %f\n", u,v);
            texcoords.push_back(glm::vec3(u, v, w));
            continue;
        }

        // normal
        if (lineType == "vn") {
            float i = 0, j = 0, k = 0;
            lineSS >> i >> j >> k;
            normals.push_back(glm::normalize(glm::vec3(i, j, k)));
            continue;
        }

        if (lineType == "o") {
            //object? mesh?
            //object == mesh?
            // blender object?
            // 
            //  == vertex groups
        }

        if (lineType == "s") {
            // Smooth Shading   ( 1 or off)
        }

        if (lineType == "l") {
            //Draw line
        }

        if (lineType == "g"){
            std::string mesh_name;
            lineSS >> mesh_name;
            // GROUP -> mesh
            if (!mesh_defined) {
                mesh_defined = true;
                meshes[current_mesh]->mesh_id = mesh_name;
            }
            continue;
        }

        if (lineType == "mtllib"){
            mat_lib_defined = true;
            // meshes have material library!!
            std::string a;
            lineSS >> a;
            this->loadMatLibrary(a);
        }

        if (lineType == "usemtl"){
            // if loaded material library ->
            std::string a;
            lineSS >> a;
            meshes[current_mesh]->material_id = a;
            continue;
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

                for (size_t j = 0; j < 3; ++j){
                    Vertex vert;
                    vert.position = glm::vec3(positions[p[j]->v]);
                    vert.texcoord = glm::vec2(texcoords[p[j]->vt]);
                    vert.normal = (p[j]->vn != 0 ? normals[p[j]->vn] : faceNormal);
                    //verts.push_back(vert);
                    meshes[current_mesh]->verts.push_back(vert);
                }
            }
        }
    }
}

void Model::enableTextures(bool v){
    allow_tex = v;
}

void Model::enableMaterials(bool v){
    allow_mat = v;
}

void Model::loadMatLibrary(std::string libname){
    std::ifstream f1(libname);
    std::string lineStr;

    std::string defined_material;

    while (std::getline(f1, lineStr)) {
        std::istringstream lineSS(lineStr);
        std::string lineType;
        lineSS >> lineType;

        if (lineType == "#")
            continue;

        //create / check for material
        if (lineType == "newmtl"){
            std::string mtname;
            lineSS >> mtname;
            defined_material = mtname;
            Material::create(mtname);
        }
        if (lineType == "Ns"){
            float p;
            lineSS >> p;
            Material::setSpecularExp(defined_material,p);
        }
        if (lineType == "Ka") {
            float r,g,b;
            lineSS >> r>>g>>b;
            Material::setAmbient(defined_material, r,g,b,1);
        }
        if (lineType == "Kd") {
            float r, g, b;
            lineSS >> r >> g >> b;
            Material::setDiffuse(defined_material, r,g,b,1);
        }
        if (lineType == "Ks") {
            float r, g, b,w;
            lineSS >> r >> g >> b;
            Material::setSpecular(defined_material, r,g,b,1);
        }
        if (lineType == "Ke") {
            float r, g, b;
            lineSS >> r >> g >> b;
            Material::setEmmisive(defined_material, r,g,b,1);
        }
        if (lineType == "Ni") {
            float p;
            lineSS >> p;
            Material::setOpticalDensity(defined_material, p);
        }
        if (lineType == "d"|| lineType == "Tr") {
            float p;        /* # some implementations use 'd'           */
            lineSS >> p;    /* others use 'Tr' (inverted: Tr = 1 - d)   */
            Material::setTransparency(defined_material, lineType == "Tr"?1-p:p);
        }
        if (lineType == "illum") {
            float p;
            lineSS >> p;
            Material::setIllumination(defined_material,p);
        }
        if (lineType == "map_Kd"){
            std::string p;
            lineSS >> p;
            Material::setDiffuseTex(defined_material,p);
        }

    }
}

//void Model::setTexture(Texture* t) {
//    this->texture = t;
//}

void Model::render() {
    glPushMatrix();

    //glTranslatef(0.0f, -1.0f, -3.0f);

    //glActiveTextureARB(GL_TEXTURE0_ARB);

    for (Mesh* m : meshes){
        //Material* mm = Material::get(m->material_id);
        if(allow_mat)
            Material::apply(m->material_id);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &m->verts[0].position);
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, sizeof(Vertex), &m->verts[0].normal);
        //glActiveTextureARB(GL_TEXTURE0_ARB);
        //this->texture->Bind();
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &m->verts[0].texcoord);


        glDrawArrays(GL_TRIANGLES, 0, m->verts.size());

        //this->texture->Unbind();
        if (allow_mat)
            Material::releaseTexture(m->material_id);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
    }



    glPopMatrix();
}


//void Model::render() {
//    glPushMatrix();
//
//    //glTranslatef(0.0f, -1.0f, -3.0f);
//
//    //glActiveTextureARB(GL_TEXTURE0_ARB);
//
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &verts[0].position);
//    glEnableClientState(GL_NORMAL_ARRAY);
//    glNormalPointer(GL_FLOAT, sizeof(Vertex), &verts[0].normal);
//    //glActiveTextureARB(GL_TEXTURE0_ARB);
//    //this->texture->Bind();
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &verts[0].texcoord);
//    
//
//    glDrawArrays(GL_TRIANGLES, 0, verts.size());
//
//    //this->texture->Unbind();
//
//    glDisableClientState(GL_VERTEX_ARRAY);
//    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//    glDisableClientState(GL_NORMAL_ARRAY);
//
//    
//
//    glPopMatrix();
//}