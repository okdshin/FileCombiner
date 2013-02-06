#ifdef FILECOMBINER_UNIT_TEST
#include "FileCombiner.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>  
#include <boost/format.hpp> 

using namespace file_combinator;
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

	//enumurate
	std::copy(directory_iterator(directory_path), directory_iterator(),
		std::back_inserter(file_path_list));

	//remove
	const auto new_end_iter = 
		std::remove_if(file_path_list.begin(), file_path_list.end(),
			[&keyword_list](const path& file_path){
				for(const auto& keyword : keyword_list){
					if(!boost::contains(file_path.string(), keyword)){
						return true;
					}
				}
				return false;
			}
		);
	file_path_list.erase(new_end_iter, file_path_list.end());
	
	//sort
	std::sort(file_path_list.begin(), file_path_list.end());

	std::copy(file_path_list.begin(), file_path_list.end(), 
		std::ostream_iterator<path>(std::cout, ", "));
	std::cout << std::endl;

	std::ofstream ofs(argv[2]);
	for(const auto& file_path : file_path_list){
		boost::filesystem::ifstream ifs(file_path);
		std::string line;
		while(ifs && getline(ifs, line)){
			ofs << line << "\n";	
		}
		ofs << "\n";
	}
	std::cout << argv[2] << " is generated." << std::endl;
	return 0;
}

#endif
