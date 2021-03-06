#include "gbcpch.h"
#include "FileIO.h"

namespace gbc
{
	std::string FileIO::ReadFile(const std::string& filepath)
	{
		std::ifstream file(filepath);
		if (file.is_open())
		{
			// Get the file size
			file.seekg(0, std::ios::end);
			size_t size = file.tellg();
			file.seekg(0, std::ios::beg);

			// Read the file into the string
			std::string contents(size, ' ');
			file.read(&contents[0], size);
			file.close();
			return contents;
		}
		return std::string();
	}
}
