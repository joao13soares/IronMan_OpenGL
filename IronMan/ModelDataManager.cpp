#pragma once

#include "ModelDataManager.h"

ModelDataManager::ModelDataManager(string vectorsFileName)
{
	vectorsData.vectorsFilePath = "Model\\" + vectorsFileName;
	readDataFiles(vectorsData.vectorsFilePath);
	readDataFiles(materialData.materialsFilePath);
}

ModelDataManager::~ModelDataManager()
{
}

void ModelDataManager::readDataFiles(string vectorsFilePath) {
	string lineIdentifier;
	string line;

	ifstream vectorsFile(vectorsFilePath);

	if (vectorsFile.is_open()) {
		while (!vectorsFile.eof()) {
			getline(vectorsFile, line);
			istringstream ss(line);
			ss >> lineIdentifier;

			if (lineIdentifier == "mtllib")
			{
				string materialFileName;
				ss >> materialFileName;
				materialData.materialsFilePath = "Model\\" + materialFileName;
			}
			else if (lineIdentifier == "v")
			{
				glm::vec3 vTemp;
				ss >> vTemp.x >> vTemp.y >> vTemp.z;
				vectorsData.v.push_back(vTemp);
			}
			else if (lineIdentifier == "vt")
			{
				glm::vec2 vtTemp;
				ss >> vtTemp.x >> vtTemp.y;
				vectorsData.vt.push_back(vtTemp);
			}
			else if (lineIdentifier == "vn")
			{
				glm::vec3 vnTemp;
				ss >> vnTemp.x >> vnTemp.y >> vnTemp.z;
				vectorsData.vn.push_back(vnTemp);
			}
			else if (lineIdentifier == "Ka")
			{
				ss >> materialData.Ka.x >> materialData.Ka.y >> materialData.Ka.z;
			}
			else if (lineIdentifier == "Kd")
			{
				ss >> materialData.Kd.x >> materialData.Kd.y >> materialData.Kd.z;
			}
			else if (lineIdentifier == "Ks")
			{
				ss >> materialData.Ks.x >> materialData.Ks.y >> materialData.Ks.z;
			}
			else if (lineIdentifier == "Ns")
			{
				ss >> materialData.Ns;
			}
			else if (lineIdentifier == "Ni")
			{
				ss >> materialData.Ni;
			}
			else if (lineIdentifier == "map")
			{
				string textureFileName;
				ss >> textureFileName;
				textureFilePath = "Model\\" + textureFileName;
			}
		}

		vectorsFile.close();
	}
	else {
		cerr << "Erro ao abrir o ficheiro '" + vectorsFilePath + "'!\n";
	}
}

VectorsData ModelDataManager::getVectorsData() {
	return vectorsData;
}

MaterialData ModelDataManager::getMaterialData() {
	return materialData;
}

string ModelDataManager::getTextureFilePath() {
	return textureFilePath;
}