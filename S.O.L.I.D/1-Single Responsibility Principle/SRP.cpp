#include<iostream>
#include<vector>
#include<string>
#include<fstream>

struct journal {
	std::string title;
	std::vector<std::string> entries;

	explicit journal(const std::string& title):title{title}{
	}

	void add(const std::string& entry){
		entries.push_back(entry);
	}

    /*
	void save(const std::string& filename){
		std::ofstream ofs(filename);
		for(auto& e:entries)
			ofs << e << std::endl;
	}
	*/
};

//A class should only have a single responsibility
//best approch :
struct PersistenceManager{
	static void save(const journal& j, const std::string& filename){
		std::ofstream ofs(filename);
		for(auto& e:j.entries)
			ofs << e << std::endl;
    }
};
