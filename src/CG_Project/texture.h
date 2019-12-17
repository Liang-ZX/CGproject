#pragma once
#pragma warning(disable : 4996)
#include "define.h"
#include "glew.h"
#include <string>

using namespace std;

class Texture
{
private:
	GLuint textureID;
	string texturePath;
	int textureType;

	int power_of_two(int n)
	{
		if (n <= 0) return 0;
		return (n&(n - 1)) == 0;
	}

	GLuint load_texture(const char *file_name)
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		GLint width, height, total_bytes;
		GLuint last_texture_ID, texture_ID = 0;
		GLubyte *pixels = NULL;
		FILE *pFile;

		if ((pFile = fopen(file_name, "rb")) == NULL)
		{
			printf("Read texture error\n");
			return 0;
		}

		fseek(pFile, 18, SEEK_SET);
		fread(&width, sizeof(width), 1, pFile);
		fread(&height, sizeof(height), 1, pFile);
		fseek(pFile, 54, SEEK_SET);

		total_bytes = (width * 3 + (4 - width * 3 % 4) % 4)*height;

		if ((pixels = (GLubyte *)malloc(total_bytes)) == NULL)
		{
			fclose(pFile);
			return 0;
		}

		if (fread(pixels, total_bytes, 1, pFile) <= 0)
		{
			free(pixels);
			fclose(pFile);
			return 0;
		}

		{
			GLint max;
			glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
			if (!power_of_two(width) || !power_of_two(height) || width > max || height > max)
			{
				const GLint new_width = 256;
				const GLint new_height = 256;
				GLint new_total_bytes;
				GLubyte *new_pixels = NULL;

				new_total_bytes = (new_width * 3 + (4 - new_width * 3 % 4) % 4)*new_height;
				new_pixels = (GLubyte *)malloc(new_total_bytes);
				if (new_pixels == NULL)
				{
					free(pixels);
					fclose(pFile);
					return 0;
				}

				gluScaleImage(GL_RGB,
					width, height, GL_UNSIGNED_BYTE, pixels,
					new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

				free(pixels);
				pixels = new_pixels;
				width = new_width;
				height = new_height;
			}
		}

		glGenTextures(1, &texture_ID);
		if (texture_ID == 0)
		{
			free(pixels);
			fclose(pFile);
			return 0;
		}

		glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&last_texture_ID);
		glBindTexture(GL_TEXTURE_2D, texture_ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);		// textureType = GL_REPLACE GL_BLEND GL_MODULATE
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
		glBindTexture(GL_TEXTURE_2D, last_texture_ID);

		free(pixels);
		fclose(pFile);
		return texture_ID;
	}

public:
	Texture(string texturePath)
	{
		this->texturePath = texturePath;
		textureID = load_texture(texturePath.c_str());
	}

	GLuint getID(void)
	{
		return textureID;
	}
};