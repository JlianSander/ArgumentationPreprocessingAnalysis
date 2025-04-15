#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "../util/FileSystemInclude.h"

#include "Observation.h"
#include "Parser.h"
#include "PreProcessor.h"

using namespace std;

class Processor {

public:
	static void process_file(fs::directory_entry file, Observation &observation, string query_file_extension);
};
#endif