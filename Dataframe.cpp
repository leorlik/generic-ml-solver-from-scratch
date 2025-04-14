#include "Dataframe.hpp"
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <tuple>
#include <regex>

const bool Dataframe::isFloatRegex(const std::string& str) const{

    static const std::regex floatRegex(
        R"(^[+-]?(\d+(\.\d*)?|\.\d+)([eE][+-]?\d+)?$)"
    );

    return std::regex_match(str, floatRegex);
}


std::tuple<std::string, bool> Dataframe::_leAteSeparador(std::FILE * file, char delimiter){

	std::string retorno{""};
	bool is_end{false};
	int aux;
	char lastChar;

	aux = std::fgetc(file);

	while(aux != EOF){

		lastChar = static_cast<char>(aux);
		if(lastChar ==  delimiter)
			break;
		
		if(lastChar == '\n'){
			is_end = true;
			break;
		}

		retorno += lastChar;
		aux = std::fgetc(file);
	}

	if (!retorno.empty() && retorno.back() == '\r') {
		retorno.pop_back();
	}

	return std::make_tuple(retorno, is_end);

}

Dataframe::Dataframe(): lines{0}, columns{0}{};

Dataframe::Dataframe(const std::string fileName, const char delimiter): lines{0}, columns{0}{

	std::FILE * file{std::fopen( fileName.c_str(), "r" )};
	//Depois trocar para exception
	if(file == NULL){

		throw std::ios_base::failure("Erro ao abrir o arquivo: " + fileName);

	} 

	//Lendo cabeçalhos
	std::tuple<std::string, bool> helper{this->_leAteSeparador(file, delimiter)};
	std::string word{std::get<0>(helper)};
	bool is_end{std::get<1>(helper)};

	while( !( (word.empty()) | is_end ) ){

		this->colNames.push_back(word);
		//Alocando espaço para os nomes das colunas
		helper = this->_leAteSeparador(file, delimiter);
        word = std::get<0>(helper);
        is_end = std::get<1>(helper);
		this->columns++;
	};
	this->colNames.push_back(word);
	this->columns++;

	helper = this->_leAteSeparador(file, delimiter);
	word = std::get<0>(helper);

	//Lendo os valores
	while(!feof(file)){

		//Se o arquivo estiver vazio
		if(word.empty())
			break;

		//Alocando espaço para os valores
		//this->values.resize(this->lines + 1);
		this->values.push_back(std::vector<float>{});
		this->values[this->lines].resize(this->columns);
		//Alocando espaço para os valores

		for(uint32_t i = 0; i < this->columns; i++){

			if(isFloatRegex(word)){
				this->values[this->lines][i] = std::stof(word);
			} else {
				throw(std::invalid_argument("Erro ao converter o valor: " + word));
			}

			helper = this->_leAteSeparador(file, delimiter);
			word = std::get<0>(helper);
		};

		this->lines++;
		//std::cout << word << std::endl;
	}

	std::fclose(file);
	
}

std::vector<float> Dataframe::popColumn(const std::string colName){

	long index{-1};

	for(uint32_t i = 0; i < this->columns; i++){
		if(this->colNames[i] == colName){
			index = static_cast<long>(i);
			break;
		}
	}

	if((index == -1)| (index > static_cast<long>(this->columns))){
		throw(std::invalid_argument("Coluna não encontrada"));
	}

	std::vector<float> column(this->lines);

	for(uint32_t i = 0; i < this->lines; i++)
		column[i] = this->values[i][index];
	
	//Deletando os valores da coluna
	for(uint32_t i = 0; i < this->lines; i++)
		this->values[i].erase(this->values[i].begin() + index);

	//Deletando o nome da coluna
	this->colNames.erase(this->colNames.begin() + index);

	this->columns--;

	return column;

}

void Dataframe::head(const uint32_t num) const {

	std::cout << "Cabeçalho: " << std::endl;
	for(uint32_t i = 0; i < this->columns; i++){
		std::cout << this->colNames[i] << "|";
	}
	std::cout << std::endl;

	uint32_t num_cols{(num > this->lines) ? this->lines : num};

	std::cout << "Primeiras linhas: " << std::endl;

	for(uint32_t i = 0; i < num_cols; i++){

		for(uint32_t j = 0; j < this->columns; j++){
			std::cout << this->values[i][j] << "|";
		}
		
		std::cout << std::endl;
	}

}

void Dataframe::printColumnNames() const{

	std::cout << "Nomes das colunas: " << std::endl;
	for(uint32_t i = 0; i < this->columns; i++){
		std::cout << this->colNames[i] << "|";
	}
	std::cout << std::endl;

}

void Dataframe::getNumberOfLines(){

	std::cout << "Número de linhas: " << this->lines << std::endl;

}

void Dataframe::getNumberOfColumns(){

	std::cout << "Número de colunas: " << this->columns << std::endl;

}

const std::vector<std::vector<float>>& Dataframe::getData() const {

    return this->values;

}

std::vector<std::vector<float>> Dataframe::copyData() const{

	return this->values;

}

Dataframe::~Dataframe(){

	//Deletando os valores
	for(uint32_t i = 0; i < this->lines; i++)
		this->values[i].clear();

	//Deletando o cabeçalho
	this->colNames.clear();

	//Deletando os valores gerais
	this->values.clear();

}
