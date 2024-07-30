#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
#include <utility>

//--------------------------------------------------!!IMPORTANT!!-----------------------------------------------------------
//
// AS OF 4/4/2024 ALL FUNCTIONS HAVE BEEN TESTED EXCEPT FOR WRITE FUNCTIONS
// 
// CURRENT FUNCTIONALITY:
// - Create (directory/file)
// - Delete (directory/file)
// - Copy (directory/file)
// - Move (directory/file)
// - Check Existing (directory/file)
// 
// PLANNED FUNCTIONALITY:
// - Write
// 
// Last progress date: 7/16/2024
// Last progress time: 2044
// Last progress: added base for write functions
//-----------------------------------------------------------------------------------------------------------------------------------

class FILEMANAGEMENT {
protected:
	//General Vars
	std::string appDirectory = std::filesystem::current_path().string();
	std::string secondaryPath;
	
	//Read/Write Vars
	std::string EMPTY;
	std::string contents;
	int totalLines{};
	int currentLine{};
	int endLine{};
	std::fstream file;
	std::ifstream readFile;
	std::ofstream temp;
	std::ostringstream buffer;
	std::string sbuffer;

	//functions that provide common operations but arnt needed outside of the class
	static std::string pathBuilder(const std::string& directory, const std::string& name) {
		return directory + "\\" + name;
	}

public: 
	//Identifiers for use as inputs for public functions
	enum itemType { Directory, File };
	//---------------------Directory/File Operations---------------------
	//Tested Working 3/30/24
	//--------------------------------------------------------------------------------
	void Create(const itemType itemType, const bool currentDirectory, std::string directory, const std::string& name) const
	{
		if (currentDirectory) {
			directory = pathBuilder(appDirectory, pathBuilder(directory, name));
		}
		else {
			directory = pathBuilder(directory, name);
		}
		if (itemType == Directory) {
			std::filesystem::create_directory(directory);
		}
		else if (itemType == File) {
			std::ofstream newFile(directory);
			newFile.close(); // ofstream opens files after creation, therefor it must be closed to clean up memory
		}
		//In the future no-solution errorhandling goes here
	}
	void Create(const itemType itemType, const bool currentDirectory, std::string path) const
	{
		if (currentDirectory) {
			path = pathBuilder(appDirectory, path);
		}
		if (itemType == Directory) {
			std::filesystem::create_directory(path);
		}
		else if (itemType == File) {
			std::ofstream newFile(path);
			newFile.close(); // ofstream opens files after creation, therefor it must be closed to clean up memory
		}
		//In the future no-solution errorhandling goes here
	}
	void DeleteDirectory(const bool currentDirectory, std::string directory, const bool deleteIfNotEmpty) const
	{
		if (currentDirectory) {
			directory = pathBuilder(appDirectory, directory);
		}
		std::cout << "Path Selected\n" << std::endl;
		std::cout << "Target Path: " << directory << std::endl;
		if (exists(directory)) {
			if (deleteIfNotEmpty) {
				std::cout << "File Exists State 1\n" << std::endl;
				std::filesystem::remove_all(directory); //Delete directory & anything in it
			}
			else {
				std::cout << "File Exists State 2\n" << std::endl;
				std::filesystem::remove(directory); //Deletes only an empty directory
			}
			std::cout << "Success\n" << std::endl;
		}
		else {
			std::cout << "Directory Doesnt Exists\n" << std::endl;
		}
	}
	void DeleteFile(const bool currentDirectory, std::string directory, const std::string& name) const
	{
		if (currentDirectory) {
			directory = pathBuilder(appDirectory, pathBuilder(directory, name));
		}
		else {
			directory = pathBuilder(directory, name);
		}
		if (exists(directory)) {
			std::cout << "File Exists\n" << std::endl;
			std::filesystem::remove(directory);
			std::cout << "Success\n" << std::endl;
		}
		else {
			std::cout << "File Doesnt Exists\n" << std::endl;
		}
	}
	void DeleteFile(const bool currentDirectory, std::string path) const
	{
		if (currentDirectory) {
			path = pathBuilder(appDirectory, path);
		}
		if (exists(path)) {
			std::cout << "File Exists\n" << std::endl;
			std::filesystem::remove(path);
			std::cout << "Success\n" << std::endl;
		}
		else {
			std::cout << "File Doesnt Exists\n" << std::endl;
		}
	}

