#include "file_management.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ios>
#include <cstdio>


class FILE_MANAGEMENT {

	void fileNew(std::string filepath, std::string filename, std::string filetype, bool include_date) {
		std::string fName = filepath + "/" + filename + filetype; //Concatenate the filename and filetype to the filepath
		std::ofstream newFile(fName);
		newFile.close();
	};
	void fileDelete(std::string filepath, std::string filename, std::string filetype) {
		std::string fName = filepath + "/" + filename + filetype; //Concatenate the filename to the filepath

		std::ifstream file(fName);
		const char* cFilePath = fName.c_str();
		remove(cFilePath);
	};
	void fileMove(std::string currentFilePath, std::string newFilePath, std::string filename, std::string filetype) {
		std::string fOldName = currentFilePath + "/" + filename + filetype; //Concatenate the filename to the filepath
		std::string fNewName = newFilePath + "/" + filename + filetype; //Concatenate the filename to the filepath
		std::ifstream old(fOldName, std::ios::in | std::ios::binary);
		std::ofstream fnew(fNewName, std::ios::out | std::ios::binary);
		fnew << old.rdbuf();
		old.close();
		fnew.close();
		fileDelete(currentFilePath, filename, filetype);
	};
	void fileCopy(std::string currentFilePath, std::string newFilePath, std::string filename, std::string filetype) {
		std::string fOldName = currentFilePath + "/" + filename + filetype; //Concatenate the filename to the filepath
		std::string fNewName = newFilePath + "/" + filename + " - copy" + filetype; //Concatenate the filename to the filepath
		std::ifstream original(fOldName, std::ios::in | std::ios::binary);
		std::ofstream copy(fNewName, std::ios::out | std::ios::binary);
		copy << original.rdbuf();
		original.close();
		copy.close();
	};
	std::string fileRead(std::string filepath, std::string filename, std::string filetype) {
		std::string fName = filepath + "/" + filename + filetype; //Concatenate the filename and filetype to the filepath
		std::string outputVar;
		std::ifstream file;
		file.open(fName, std::ios::in);
		file >> outputVar;
		return outputVar;
	};
	std::string fileReadLine(std::string filepath, std::string filename, std::string filetype, int line) {
		std::string fName = filepath + "/" + filename + filetype; //Concatenate the filename and filetype to the filepath
		std::string outputVar;
		std::ifstream file;
		file.open(fName, std::ios::in);

		while (line > 1) {
			getline(file, outputVar);
			line--;
		}

		getline(file, outputVar);

		file >> outputVar;
		return outputVar;
	};
	void fileWrite(std::string filepath, std::string filename, std::string filetype, std::string output, bool newline) {
		std::string fName = filepath + "/" + filename + filetype; //Concatenate the filename and filetype to the filepath
		std::string outputVar;
		std::ofstream file;
		file.open(fName, std::ios::out);
		file << output;
		if (newline == true) {
			file << "\n";
		}
		file.close();
	};
	void fileWrite(std::string filepath, std::string filename, std::string filetype, std::string output, bool newline, std::string output2, bool newline2) {
		std::string fName = filepath + "/" + filename + filetype; //Concatenate the filename and filetype to the filepath
		std::string outputVar;
		std::ofstream file;
		file.open(fName, std::ios::out);
		file << output;
		if (newline == true) {
			file << "\n";
		}
		file << output2;
		if (newline2 == true) {
			file << "\n";
		}
		file.close();
	};
	void fileWrite(std::string filepath, std::string filename, std::string filetype, std::string output, bool newline, std::string output2, bool newline2, std::string output3, bool newline3) {
		std::string fName = filepath + "/" + filename + filetype; //Concatenate the filename and filetype to the filepath
		std::string outputVar;
		std::ofstream file;
		file.open(fName, std::ios::out);
		file << output;
		if (newline == true) {
			file << "\n";
		}
		file << output2;
		if (newline2 == true) {
			file << "\n";
		}
		file << output3;
		if (newline3 == true) {
			file << "\n";
		}
		file.close();
	};
	void fileWrite(std::string filepath, std::string filename, std::string filetype, std::string output, bool newline, std::string output2, bool newline2, std::string output3, bool newline3, std::string output4, bool newline4) {
		std::string fName = filepath + "/" + filename + filetype; //Concatenate the filename and filetype to the filepath
		std::string outputVar;
		std::ofstream file;
		file.open(fName, std::ios::out);
		file << output;
		if (newline == true) {
			file << "\n";
		}
		file << output2;
		if (newline2 == true) {
			file << "\n";
		}
		file << output3;
		if (newline3 == true) {
			file << "\n";
		}
		file << output4;
		if (newline4 == true) {
			file << "\n";
		}
		file.close();
	};
};