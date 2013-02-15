#ifdef FILECOMBINER_UNIT_TEST
#include "FileCombiner.h"
#include <iostream>

using namespace file_combiner;
using namespace boost::filesystem;
int main(int argc, char* argv[])
{
	if(argc < 2){
		std::cout << boost::format(
			"This program combines files which have same keywords in their names with a line interval.\nUsage:\n\t%1% <directory_path> <save_file_path> [<keyword1> <keyword2> ...]")
				% path(argv[0]).filename().string()
		<< std::endl;
		return 0;
	}
	path directory_path(argv[1]);
	if(!exists(directory_path)){
		std::cout << directory_path << " does not exist." << std::endl;
		return 0;
	}
	if(!is_directory(directory_path)){
		std::cout << directory_path << " is not directory." << std::endl;
		return 0;	
	}
	std::vector<path> file_path_list;

	std::vector<std::string> keyword_list;
	for(int i = 3; i < argc; ++i){
		keyword_list.push_back(std::string(argv[i]));
	}

	CombineFile(directory_path, keyword_list, boost::filesystem::path(argv[2]));

	return 0;
}

#endif
