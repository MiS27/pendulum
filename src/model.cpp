#include "model.h"

Model::Model(World *in_world) {
	world = in_world;
}

bool Model::load(string model_file) {
	clear();
	
	Assimp::Importer Importer;
	const aiScene* pScene = Importer.ReadFile(model_file.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
	
	if (!parse_scene(pScene, model_file)) {
		fprintf(stderr, "Error parsing '%s': '%s'\n", model_file.c_str(), Importer.GetErrorString());
		return false;
	} else {
		return true;
	}
}

bool Model::parse_scene(const aiScene *pScene, string &model_file) {
	if (pScene) {
		meshes.reserve(pScene->mNumMeshes);
		textures.reserve(pScene->mNumMaterials);
		
		if (!load_textures(pScene, model_file)) {
			return false;
		}
		
		for (unsigned i = 0, len = pScene->mNumMeshes; i < len; ++i) {
			const aiMesh* paiMesh = pScene->mMeshes[i];
			meshes.push_back(new Mesh(paiMesh, textures[paiMesh->mMaterialIndex, world]));
		}
	} else {
		return false;
	}
	
	return true;
}


bool Model::load_textures(const aiScene* pScene, const string& model_file) {
	string::size_type SlashIndex = model_file.find_last_of("/");
	string dir;
	
	if (SlashIndex == string::npos) {
		dir = ".";
	} else if (SlashIndex == 0) {
		dir = "/";
	} else {
		dir = model_file.substr(0, SlashIndex);
	}
	
	for (unsigned i = 0; i < pScene->mNumMaterials; ++i) {
		Texture *texture;
		if (load_texture_from_material(pScene->mMaterials[i], dir, &texture)) {
			textures.push_back(texture);
		} else {
			return false;
		}
	}
	
	return true;
}

bool Model::load_texture_from_material(aiMaterial *material, string &dir, Texture **texture) {
	if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
		aiString path;
		
		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
			string full_path = dir + "/" + path.data;
			*texture = new Texture(GL_TEXTURE_2D, full_path.c_str());
			
			if (!(*texture)->load()) {
				fprintf(stderr, "Error loading texture '%s'\n", full_path.c_str());
				delete *texture;
				*texture = NULL;
				res = false;
			} else {
				printf("Loaded texture '%s'\n", full_path.c_str());
			}
		}
	}
	
	if (!(*texture)) {
		printf("loading blank\n");
		*texture = new Texture(GL_TEXTURE_2D, "./models/blank.png");
		
		res = (*texture)->load();
	}
	
	return res;
}

void Model::clear() {
	for (unsigned i = 0, len = textures.size(); i < len; ++i) {
		delete textures[i];
	}
	
	textures.clear();
	
	for (unsigned i = 0, len = meshes.size(); i < len; ++i) {
		delete meshes[i];
	}
	
	meshes.clear();
}

Model::~Model() {
	clear();
}
void Model::draw() {
	for (unsigned i = 0, len = meshes.size(); i < len; ++i) {
		meshes[i]->draw();
	}
}
