#include "pch.h"
#include "ShaderProcessor.h"
namespace Alice
{
	ShaderProcessor::ShaderProcessor(std::string vertPath, std::string fragPath)
	{
		std::fstream vertStream;
		vertStream.open(vertPath);
		this->vert = getText(vertStream);

		std::fstream fragStream;
		fragStream.open(fragPath);
		this->frag = getText(fragStream);
	}

	std::string ShaderProcessor::getText(std::fstream& fileStream)
	{
		std::string result;
		std::string line;
		while (getline(fileStream, line))
		{
			result += "\n" + line;
		}
		return result;
	}
}