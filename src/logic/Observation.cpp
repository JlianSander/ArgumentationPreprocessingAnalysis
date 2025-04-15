#include "../../include/logic/Observation.h"

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

void Observation::write_csv(fs::__cxx11::directory_entry file)
{
	std::ofstream csv_file;
	csv_file.open(Path_csv, std::ios_base::app);
	csv_file << file.path().filename() << ","
		<< to_string(Number_Args_AF) << ","
		<< to_string(Number_Args_AF_no_COI) << ","
		<< to_string(Number_Args_AF_no_GR) << ","
		<< to_string(Number_Args_AF_no_COI_GR) << ","
		<< to_string(Number_Args_COI) << ","
		<< to_string(Number_Args_GR) << ","
		<< to_string(Is_Solved) << ","
		<< to_string(Is_Accepted) << "\n";
	csv_file.close();
}