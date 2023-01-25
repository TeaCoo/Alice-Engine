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
		this->length_per_vertex = 3 + 2 + 3; // 3 for position, 2 for texture, 3 for normal
		this->vertex_buffer->CreateBuffer(mesh->vertices.size() * this->length_per_vertex);
		if (mesh->mesh_type[0] == MeshType::TRIANGLES)
			this->index_buffer->CreateBuffer(mesh->vertices.size(), 3);
		else if (mesh->mesh_type[0] == MeshType::QUADS)
			this->index_buffer->CreateBuffer(mesh->vertices.size(), 4);

		this->vertexCount = mesh->vertices.size();
		this->indexCount = mesh->vertices.size();
		for (int i = 0; i < mesh->vertices.size(); i++)
		{
			int batch_index = 0;
			this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = mesh->vertices[i].position.x;
			this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = mesh->vertices[i].position.y;
			this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = mesh->vertices[i].position.z;

			if (this->IsBatchTexture && mesh->vertex_uv.size() != 0)
			{
				this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = mesh->vertices[i].UV.x;
				this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = mesh->vertices[i].UV.y;
			}
			else 
			{
				this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = 0;
				this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = 0;
			}

			if (this->IsBatchNormal && mesh->vertex_normal.size() != 0)
			{
				this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = mesh->vertices[i].normal.x;
				this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = mesh->vertices[i].normal.y;
				this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = mesh->vertices[i].normal.z;
			}
			else
			{
				this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = 0;
				this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = 0;
				this->vertex_buffer->positions[this->length_per_vertex * i + batch_index++] = 0;
			}

			this->index_buffer->index[i] = i;
		}
		/*
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
		*/
	}

	void MeshBuffer::GetVertexTexture()
	{

	}

	void MeshBuffer::GetVertexNormal()
	{

	}
}
