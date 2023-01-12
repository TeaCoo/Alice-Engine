#pragma once
namespace Alice
{
	class FileReader
	{
	public:
		FileReader();
		FileReader(std::string fileName);
		~FileReader();
		bool ReadFile(std::string fileName);
		bool IsOpen();
		std::vector<std::string> split(std::string s, std::string delimiter);
	protected:
		std::fstream fileStream;
	private:
		bool isOpen = false;
	};
}

