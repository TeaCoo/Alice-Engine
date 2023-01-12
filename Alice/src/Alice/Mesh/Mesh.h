#pragma once
namespace Alice {
	struct VertexPosition
	{
		float x;
		float y;
		float z;
	};

	struct VertexUV
	{
		float u;
		float v;
	};

	struct VertexNormal
	{
		float x;
		float y;
		float z;
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

	class Mesh
	{
	public:
		bool FinalCheck();
		
	public:
		std::vector<std::string>	mesh_name;
		std::vector<MeshType>		mesh_type;

		std::vector<VertexPosition> vertex_position;
		std::vector<VertexNormal>	vertex_normal;
		std::vector<VertexUV>		vertex_uv;
		std::vector<TrangleFace>	mesh_trangle_faces;
		std::vector<QuadsFace>		mesh_quads_faces;
	};

	std::ostream& operator<<(std::ostream& outStream, Mesh* mesh);
}
