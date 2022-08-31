#pragma once
#include <string>


class FILE_MANAGEMENT {
public:
	std::string date;

	void fileNew(std::string filename, std::string filetype, bool include_date);

};
