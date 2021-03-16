#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include <memory>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "../Core/Debug.h"
#include <glew.h>

struct Texture {
	GLuint textureID = 0;
	float width = 0.0f;
	float height = 0.0f;
	string textureName = "";
};

class TextureHandler
{
public:
	TextureHandler(const TextureHandler&) = delete;
	TextureHandler(TextureHandler&&) = delete;
	TextureHandler& operator=(const TextureHandler&) = delete;
	TextureHandler& operator=(TextureHandler&&) = delete;

	static TextureHandler* GetInstance();
	void OnDestroy();

	void CreateTexture(const string& textureName_, const string& textureFilePath_);
	const GLuint GetTexture(const string& textureName_);
	const Texture* GetTextureData(const string textureName_);
	
private:
	TextureHandler();
	~TextureHandler();

	static unique_ptr<TextureHandler> textureInstance;
	friend default_delete<TextureHandler>;
	static vector<Texture*> textures;










};

#endif // !TEXTUREHANDLER_H



