#include "../include/Main.h"

using namespace std;

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

void static print_usage()
{
	cout << "Usage: " << PROGRAM_NAME << " -d <directory> -q <query-file-extension> -c <csv-file> \n\n";
	cout << "  <directory>    container of  argumentation frameworks\n";
	cout << "Options:\n";
	cout << "  --help      Displays this help message.\n";
	cout << "  --version   Prints version and author information.\n";
	cout << "  --formats   Prints available file formats.\n";
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

void static print_version()
{
	cout << PROGRAM_NAME << " (version "<< VERSIONNUMBER <<")\n"
		<< "Lars Bengel, University of Hagen <lars.bengel@fernuni-hagen.de>\n" 
		<< "Julian Sander, University of Hagen <julian.sander@fernuni-hagen.de>\n"
		<< "Matthias Thimm, University of Hagen <matthias.thimm@fernuni-hagen.de>\n";
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

void static print_formats()
{
	cout << "[i23, tgf]" << endl;
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

int main(int argc, char **argv)
{
	// read command arguments
	if (argc == 1) {
		print_version();
		return 0;
	}

	int option_index = 0;
	int opt = 0;
	string dir, csv_file_path, query_file_extension;

	while ((opt = getopt_long_only(argc, argv, "", longopts, &option_index)) != -1) {
		switch (opt) {
		case 0:
			break;
		case 'd':
			dir = optarg;
			break;
		case 'c':
			csv_file_path = optarg;
			break;
		case 'q':
			query_file_extension = optarg;
			break;
		default:
			return 1;
		}
	}

	if (version_flag) {
		print_version();
		return 0;
	}

	if (usage_flag) {
		print_usage();
		return 0;
	}

	if (formats_flag) {
		print_formats();
		return 0;
	}

	if (dir.empty()) {
		cerr << argv[0] << ": Input directory must be specified via -d flag\n";
		return 1;
	}

	if (csv_file_path.empty()) {
		csv_file_path = std::string(".") + fs::path::preferred_separator + std::string("Data_Tmp.csv");
	}

	cout << "Process files in " << dir << endl;
	cout << "Save results in " << csv_file_path << endl;

	//object to store and process observations
	Observation obsv = Observation(csv_file_path);

	//prepare iterating through directory
	typedef vector<fs::directory_entry> vec;
	vec v;

	copy(fs::directory_iterator(dir), fs::directory_iterator(), back_inserter(v));
	sort(v.begin(), v.end());				// sort, since directory iteration is not ordered on some file systems

	//iterate through files
	for (vec::const_iterator it(v.begin()), it_end(v.end()); it != it_end; ++it)
	{
		Processor::process_file(*it, obsv, query_file_extension);
		obsv.write_csv(*it);
	}

	return 0;
}