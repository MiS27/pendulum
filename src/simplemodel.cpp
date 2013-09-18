#include "simplemodel.h"

SimpleModel::SimpleModel(ShaderProgram *shaderProgram, Model *model) : Model(shaderProgram, model) {
}

bool SimpleModel::load(string model_file) {
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

bool SimpleModel::parse_scene(const aiScene *pScene, string &model_file) {
	if (pScene) {
		meshes.reserve(pScene->mNumMeshes);
		textures.reserve(pScene->mNumMaterials);
		
		if (!load_textures(pScene, model_file)) {
			return false;
		}
		cout<<"SimpleModel::parse_scene before Mesh"<<endl;
		for (unsigned i = 0, len = pScene->mNumMeshes; i < len; ++i) {
			const aiMesh* paiMesh = pScene->mMeshes[i];
			meshes.push_back(new Mesh(paiMesh, textures[paiMesh->mMaterialIndex], shaderProgram));
		}
	} else {
		return false;
	}
		//cout<<"SimpleModel::parse_scene after Mesh"<<endl;
	
	return true;
}


bool SimpleModel::load_textures(const aiScene* pScene, const string& model_file) {
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

bool SimpleModel::load_texture_from_material(aiMaterial *material, string &dir, Texture **texture) {
	bool res = true;
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

void SimpleModel::clear() {
	for (unsigned i = 0, len = textures.size(); i < len; ++i) {
		delete textures[i];
	}
	
	textures.clear();
	
	for (unsigned i = 0, len = meshes.size(); i < len; ++i) {
		delete meshes[i];
	}
	
	meshes.clear();
}

SimpleModel::~SimpleModel() {
	clear();
}

void SimpleModel::draw() {
	calculateM();
	shaderProgram->pass_matrix_to_shader("M", calculatedM);
	for (unsigned i = 0, len = meshes.size(); i < len; ++i) {
		meshes[i]->draw();
	}
}
