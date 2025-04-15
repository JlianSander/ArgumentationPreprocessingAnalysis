#ifndef OBSV_H
#define OBSV_H

#include <iostream>
#include <fstream>

#include "../util/FileSystemInclude.h"

using namespace std;

class Observation {
public:
	int Number_Args_AF;
	int Number_Args_AF_reduced_by_GR;
	int Number_Args_AF_COI_reduced_by_GR;
	int Number_Args_COI;
	int Number_Args_GR_in_COI;
	int Number_Args_GR_only;
	bool Is_Solved;
	bool Is_Accepted;

	string Path_csv;

	Observation(string path_csv) {
		Number_Args_AF = -1;
		Number_Args_AF_reduced_by_GR = -1;
		Number_Args_AF_COI_reduced_by_GR = -1;
		Number_Args_COI = -1;
		Number_Args_GR_in_COI = -1;
		Number_Args_GR_only = -1;
		Is_Solved = false;
		Is_Accepted = false;
		Path_csv = path_csv;

		//prepare csv-file
		std::ofstream csv_file;
		csv_file.open(Path_csv);
		csv_file << "File, Number_Args_AF, Number_Args_in_COI, Number_Args_AF_Reduced_By_GR, Number_Args_in_COI_reduced_by_GR, Number_Args_GR_of_COI, Number_Args_GR_of_AF, Is_Solved, Is_Accepted" << endl;
		csv_file.close();
	}

	void write_csv(fs::directory_entry file);
};
#endif