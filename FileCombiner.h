#pragma once
//FileCombiner:20130206
#include <iostream>
#include <string>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>  
#include <boost/format.hpp> 

namespace file_combiner
{
inline auto CombineFile(
		const boost::filesystem::path& directory_path, 
		std::vector<std::string> keyword_list,
		const boost::filesystem::path& dst_file_path) -> void {

	std::vector<boost::filesystem::path> file_path_list;

	//enumurate
	std::copy(boost::filesystem::directory_iterator(directory_path), 
		boost::filesystem::directory_iterator(),
		std::back_inserter(file_path_list));

	//remove
	const auto new_end_iter = 
		std::remove_if(file_path_list.begin(), file_path_list.end(),
			[&keyword_list](const boost::filesystem::path& file_path){
				for(const auto& keyword : keyword_list){
					if(!boost::contains(file_path.filename().string(), keyword)){
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
		std::ostream_iterator<boost::filesystem::path>(std::cout, ", "));
	std::cout << std::endl;

	boost::filesystem::ofstream ofs(dst_file_path);
	for(const auto& file_path : file_path_list){
		boost::filesystem::ifstream ifs(file_path);
		std::string line;
		while(ifs && getline(ifs, line)){
			ofs << file_path.filename().string() << " " << line << "\n";	
		}
		ofs << "\n";
	}
	return;
	
}

}

