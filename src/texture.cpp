#include "texture.h"

#include <cstdio>

Texture::Texture(GLenum texture_target, const string& in_file_name) : file_name(in_file_name) {
	this->texture_target = texture_target;
	image = NULL;
}

bool Texture::load() {
	try {
		image = new Magick::Image(file_name);
		image->write(&blob, "RGBA");
	} catch (Magick::Error& error) {
		fprintf(stderr, "Error while loading texture '%s': %s\n", file_name.c_str(), error.what());
		return false;
	}

	init_bind();
	
	return true;
}

void Texture::init_bind() {
	glGenTextures(1, &texture_obj);
	glBindTexture(texture_target, texture_obj);
	glTexImage2D(texture_target, 0, GL_RGB, image->columns(), image->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, blob.data());
	glTexParameterf(texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Texture::bind() {
	glBindTexture(texture_target, texture_obj);
}

double Texture::size() {
	if (this && image) {
		return (double)image->columns() * image->rows();
	} else {
		return 0;
	}
}

string Texture::get_file_name() {
	return file_name;
}

bool Texture::operator==(const Texture &o) const {
	return file_name == o.file_name;
}
