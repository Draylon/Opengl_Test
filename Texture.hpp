#ifndef TEXTURE_ENTITY
#define TEXTURE_ENTITY
#include <string>
#include <vector>
#include <map>

class Texture {
private:
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int  m_Width, m_Height, m_BPP;
	unsigned int texID;

	static unsigned int texture_count;
	static std::map<std::string,Texture*> texture_list;
	
	Texture(const std::string& path);
public:
	static void End() {
		for (std::pair<std::string, Texture*> t : texture_list) {
			delete t.second;
		}
		texture_list.clear();
		/*for (int i = 0; i < texture_list.size(); i++)
			delete texture_list[i];*/
	}

	
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

	static Texture* fetch(std::string);
};

#endif