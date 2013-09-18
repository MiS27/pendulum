#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "shared.h"

using namespace std;

class Texture {
private:
	string file_name;
	GLenum texture_target;
	GLuint texture_obj;
	Magick::Image* image;
	Magick::Blob blob;
	
	void init_bind();
public:
	Texture(GLenum texture_target, const string& file_name);

	string get_file_name();

	bool load();
	void bind();
	double size();

	bool operator==(const Texture &o) const;
};


#endif
