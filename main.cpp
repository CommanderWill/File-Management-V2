#include <iostream>
#include "fileManagementV2.h"

int main() {
	std::cout << "Testing for File Management V2\n\n";
	FILEMANAGEMENT fm;
	/*
	std::cout << "--------------------File 1 Read All ---------------------------------\n";
	std::cout << fm.Read(true, "test.txt") << std::endl;
	std::cout << "-----------------------------------------------------------------------\n\n";

	std::cout << "\n\n---------------------------File 1 - Line 2 ------------------------\n";
	std::cout << fm.Read(true, "test.txt", 2) << std::endl;
	std::cout << "-----------------------------------------------------------------------\n\n";

	std::cout << "\n\n--------------------File 2 Read All ---------------------------------\n";
	std::cout << fm.Read(true, "testFolder", "file2.txt") << std::endl;
	std::cout << "-----------------------------------------------------------------------\n\n";

	std::cout << "\n\n---------------------------File 2 - Line 3 ------------------------\n";
	std::cout << fm.Read(true, "testFolder", "file2.txt", 3) << std::endl;
	std::cout << "-----------------------------------------------------------------------\n\n";

	std::cout << "\n\n--------------------File 1 Read All ---------------------------------\n";
	std::cout << fm.Read(true, "test.txt") << std::endl;
	std::cout << "-----------------------------------------------------------------------\n\n";
	*/
	// Testing Directory: D:\vs projects\file_management_v2\File Management V2\File Management V2\x64\Debug
	// "D:\\vs projects\\file_management_v2\\File Management V2\\File Management V2\\x64\\Debug"

	/*std::cout << "\n\nCreated NewFolder .\n";
	fm.Create(fm.Directory, true, "NewFolder");

	std::cout << "\n\nCreated NewFolder/NewFile.txt . .\n";
	fm.Create(fm.File, true, "NewFolder", "NewFile1.txt");

	std::cout << "\n\nCopying testFolder . . .\n";
	fm.CopyDirectory(true, "testFolder", "testFolder (2)", false, true);
	std::cout << "\n\nCopying testFolder take 2 . . .\n";
	fm.CopyDirectory(false, "D:\\vs projects\\file_management_v2\\File Management V2\\File Management V2\\x64\\Debug", "testFolder", "D:\\vs projects\\file_management_v2\\File Management V2\\File Management V2\\x64\\Debug",  "testFolder (3)", false, true);

	std::cout << "\n\nCopying NewFile1.txt . . . .\n";
	fm.CopyFile(true, "NewFolder", "NewFile1.txt", "testFolder", "NewFile2.txt", false);
	fm.CopyFile(false, "D:\\vs projects\\file_management_v2\\File Management V2\\File Management V2\\x64\\Debug\\NewFolder\\NewFile1.txt", "D:\\vs projects\\file_management_v2\\File Management V2\\File Management V2\\x64\\Debug\\testFolder\\NewFile2 (2).txt", false);

	std::cout << "\n\nDeleted NewFolder . . . . .\n";
	fm.DeleteDirectory(true, "NewFolder", true);
	fm.DeleteDirectory(true, "D:\\vs projects\\file_management_v2\\File Management V2\\File Management V2\\x64\\Debug\\actuallyDeleteThis", false);

	std::cout << "\n\nDeleted deleteThis2 . . . . . .\n";
	fm.DeleteFile(true, "deleteThis\\deleteThis2.txt");
	fm.DeleteFile(false, "D:\\vs projects\\file_management_v2\\File Management V2\\File Management V2\\x64\\Debug\\deleteThis\\deleteThis3.txt");

	std::cout << "\n\nMoving Shit Pt 1. . . . . . .\n";
	fm.MoveDirectory(true, "startDirectory", "moveThisFolder", "endDirectory", "movedThisFolder", true);
	std::cout << "\n\nMoving Shit Pt 2. . . . . . .\n";
	fm.MoveDirectory(false, "D:\\vs projects\\file_management_v2\\File Management V2\\File Management V2\\x64\\Debug\\startDirectory", "D:\\vs projects\\file_management_v2\\File Management V2\\File Management V2\\x64\\Debug\\endDirectory\\startDirectory", true);
	std::cout << "\n\nMoving Shit Pt 3. . . . . . .\n";
	fm.MoveFile(true, "startDirectory2", "moveThis1.txt", "endDirectory", "movedThis1.txt",false);
	std::cout << "\n\nMoving Shit Pt 4. . . . . . .\n";
	fm.MoveFile(false, "D:\\vs projects\\file_management_v2\\File Management V2\\File Management V2\\x64\\Debug\\startDirectory2\\moveThis2.txt", "D:\\vs projects\\file_management_v2\\File Management V2\\File Management V2\\x64\\Debug\\endDirectory2\\moveThis2.txt", false);
	std::cout << "\n\nMoving Shit Pt 5. . . . . . .\n";
	fm.MoveFile(false, "D:\\vs projects\\file_management_v2\\File Management V2\\File Management V2\\x64\\Debug\\startDirectory2\\moveThis3.txt", "D:\\vs projects\\file_management_v2\\File Management V2\\File Management V2\\x64\\Debug\\endDirectory2\\moveThis2.txt", true);*/

	//Result of 3/30/24 Testing
	// 1. Copy directory:
	//     a) needs overwrite capability added--
	//     b) needs to check if both copied path exists (AND when target path exists that overwrite is on or it doesnt copy)--
	//     b) needs error catching & fallouts
	// 2. Should plan logic for future functions before adding them

	//Result of 4/4/24 Testing
	// 1.Copy Directory: All Issues Resolved
	// 2. Ready to plan write functions



	int line;
	std::string message;
	bool appActive = true;

	fm.DeleteFile(true, "fillLine2.txt");
	fm.Create(FILEMANAGEMENT::File, true, "fillLine2.txt");
	fm.Write(FILEMANAGEMENT::File, true, "fillLine2.txt", "Line 1\nLine 2\nLine 3\nLine 4\nLine 5");

	while (appActive) {
		//Write line 2 on existing
		std::cout << "Read existing file:\n";
		fm.Read(true, "fillLine2.txt");

		std::cout << "\n\nRead existing file 2:\n";
		fm.Read(true, "fillLine2.txt");


		std::cout << "Select Line to Write To: ";
		std::cin >> line;
		std::cout << "Type Message to Write:\n";
		std::cin.ignore();
		getline(std::cin, message);

		std::cout << "\n\nRewriting line 2 on existing file\n";
		fm.Write(true, true, "fillLine2.txt", message, line);

		std::cout << "\n\nUpdated File Contents:\n";
		fm.Read(true, "fillLine2.txt");


		std::cout << "Select An Option:\n1. Repeat\n0. End\n";
		std::cin >> appActive;
	}
	

	//ReWrite Line 3 on existing file
	//std::cout << "Rewriting line 3 on existing file\n";
	//fm.Write(true, true, "fillLine2.txt", "Line 3 ReWrite Success", 3);

	char hold;
	std::cin >> hold;

	return 0;
}