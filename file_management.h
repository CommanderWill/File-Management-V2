#pragma once
#include <string>


class FILE_MANAGEMENT {
public:

	void fileNew(std::string filepath, std::string filename, std::string filetype, bool include_date);
	void fileDelete(std::string filepath, std::string filename, std::string filetype);
	void fileMove(std::string currentFilePath, std::string newFilePath, std::string filename, std::string filetype);
	void fileCopy(std::string currentFilePath, std::string newFilePath, std::string filename, std::string filetype);

	std::string fileRead(std::string filepath, std::string filename, std::string filetype);
	std::string fileReadLine(std::string filepath, std::string filename, std::string filetype, int line);

	void fileWrite(std::string filepath, std::string filename, std::string filetype, std::string output, bool newline);
	void fileWrite(std::string filepath, std::string filename, std::string filetype, std::string output, bool newline, std::string output2, bool newline2);
	void fileWrite(std::string filepath, std::string filename, std::string filetype, std::string output, bool newline, std::string output2, bool newline2, std::string output3, bool newline3);
	void fileWrite(std::string filepath, std::string filename, std::string filetype, std::string output, bool newline, std::string output2, bool newline2, std::string output3, bool newline3, std::string output4, bool newline4);
};
