#include "Dataframe.cpp"

Dataframe::Dataframe(const std::string fileName, char delimiter){


	std::FILE * file = std::fopen( fileName.c_str(), "r" );


};

std::string _leAteSeparador(std::FILE * file, char delimiter){

	std::string retorno;
	int aux;
	char lastChar;

	aux = std::fgetc(file);

	while(aux != EOF){

		lastChar = static_cast<char>(aux);
		if(lastChar ==  delimiter || lastChar == '\n')
			break;

		retorno += lastChar;
		aux = std::fgetc(file);
	}

	return retorno;

};
