#pragma once
namespace Alice
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();
		void CreateBuffer(unsigned int size);
		void DestoryBuffer();
		unsigned int GetVertexCount();
	public:
		float* positions = nullptr;
	private:
		unsigned int VertexCount = 0;
	};
}

