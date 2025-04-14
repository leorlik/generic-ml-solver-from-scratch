#ifndef DATAFRAME_HPP
#define DATAFRAME_HPP

#include <string>
#include <fstream>
#include <cstdint>
#include <vector>
#include <tuple>

class Dataframe{
	
	public:

		Dataframe();
		Dataframe(std::string fileName, const char delimiter = ';');
		void head(uint32_t num = DEFAULT_NUM_HEAD_LINES) const;
		void printColumnNames() const;
		std::vector<float> popColumn(const std::string colName);

		std::tuple<std::string, bool> _leAteSeparador(std::FILE * file, char delimiter);
		
		void getNumberOfLines();
		void getNumberOfColumns();
		
		const std::vector<std::vector<float>>& getData() const;
		std::vector<std::vector<float>> copyData() const;


		~Dataframe();

	private:

		std::vector<std::string> colNames;
		std::vector<std::vector<float>> values;
		uint32_t lines;
		uint32_t columns;
		static constexpr uint32_t DEFAULT_NUM_HEAD_LINES{5};
		const bool isFloatRegex(const std::string& str) const;

};

#endif
