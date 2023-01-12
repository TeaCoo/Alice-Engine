#pragma once
#include "FileReader.h"
#include "Alice/Mesh/Mesh.h"
namespace Alice
{
	class ObjFileReader : FileReader
	{
	public:
		ObjFileReader(std::string fileName);
		void CopyName(std::vector<std::string>& words);
		void CopyVertexPosition(std::vector<std::string>& words);
		void CopyVertexNormal(std::vector<std::string>& words);
		void CopyVertexTexture(std::vector<std::string>& words);
		void CopyMeshFace(std::vector<std::string>& words);
		void Exception(std::string exception);
	public:
		Mesh* meshes;
	private:
		bool IsGetType = false;
	};
}
