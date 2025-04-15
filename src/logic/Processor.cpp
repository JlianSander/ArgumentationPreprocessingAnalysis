#include "../../include/logic/Processor.h"
using namespace std;

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

static uint32_t read_query(fs::directory_entry &file, string query_file_extension)
{
	fs::path query_file{ file.path() }, extension_query{ query_file_extension };
	query_file.replace_extension("af.arg");
	ifstream input;
	input.open(query_file);

	if (!input.good()) {
		cerr << "Cannot open query file\n";
		exit(1);
	}

	string line, query;

	getline(input, line);
	std::istringstream iss(line);
	iss >> query;

	return std::stoi(query);
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

void Processor::process_file(fs::directory_entry file, Observation &observation, string query_file_extension)
{
	// parse the framework
	AF framework;
	string file_format = file.path().extension();

	switch (Enums::string_to_format(file_format)) {
	case I23:
		framework = Parser::parse_af_i23(file.path());
		break;
	case TGF:
		framework = Parser::parse_af_tgf(file.path());
		break;
	default:
		cerr << file_format << ": Unsupported file format\n";
	};

	//read query argument
	uint32_t query_argument = read_query(file, query_file_extension);

	//count args of initial framework
}