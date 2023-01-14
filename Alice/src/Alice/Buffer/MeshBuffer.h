#pragma once
#include "Alice/Buffer/IndexBuffer.h"
#include "Alice/Buffer/VertexBuffer.h"
#include "Alice/Mesh/Mesh.h"
namespace Alice
{
	enum BatchType
	{
		NONE	= 0,
		TEXTURE	= BIT(0),
		NORMAL	= BIT(1),
	};
	class MeshBuffer
	{
	public:
		MeshBuffer(Mesh* mesh, const unsigned int type = BatchType::NONE);
		~MeshBuffer();
		void CreateMeshBuffer(Mesh* mesh);
		void GetVertexTexture();
		void GetVertexNormal();
	public:
		IndexBuffer* index_buffer;
		VertexBuffer* vertex_buffer;
		unsigned int length_per_vertex;
		unsigned int vertexCount;
		unsigned int faceEdgeCount;
		unsigned int faceCount;
	private:
		bool IsBatchTexture;
		bool IsBatchNormal;
	};
}

