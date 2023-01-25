#include "pch.h"
#include "VertexBuffer.h"
namespace Alice
{
	VertexBuffer::VertexBuffer()
	{

	}

	VertexBuffer::~VertexBuffer()
	{
		if(this->positions)
			DestoryBuffer();
	}

	void VertexBuffer::CreateBuffer(unsigned int size)
	{
		this->positions = (float*)malloc(sizeof(float) * size);
	}

	void VertexBuffer::DestoryBuffer()
	{
		free(this->positions);
	}

	unsigned int VertexBuffer::GetVertexCount()
	{
		return this->VertexCount;
	}
}