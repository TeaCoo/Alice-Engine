#include "pch.h"
#include "IndexBuffer.h"
namespace Alice
{
	IndexBuffer::IndexBuffer()
	{
	}

	IndexBuffer::~IndexBuffer()
	{
		if (this->index)
			DestoryBuffer();
	}

	void IndexBuffer::CreateBuffer(unsigned int size, unsigned int faceType)
	{
		this->IndexCount = size;
		this->index = (unsigned int*)malloc(sizeof(unsigned int) * size * faceType);
	}

	void IndexBuffer::DestoryBuffer()
	{
		free(this->index);
	}

	unsigned int IndexBuffer::GetIndexCount()
	{
		return this->IndexCount;
	}
}
