#pragma once
namespace Alice
{
	class IndexBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();
		void CreateBuffer(unsigned int size, unsigned int faceType);
		void DestoryBuffer();
		unsigned int GetIndexCount();
	public:
		unsigned int* index = nullptr;	
	private:
		unsigned int IndexCount = 0;
		
	};
}

