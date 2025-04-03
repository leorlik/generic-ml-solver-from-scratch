#ifndef DATAFRAME_HPP
#define DATAFRAME_HPP

#include <string>
#include <fstream>

class Dataframe{
	public:
		Dataframe(std::string fileName, char delimiter);
		const void head() const;
		float * popColumn();

	private:
		std:: string_leAteSeparador(std::FILE * file, char delimiter);

		std::string * colNames;
		float ** values;
		int lines;
		int columns;

};

#endif
