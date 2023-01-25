#include "pch.h"
#include "ObjFileReader.h"

namespace Alice
{
	ObjFileReader::ObjFileReader(std::string fileName)
	{
		if (this->ReadFile(fileName))
		{
			this->meshes = new Mesh();
			std::string line;
			while (getline(this->fileStream, line))
			{
				std::vector<std::string> words = split(line, " ");
				if (words.size() != 0)
				{
					if (words[0] == "#")
					{
						continue;
					}	
					if (words[0] == "o")
					{
						if (words.size() < 2)	// exception no name
						{
							continue;
						}
						else
						{
							CopyName(words);
						}
					}	
					if (words[0] == "v")
					{
						if (words.size() < 4)
						{
							Exception("Read vertex position fail");
							break;
						}
						else
						{
							CopyVertexPosition(words);
						}
					}
					if (words[0] == "vt")
					{
						if (words.size() < 3)
						{
							Exception("Read vertex texture fail");
							break;
						}
						else
						{
							CopyVertexTexture(words);
						}
					}
					if (words[0] == "vn")
					{
						if (words.size() < 4)
						{
							Exception("Read vertex normal fail");
							break;
						}
						else
						{
							CopyVertexNormal(words);
						}
					}
					if (words[0] == "f")
					{
						if (words.size() < 4)
						{
							Exception("Read vertex face fail");
							break;
						}
						else
						{
							CopyMeshFace(words);
						}
					}
					if (words[0] == "s")
					{

					}
				}
			}
			if (!this->meshes->FinalCheck()) 
			{
				Exception("Load mesh fail, count of name and type not match.");
			}
		}
	}

	void ObjFileReader::CopyName(std::vector<std::string>& words)
	{
		this->meshes->mesh_name.push_back(words[1]);
		if (this->IsGetType)
			this->IsGetType = false;
	}

	void ObjFileReader::CopyVertexPosition(std::vector<std::string>& words)
	{
		glm::vec3 position;
		position.x = atof(words[1].c_str());
		position.y = atof(words[2].c_str());
		position.z = atof(words[3].c_str());
		this->meshes->vertex_position.emplace_back(position);
	}

	void ObjFileReader::CopyVertexNormal(std::vector<std::string>& words)
	{
		glm::vec3 normal;
		normal.x = atof(words[1].c_str());
		normal.y = atof(words[2].c_str());
		normal.z = atof(words[3].c_str());
		this->meshes->vertex_normal.emplace_back(normal);
	}

	void ObjFileReader::CopyVertexTexture(std::vector<std::string>& words)
	{
		glm::vec2 texture;
		texture.x = atof(words[1].c_str());
		texture.y = atof(words[2].c_str());
		this->meshes->vertex_uv.emplace_back(texture);
	}

	void ObjFileReader::CopyMeshFace(std::vector<std::string>& words)
	{
		if (words.size() == 4)	//trangle face
		{
			TrangleFace triange_face;
			if (!this->IsGetType)
			{
				this->meshes->mesh_type.push_back(MeshType::TRIANGLES);
				this->IsGetType = true;
			}
			for (int i = 1; i < words.size(); i++) 
			{
				std::vector<std::string> data = split(words[i], "/");
				triange_face.vertexs[i - 1] = atoi(data[0].c_str());
				triange_face.textures[i - 1] = atoi(data[1].c_str());
				triange_face.normals[i - 1] = atoi(data[2].c_str());

				addVertix(
					this->meshes->vertex_position[triange_face.vertexs[i - 1] - 1],
					this->meshes->vertex_normal[triange_face.normals[i - 1] - 1],
					glm::vec3(0),
					this->meshes->vertex_uv[triange_face.textures[i - 1] - 1]
				);
			}
			this->meshes->mesh_trangle_faces.emplace_back(triange_face);
		}
		else if (words.size() == 5) //quads face
		{
			QuadsFace quads_face;
			if (!this->IsGetType)
			{
				this->meshes->mesh_type.push_back(MeshType::QUADS);
				this->IsGetType = true;
			}
			for (int i = 1; i < words.size(); i++)
			{
				std::vector<std::string> data = split(words[i], "/");
				quads_face.vertexs[i - 1] = atoi(data[0].c_str());
				quads_face.textures[i - 1] = atoi(data[1].c_str());
				quads_face.normals[i - 1] = atoi(data[2].c_str());

				addVertix(
					this->meshes->vertex_position[quads_face.vertexs[i - 1] - 1],
					this->meshes->vertex_normal[quads_face.normals[i - 1] - 1],
					glm::vec3(0),
					this->meshes->vertex_uv[quads_face.textures[i - 1] - 1]
				);
			}
			this->meshes->mesh_quads_faces.emplace_back(quads_face);
		}
	}

	void ObjFileReader::addVertix(glm::vec3 position, glm::vec3 normal, glm::vec3 color, glm::vec2 UV)
	{
		Vert vec(position, normal, color, UV);
		this->meshes->vertices.emplace_back(vec);
	}

	void ObjFileReader::Exception(std::string exception)
	{
		delete this->meshes;
		ALICE_CORE_ERROR("<ERROR> " + exception);
	}

}
