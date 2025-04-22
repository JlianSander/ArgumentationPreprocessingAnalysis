#include "../../include/logic/Processor.h"
using namespace std;

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

static string read_query(fs::directory_entry &file, string query_file_extension)
{
	fs::path query_file{ file.path() }, extension_query{ query_file_extension };
	query_file.replace_extension(query_file_extension);
	ifstream input;
	input.open(query_file);

	if (!input.good()) {
		cerr << "Cannot open query file at: " << query_file << endl;
		exit(1);
	}

	string line, query;

	getline(input, line);
	std::istringstream iss(line);
	iss >> query;

	return query;
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

void Processor::process_file(fs::directory_entry file, Observation &observation, string query_file_extension)
{
	// parse the framework
	AF framework;
	string file_format = file.path().extension();
	uint32_t query_argument;

	//parse framework and query argument
	switch (Enums::string_to_format(file_format)) {
	case I23:
		framework = Parser::parse_af_i23(file.path(), read_query(file, query_file_extension), query_argument);
		break;
	case TGF:
		framework = Parser::parse_af_tgf(file.path(), read_query(file, query_file_extension), query_argument);
		break;
	default:
		cerr << file_format << ": Unsupported file format\n";
		return;
	};
	if (query_argument == 0)
	{
		cout << "ERROR query argument could not be parsed in file: " << file.path() << endl;
		exit(1);
	}

	//count args of initial framework
	observation.Number_Args_AF = framework.num_args;

	//calculate cone of influence
	ConeOfInfluence coi = ConeOfInfluence(framework);
	ArrayBitSet activeArgs = PreProcessor::calculate_cone_influence(framework, query_argument, coi);
	observation.Number_Args_COI = activeArgs._array.size();

	//calculate grounded extension on original framework
	list<uint32_t> grounded_extension;
	ArrayBitSet originalAF = framework.create_active_arguments();
	ArrayBitSet reduct_only_gr;
	PreProcessor::reduce_by_grounded(framework, originalAF, query_argument, false, false, reduct_only_gr, grounded_extension);
	observation.Number_Args_AF_reduced_by_GR = reduct_only_gr._array.size();
	observation.Number_Args_GR_only = grounded_extension.size();

	//calculate grounded extension on framework reduced by cone of influence
	list<uint32_t> grounded_extension_after_coi;
	ArrayBitSet reduct_after_gr_coi;
	pre_proc_result result_after_gr_coi = PreProcessor::reduce_by_grounded(framework, activeArgs, query_argument, false, false, reduct_after_gr_coi, grounded_extension_after_coi);
	observation.Number_Args_AF_COI_reduced_by_GR = reduct_after_gr_coi._array.size();
	observation.Number_Args_GR_in_COI = grounded_extension_after_coi.size();
	observation.Is_Solved = result_after_gr_coi != pre_proc_result::unknown;
	observation.Is_Accepted = result_after_gr_coi == pre_proc_result::accepted;
}