#pragma once
#include <glm/vec3.hpp> 
#include <glm/vec2.hpp> 
namespace Alice {
	struct Vert
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
		glm::vec2 UV;

		// To allow for emplace_back()
		Vert(const glm::vec3& P, const glm::vec3& N, const glm::vec3& C, const glm::vec2& U)
			: position(P), normal(N), color(C), UV(U) {}
		// Allow for float based data
		Vert(float P_x, float P_y, float P_z, float N_x, float N_y, float N_z,
			float C_r, float C_g, float C_b, float T_u, float T_v)
			: position(P_x, P_y, P_z), normal(N_x, N_y, N_z), color(C_r, C_g, C_b), UV(T_u, T_v) {}
		// Equality for hashing
		bool operator== (const Vert& b) const {
			return (position == b.position && normal == b.normal && color == b.color && UV == b.UV);
		}
		Vert() : position(glm::vec3(0)), normal(glm::vec3(0)), color(glm::vec3(0)), UV(glm::vec2(0)) {}
	};

	struct TrangleFace
	{
		unsigned int  vertexs[3];
		unsigned int  textures[3];
		unsigned int  normals[3];
	};

	struct QuadsFace
	{
		unsigned int vertexs[4];
		unsigned int textures[4];
		unsigned int normals[4];
	};

	enum MeshType
	{
		TRIANGLES,
		QUADS,
	};

	class ALICE_API Mesh
	{
	public:
		bool FinalCheck();
		
	public:
		std::vector<std::string>	mesh_name;
		std::vector<MeshType>		mesh_type;

		std::vector<glm::vec3>		vertex_position;
		std::vector<glm::vec3>		vertex_normal;
		std::vector<glm::vec2>		vertex_uv;
		std::vector<TrangleFace>	mesh_trangle_faces;
		std::vector<QuadsFace>		mesh_quads_faces;
		
		std::vector<Vert>			vertices;
	};

	std::ostream& operator<<(std::ostream& outStream, Mesh* mesh);
}
