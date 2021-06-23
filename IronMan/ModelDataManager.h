#pragma once

#include "Libraries.h"

struct VectorsData {
	string vectorsFilePath;
	vector<glm::vec3> v;
	vector<glm::vec2> vt;
	vector<glm::vec3> vn;
};

struct MaterialData {
	string materialsFilePath;
	glm::vec3 Ka;
	glm::vec3 Kd;
	glm::vec3 Ks;
	float Ns;
	float Ni;
};

class ModelDataManager
{
	public:
		ModelDataManager(string vectorsFileName);
		~ModelDataManager();

		VectorsData getVectorsData();
		MaterialData getMaterialData();
		string getTextureFilePath();

	private:
		void readDataFiles(string fileName);

		VectorsData vectorsData;
		MaterialData materialData;
		string textureFilePath;

};