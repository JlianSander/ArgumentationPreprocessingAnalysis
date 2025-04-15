#ifndef OBSV_H
#define OBSV_H

#include <iostream>
#include <fstream>

#include "../util/FileSystemInclude.h"

using namespace std;

class Observation {
public:
	int Number_Args_AF;
	int Number_Args_AF_no_COI;
	int Number_Args_AF_no_COI_GR;
	int Number_Args_AF_no_GR;
	int Number_Args_COI;
	int Number_Args_GR;
	bool Is_Solved;
	bool Is_Accepted;

	string Path_csv;

	Observation(string path_csv) {
		Number_Args_AF = -1;
		Number_Args_AF_no_COI = -1;
		Number_Args_AF_no_COI_GR = -1;
		Number_Args_AF_no_GR = -1;
		Number_Args_COI = -1;
		Number_Args_GR = -1;
		Is_Solved = false;
		Is_Accepted = false;
		Path_csv = path_csv;

		//prepare csv-file
		std::ofstream csv_file;
		csv_file.open(Path_csv);
		csv_file << "File, Number_Args_AF, Number_Args_AF_No_COI, Number_Args_AF_No_GR, Number_Args_AF_No_COI_GR, Number_Args_COI, Number_Args_GR, Is_Solved, Is_Accepted,\n";
		csv_file.close();
	}

	void write_csv(fs::directory_entry file);
};
#endif