	//----------Copy Operations -------------------------------------------
	//Tested Working 4/4/24
	//--------------------------------------------------------------------------------
	void CopyDirectory(const bool relToCurrentDirectory, std::string currentDirectory, const std::string& currentDirectoryName, const std::string& newDirectory, std::string newDirectoryName, const bool directoriesOnly, const bool overwriteExisting) const
	{ //Directory Copying
		std::cout << "Full Path Selection\n" << std::endl;
		if (relToCurrentDirectory) {
			std::cout << "Current DIrectory\n" << std::endl;
			currentDirectory = pathBuilder(appDirectory, pathBuilder(currentDirectory, currentDirectoryName));
			newDirectoryName = pathBuilder(appDirectory, pathBuilder(newDirectory, newDirectoryName));
		}
		else {
			std::cout << "Without Current Directory\n" << std::endl;
			currentDirectory = pathBuilder(currentDirectory, currentDirectoryName);
			newDirectoryName = pathBuilder(newDirectory, newDirectoryName);
		}
		std::cout << "Path Selected\n" << std::endl;
		std::cout << "Copy Path: " << currentDirectory << std::endl;
		std::cout << "Target Path: " << newDirectoryName << std::endl;
		if (exists(newDirectoryName) && !overwriteExisting) {
			std::cout << "Directory Already Exists\n" << std::endl;			
		}
		else {
			try {
				if (directoriesOnly && overwriteExisting) { //Only copy directories and overwrite existing directories/files
					std::cout << "Directories Only & Overwrite Existing\n" << std::endl;
					constexpr std::filesystem::copy_options copyOptions = std::filesystem::copy_options::directories_only | std::filesystem::copy_options::overwrite_existing;
					std::filesystem::copy(currentDirectory, newDirectoryName, copyOptions);
					std::cout << "Success\n" << std::endl;
				}
				else if (directoriesOnly) { //Only copy directories, do not overwrite existing
					std::cout << "Directories Only\n" << std::endl;
					constexpr auto copyOptions = std::filesystem::copy_options::overwrite_existing;
					std::filesystem::copy(currentDirectory, newDirectoryName, copyOptions);
					std::cout << "Success\n" << std::endl;
				}
				else if (overwriteExisting) { //Copy directories & files, Overwrite Existing Directories/Files
					std::cout << "Overwrite Existing\n" << std::endl;
					constexpr auto copyOptions = std::filesystem::copy_options::overwrite_existing;
					std::filesystem::copy(currentDirectory, newDirectoryName, copyOptions);
					std::cout << "Success\n" << std::endl;
				}
				else { //Include Files & Do Not Overwrite Existing Directories/Files
					std::cout << "No Options Selected\n" << std::endl;
					std::filesystem::copy(currentDirectory, newDirectoryName);
					std::cout << "Success\n" << std::endl;
				}
			}
			catch (std::filesystem::filesystem_error& error1) {
				std::cout << "Copy Failed with Error: " << error1.what() << std::endl;
			}
		}
	}
	void CopyDirectory(const bool relToCurrentDirectory, std::string currentPath, std::string newPath, const bool directoriesOnly, const bool overwriteExisting) const
	{ //Tested Working 3/30/24
		if (relToCurrentDirectory) {
			currentPath = pathBuilder(appDirectory, currentPath);
			newPath = pathBuilder(appDirectory, newPath);
		}
		if (exists(newPath) && !overwriteExisting) {
			std::cout << "Directory Already Exists\n" << std::endl;
		}
		else {
			try {
				if (directoriesOnly && overwriteExisting) { //Only copy directories and overwrite existing directories/files
					std::cout << "Directories Only & Overwrite Existing\n" << std::endl;
					constexpr std::filesystem::copy_options copyOptions = std::filesystem::copy_options::directories_only | std::filesystem::copy_options::overwrite_existing;
					std::filesystem::copy(currentPath, newPath, copyOptions);
					std::cout << "Success\n" << std::endl;
				}
				else if (directoriesOnly) { //Only copy directories, do not overwrite existing
					std::cout << "Directories Only\n" << std::endl;
					constexpr auto copyOptions = std::filesystem::copy_options::overwrite_existing;
					std::filesystem::copy(currentPath, newPath, copyOptions);
					std::cout << "Success\n" << std::endl;
				}
				else if (overwriteExisting) { //Copy directories & files, Overwrite Existing Directories/Files
					std::cout << "Overwrite Existing\n" << std::endl;
					constexpr auto copyOptions = std::filesystem::copy_options::overwrite_existing;
					std::filesystem::copy(currentPath, newPath, copyOptions);
					std::cout << "Success\n" << std::endl;
				}
				else { //Include Files & Do Not Overwrite Existing Directories/Files
					std::cout << "No Options Selected\n" << std::endl;
					std::filesystem::copy(currentPath, newPath);
					std::cout << "Success\n" << std::endl;
				}
			}
			catch (std::filesystem::filesystem_error& error1) {
				std::cout << "Copy Failed with Error: " << error1.what() << std::endl;
			}
		}
	}
	void CopyFile(const bool relToCurrentDirectory, std::string currentDirectory, const std::string& currentFileName, std::string newDirectory, const std::string& newFileName, const bool overwriteExisting) const { //Tested Working 3/30/24
		if (relToCurrentDirectory) {
			currentDirectory = pathBuilder(appDirectory, pathBuilder(currentDirectory, currentFileName));
			newDirectory = pathBuilder(appDirectory, pathBuilder(newDirectory, newFileName));
		}
		else {
			currentDirectory = pathBuilder(currentDirectory, currentFileName);
			newDirectory = pathBuilder(newDirectory, newFileName);
		}
		// secondaryPath = currentDirectory
		// path = newDirectory
		std::cout << currentDirectory << "\n" << newDirectory << std::endl;
		if (!exists(newDirectory)) {
			if (overwriteExisting) {
				constexpr auto copyOptions = std::filesystem::copy_options::overwrite_existing;
				std::filesystem::copy(currentDirectory, newDirectory, copyOptions);
			}
			else {
				std::filesystem::copy(currentDirectory, newDirectory);
			}
		}
		else {
			std::cout << "File Already Exists\n" << std::endl;
		}
	}
	void CopyFile(const bool relToCurrentDirectory, std::string currentPath, std::string newPath, const bool overwriteExisting) const { //Tested Working 3/30/24
		if (relToCurrentDirectory) {
			currentPath = pathBuilder(appDirectory, currentPath);
			newPath = pathBuilder(appDirectory, newPath);
		}
		std::cout << "Path Selected\n" << std::endl;
		std::cout << "Copy Path: " << currentPath << std::endl;
		std::cout << "Target Path: " << newPath << std::endl;
		if (!exists(newPath)) {
			if (overwriteExisting) {
				constexpr auto copyOptions = std::filesystem::copy_options::overwrite_existing;
				std::filesystem::copy(currentPath, newPath, copyOptions);
			}
			else {
				std::filesystem::copy(currentPath, newPath);
			}
			std::cout << "Success\n" << std::endl;
		}
		else {
			std::cout << "File Already Exists\n" << std::endl;
		}
	}
	
