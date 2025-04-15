#include "../../include/logic/Observation.h"

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

void Observation::write_csv(fs::__cxx11::directory_entry file)
{
	string str_is_solved = Is_Solved == true ? "TRUE" : "FALSE";
	string str_is_accepted = Is_Accepted == true ? "TRUE" : "FALSE";

	std::ofstream csv_file;
	csv_file.open(Path_csv, std::ios_base::app);
	csv_file << file.path().filename() << ","
		<< to_string(Number_Args_AF) << ","
		<< to_string(Number_Args_COI) << ","
		<< to_string(Number_Args_AF_reduced_by_GR) << ","
		<< to_string(Number_Args_AF_COI_reduced_by_GR) << ","
		<< to_string(Number_Args_GR_in_COI) << ","
		<< to_string(Number_Args_GR_only) << ","
		<< str_is_solved << ","
		<< str_is_accepted << endl;
	csv_file.close();
}