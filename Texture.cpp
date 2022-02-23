#include "Texture.hpp"
#include <GL/glew.h>
#include <stb/stb_image.h>
#include <iostream>

std::map<std::string,Texture*> Texture::texture_list;
unsigned int Texture::texture_count;

Texture::Texture(const std::string& path){
	texture_list.emplace(path, this);
	if (texture_count == 0) {
		glEnable(GL_TEXTURE_2D);
	}
	texture_count++;

	m_FilePath = path;
	m_LocalBuffer = nullptr;
	m_Width = 110;
	m_Height = 110;
	m_BPP = 0;

	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	//          (GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	//           GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
	//glBindTexture(GL_TEXTURE_2D,texID);

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture() {
	glDeleteTextures(1,&texID);
	printf("texture deleted\n");
}

void Texture::Bind(unsigned int slot) const{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, texID);
}

void Texture::Unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture* Texture::fetch(std::string name) {
	if (texture_list.find(name) != texture_list.end()) {
		return texture_list[name];
	}
	Texture* tt = new Texture(name);
	return tt;
}