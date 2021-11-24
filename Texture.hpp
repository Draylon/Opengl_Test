#include <string>
#ifndef TEXTURE_ENTITY
#define TEXTURE_ENTITY


class Texture {
private:
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int  m_Width, m_Height, m_BPP;

public:
	Texture(){}
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};

#endif