	//----------Move Operations -------------------------------------------
	//Tested Working 4/4/24
	//--------------------------------------------------------------------------------
	//Directory Moving
	void MoveDirectory(const bool relToCurrentDirectory, const std::string& currentDirectory, const std::string& currentDirectoryName, const std::string& newDirectory, const std::string& newDirectoryName, const bool overwriteExisting) const
	{
		CopyDirectory(relToCurrentDirectory, currentDirectory, currentDirectoryName, newDirectory, newDirectoryName, false, overwriteExisting);
		DeleteDirectory(relToCurrentDirectory, pathBuilder( currentDirectory, currentDirectoryName), true);
	}
	void MoveDirectory(const bool relToCurrentDirectory, const std::string& currentPath, const std::string& newPath, const bool overwriteExisting) const {
		CopyDirectory(relToCurrentDirectory, currentPath, newPath, false, overwriteExisting);
		DeleteDirectory(relToCurrentDirectory, currentPath, true);
	}
	//File Moving
	void MoveFile(const bool relToCurrentDirectory, const std::string& currentDirectory, const std::string& currentFileName, const std::string& newDirectory, const std::string& newFileName, const bool overwriteExisting) const
	{
		CopyFile(relToCurrentDirectory, currentDirectory, currentFileName, newDirectory, newFileName, overwriteExisting);
		DeleteFile(relToCurrentDirectory, currentDirectory, currentFileName);
	}
	void MoveFile(const bool relToCurrentDirectory, const std::string& currentPath, const std::string& newPath, const bool overwriteExisting) const
	{
		CopyFile(relToCurrentDirectory, currentPath, newPath, overwriteExisting);
		DeleteFile(relToCurrentDirectory, currentPath);
	}


