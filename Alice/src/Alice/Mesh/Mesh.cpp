#include "pch.h"
#include "Mesh.h"
namespace Alice {
	bool Alice::Mesh::FinalCheck()
	{
		if (this->mesh_name.size() != this->mesh_type.size()
			|| this->mesh_type.size() == 0)
		{
			return false;
		}	
		else if (this->mesh_name.size() == 0) 
		{
			for (int i = 0; i < this->mesh_type.size(); i++)
			{
				this->mesh_name.push_back("Object_" + i + 1);
			}
			return true;
		}
		return true;
	}
	std::ostream& operator<<(std::ostream& outStream, Mesh* mesh)
	{
		std::map<MeshType, std::string> m;
		m[TRIANGLES] = "TRIANGLES";
		m[QUADS] = "QUADS";

		outStream << "===========================================" << std::endl;
		outStream << "Mesh Count: " << mesh->mesh_name.size() << std::endl;
		
		for (int i = 0; i < mesh->mesh_name.size();i++) 
		{
			outStream << "\tMesh Name: " << mesh->mesh_name[i] << std::endl;
			outStream << "\tMesh Type: " << m[mesh->mesh_type[i]] << std::endl;
		}
		outStream << "\tVertex Count: " << mesh->vertex_position.size() << std::endl;
		outStream << "\tTexture Count: " << mesh->vertex_uv.size() << std::endl;
		outStream << "\tNormal Count: " << mesh->vertex_normal.size() << std::endl;
		outStream << "\tFace Count(Triangle): " << mesh->mesh_trangle_faces.size() << std::endl;
		outStream << "\tFace Count(Quads): " << mesh->mesh_quads_faces.size() << std::endl;
		outStream << "===========================================";
		return outStream;
	}
}
