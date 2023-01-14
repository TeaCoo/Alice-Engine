#include "pch.h"
#include "MeshBuffer.h"
namespace Alice
{
	MeshBuffer::MeshBuffer(Mesh* mesh, const unsigned int type)
	{
		if (type & BatchType::TEXTURE)
			this->IsBatchTexture = true;
		else
			this->IsBatchTexture = false;

		if (type & BatchType::NORMAL)
			this->IsBatchNormal = true;
		else
			this->IsBatchNormal = false;

		CreateMeshBuffer(mesh);
	}

	MeshBuffer::~MeshBuffer()
	{
		delete this->index_buffer;
		delete this->vertex_buffer;
	}

	void MeshBuffer::CreateMeshBuffer(Mesh* mesh)
	{
		this->vertex_buffer = new VertexBuffer();
		this->index_buffer = new IndexBuffer();
		this->vertex_buffer->CreateBuffer(mesh->vertex_position.size());

		this->length_per_vertex = 3;
		if (this->IsBatchTexture)
			this->length_per_vertex += 2;
		if (this->IsBatchNormal)
			this->length_per_vertex += 3;

		this->vertexCount = mesh->vertex_position.size();
		for (int i = 0; i < mesh->vertex_position.size(); i++)
		{
			int batch_index = 0;
			this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = mesh->vertex_position[i].x;
			this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = mesh->vertex_position[i].y;
			this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = mesh->vertex_position[i].z;

			// need to be fixed !!!!!!///////////////
			if (this->IsBatchTexture && mesh->vertex_uv.size() != 0)
			{
				this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = 0;
				this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = 0;
			}

			if (this->IsBatchNormal && mesh->vertex_normal.size() != 0)
			{
				this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = 0;
				this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = 0;
				this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = 0;
			}
			//////////////////////////////////////////
		}
		for (int i = 0; i < mesh->mesh_type.size(); i++) 
		{
			if (mesh->mesh_type[i] == MeshType::TRIANGLES)
			{
				this->index_buffer->CreateBuffer(mesh->mesh_trangle_faces.size(), 3);
				for (int j = 0; j < mesh->mesh_trangle_faces.size(); j++)
				{
					this->index_buffer->index[3 * j + 0] = mesh->mesh_trangle_faces[j].vertexs[0] - 1;
					this->index_buffer->index[3 * j + 1] = mesh->mesh_trangle_faces[j].vertexs[1] - 1;
					this->index_buffer->index[3 * j + 2] = mesh->mesh_trangle_faces[j].vertexs[2] - 1;
				}
				this->faceEdgeCount = 3;
				this->faceCount = mesh->mesh_trangle_faces.size();
			}	
			if (mesh->mesh_type[i] == MeshType::QUADS)
			{
				this->index_buffer->CreateBuffer(mesh->mesh_quads_faces.size(), 4);
				for (int j = 0; j < mesh->mesh_quads_faces.size(); j++)
				{
					this->index_buffer->index[4 * j + 0] = mesh->mesh_quads_faces[j].vertexs[0] - 1;
					this->index_buffer->index[4 * j + 1] = mesh->mesh_quads_faces[j].vertexs[1] - 1;
					this->index_buffer->index[4 * j + 2] = mesh->mesh_quads_faces[j].vertexs[2] - 1;
					this->index_buffer->index[4 * j + 3] = mesh->mesh_quads_faces[j].vertexs[3] - 1;
				}
				this->faceEdgeCount = 4;
				this->faceCount = mesh->mesh_quads_faces.size();
			}	
		}
	}

	void MeshBuffer::GetVertexTexture()
	{

	}

	void MeshBuffer::GetVertexNormal()
	{

	}
}