	//----------Read Operations--------------------------------------------
	//Tested Working 3/28/24
	//Updated Working 3/30/24
	//--------------------------------------------------------------------------------
	std::string Read(const bool currentDirectory, const std::string& directory, const std::string& fileName) {
		return Read(currentDirectory, pathBuilder(directory, fileName));
	}
	std::string Read(const bool currentDirectory, const std::string& directory, const std::string& fileName, const int line) {
		return Read(currentDirectory, pathBuilder(directory, fileName), line);
	}
	std::string Read(const bool currentDirectory, std::string path) {
		if (currentDirectory) {
			path = pathBuilder(appDirectory, path);
		}
		file.open(path, static_cast<std::ios_base::openmode>(std::ios::in |std::ios::beg));

		if (file.is_open()) {			
			buffer << file.rdbuf();
			contents = buffer.str();
		}
		buffer.rdbuf()->str(EMPTY);
		std::cout << "START BUFFER {"<< buffer.str() << "} END BUFFER\n\n";
		std::cout << "START CONTENTS {" << contents << "} END CONTENTS\n\n";
		file.close();
		return contents;
	}
	std::string Read(const bool currentDirectory, std::string path, const int line) {
		if (currentDirectory) {
			path = pathBuilder(appDirectory, path);
		}
		file.open(path, static_cast<std::ios_base::openmode>(std::ios::in | std::ios::beg));

		for (int i = 0; i < line - 1; ++i) {
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		getline(file, contents);
		file.close();
		return contents;
	}

	//---------------------Write Operations---------------------------------
	//Tested Working 4/5/24
	//--------------------------------------------------------------------------------
	//Write All
	void Write(const bool currentDirectory, const bool overwriteExisting, std::string path, const std::string& inputContent) {
		if (currentDirectory) {
			path = pathBuilder(appDirectory, path);
		}
		//path = path
		if (!exists(path)) {
			Create(File, false, path);
		}
		file.open(path, static_cast<std::ios_base::openmode>(std::ios::out | std::ios::end));
		file << inputContent << std::endl;
		file.close();
	}
	void Write(const bool currentDirectory, const bool overwriteExisting, const std::string& directory, const std::string& fileName, const std::string& inputContent) {
		Write(currentDirectory, overwriteExisting, pathBuilder(directory, fileName), inputContent);
	}
	void Write_Mem(const bool currentDirectory, const bool overwriteExisting, std::string path, const std::string& inputContent, const int line) {
		//Set Directory
		if (currentDirectory) {
			path = pathBuilder(appDirectory, path);
		}
		//Creates file if it doesnt already exist
		if (!exists(path)) {
			Create(File, false, path);
		}
		//Open file in read/write mode at location 0
		file.open(path, static_cast<std::ios_base::openmode>(std::ios::in | std::ios::out |std::ios::beg));
		//If file successfully opened run edit line operations
		if (file.is_open()) {
			//Set up variables for operation
			contents = "";
			std::cout << "Current Contents: {" << contents << "} Size: {" << contents.size() << "} chars\n";
			currentLine = 1;
			std::cout << "--Getting Total Lines--\n";
			while (!file.eof()) {
				getline(file, sbuffer);
				std::cout << "Line # " << totalLines << ": " << sbuffer << std::endl;
				totalLines++;
			}
			std::cout << "--Total Current Lines: " << totalLines;
			std::cout << "\n\nRunning File Streaming\n\n";
			if (line > totalLines) {
				endLine = line;
			}
			else {
				endLine = totalLines;
			}

			//Reset location to 0
			file.seekg(0);

			//Take data in for each line and add it to the contents string that will get output into the target file
			while (currentLine < (endLine + 1)) {
				//If on a line that doesnt exist yet set to newline
				if (currentLine > totalLines) {
					std::cout << "Current Line:" << currentLine << "> Total Lines:" << totalLines << std::endl;
					sbuffer = "\n";
				}
				else {
					std::cout << "Operation: Passing Line + Input\n";
					getline(file, sbuffer);
				}
				
				std::cout << "Line #" << currentLine << " -----------------------------------------\nBuffer Contents: {" << sbuffer << "} Size: {" << sbuffer.size() << "} chars\n";

				//When the target line is reached determine what the line will be equal to
				if (currentLine == line) {
					std::cout << "Line Found" << currentLine << "=" << line << std::endl;
					if (overwriteExisting) {
						std::cout << "Input\n";
						if (currentLine != 1) {
							contents += "\n";
						}
						contents += inputContent;
					}
					else {
						std::cout << "Operation: Passing Line + Input\n";
						if (currentLine != 1) {
							contents += "\n";
						}
						if (currentLine <= totalLines) {
							contents += sbuffer;
						}
						contents += inputContent;
					}
				}
				//For all other lines use the existing value or newline
				else {
					std::cout << "Operation: Passing Line\n";
					if (currentLine > totalLines) {
						contents += "\n";
					} else {
						if (currentLine != 1) {
							contents += "\n";
						}
						contents += sbuffer;
					}					
				}
				std::cout << "New Contents: {" << contents << "} Size: {" << contents.size() << "} chars\n\n";
				//Increase line by 1
				currentLine++;
			}
			file.seekg(0);
			file << contents;
			file.close();

			contents = "";
			buffer.rdbuf()->str(EMPTY);
			totalLines = 0;
		}
		else {
			std::cout << "!!File Failed to Open!!\n\n\n";
		}
	}
	void Write(const bool currentDirectory, const bool overwriteExisting, std::string path, const std::string& inputContent, const int line) { //Not working properly, memory version is for reference
		//Set Directory
		if (currentDirectory) {
			path = pathBuilder(appDirectory, path);
		}		

		//Creates file if it doesnt already exist
		if (!exists(path)) {
			Create(File, false, path);
		}		

		//Open original in read/write mode at location 0
		readFile.open(path, static_cast<std::ios_base::openmode>(std::ios::in | std::ios::beg));
		
		
		if (readFile.is_open()) {
			std::cout << "\n\nBeginning Line Write Operation\n";
			//Set up variables for operation
			contents = "TEST";
			std::cout << "Current Contents: {\n" << contents << "\n} Size: {\n" << contents.size() << "\n} chars\n";
			readFile.seekg(0);
			buffer << readFile.rdbuf();
			contents = buffer.str();
			std::cout << "Current Contents: {\n" << contents << "\n} Size: {\n" << contents.size() << "\n} chars\n";

			currentLine = 1;
			std::cout << "-----START GATHERING ORIGINAL FILE DATA-----\n";
			readFile.seekg(0);
			std::cout << "Position Zero: " << readFile.tellg() << std::endl;
			while (!readFile.eof()) {
				std::cout << "Line # " << totalLines  << " | Start Char: " << readFile.tellg();
				readFile.ignore(0, '\n');
				getline(readFile, sbuffer);
				std::cout << " | End Char: " << readFile.tellg() << " | Contents: " << sbuffer << std::endl;
				totalLines++;
			}
			std::cout << "-----END GATHERING ORIGINAL FILE DATA-----\n";
			//Reset location to 0
			
			//Check if errors exist for console error displaying
			if (readFile.eof()) {
				std::cout << "ERROR: End Of File\n";
			} else if (readFile.fail()) {
				std::cout << "ERROR: End Of File\n";
			} else if (readFile.bad()) {
				std::cout << "ERROR: End Of File\n";
			}
			readFile.clear();
			try {
				readFile.seekg(0);
				if (readFile.eof()) {
					throw "ERROR: End Of File\n";
				}
				else if (readFile.fail()) {
					throw "ERROR: End Of File\n";
				}
				else if (readFile.bad()) {
					throw "ERROR: End Of File\n";
				}
			}
			catch (std::string thrownError) {
				std::cout << thrownError;
			}
			
			std::cout << "Position Zero: " << readFile.tellg();
			std::cout << "\nTotal Current Lines: " << totalLines;
			std::cout << "\n\nRunning readFile Streaming\n\n";
			if (line > totalLines) {
				endLine = line;
			} else {
				endLine = totalLines;
			}

			secondaryPath = path + ".tmp";

			std::cout << "Target Path: " + path + "\n";
			std::cout << "Copy Path: " + secondaryPath + "\n";
			if (!exists(secondaryPath)) {
				Create(File, false, secondaryPath);
			} else {
				std::cout << "ERROR: Temp file already exists, aborting operation\n";
				return;
			}
			std::cout << "Target Path: " + path + "\n";
			std::cout << "Copy Path: " + secondaryPath + "\n";

			//Open temp file in write mode at location 0
			temp.open(secondaryPath, static_cast<std::ios_base::openmode>(std::ios::out | std::ios::beg));
			//If original file and temp file are successfully opened, run operation - checks are run independantly for error reporting
			
			if (temp.is_open()) {	
				//Take data in for each line and add it to the contents string that will get output into the target file
				while (currentLine < (endLine + 1)) {
					//If on a line that doesnt exist yet set to newline
					if (currentLine > totalLines) {
						std::cout << "Operation: Setting Line Data to Blank";
						sbuffer = "\n";
					}
					else {
						std::cout << "Operation: Getting Line Data\n";
						getline(readFile, sbuffer);
					}

					std::cout << "Line #" << currentLine << " -----------------------------------------\nBuffer Contents: {" << sbuffer << "} Size: {" << sbuffer.size() << "} chars\n";
					//When the target line is reached determine what the line will be equal to
					if (currentLine == line) {
						std::cout << "Line Found: " << currentLine << "=" << line << std::endl;
						if (overwriteExisting) {
							std::cout << "Input\n";
							if (currentLine != 1) {
								temp << "\n";
							}
							temp << inputContent;
						}
						else {
							std::cout << "Operation: Passing Line + Input\n";
							if (currentLine != 1) {
								temp << "\n";
							}
							if (currentLine <= totalLines) {
								temp << sbuffer;
							}
							temp << inputContent;
						}
					}
					//For all other lines use the existing value or newline
					else {
						std::cout << "Operation: Passing Line\n";
						if (currentLine > totalLines) {
							temp << "\n";
						}
						else {
							if (currentLine != 1) {
								temp << "\n";
							}
							temp << sbuffer;
						}
					}
					//Increase line by 1
					currentLine++;
				}
				readFile.close();
				temp.close();

				buffer.rdbuf()->str(EMPTY);
				totalLines = 0;

				std::cout << "Target Path: " + path + "\n";
				std::cout << "Copy Path: " + secondaryPath + "\n";

				std::filesystem::remove(path);
				std::cout << "Original File Removed\n" << std::endl;

				std::filesystem::rename(secondaryPath, path);
				std::cout << "Temp File Renamed\n" << std::endl;
			}
			else {
				std::cout << "Temp File Failed To Open\n";
			}
			readFile.clear();
		}
		else {
			std::cout << "!!Original File Failed to Open!!\n\n\n";
		}
	}
	void Write(const bool currentDirectory, const bool overwriteExisting, const std::string& directory, const std::string& fileName, const std::string& inputContent, const int line) {
		Write(currentDirectory, overwriteExisting, pathBuilder(directory, fileName), inputContent, line);
	}

	//---------------------Additional Operations---------------------------
	//Tested Working 3/30/24
	//--------------------------------------------------------------------------------
	bool exists(const bool currentDirectory, std::string path) const
	{
		if (currentDirectory) {
			path = pathBuilder(appDirectory, path);
		}
		return std::filesystem::exists(path);
	}

	static bool exists(const std::string& path) {
		return std::filesystem::exists(path);
	}
	

	//Constructor/Destructor
	FILEMANAGEMENT() = default;
	~FILEMANAGEMENT() = default;
};