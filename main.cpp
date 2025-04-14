#include "Dataframe.hpp"
#include "LogisticRegression.hpp"
#include "LinearRegression.hpp"
#include "CommandLineArgs.hpp"
#include "ModelEvaluator.hpp"
#include <iostream>
#include <tuple>
#include <memory>

int main(int argc, char ** argv){

    CommandLineArgs args(argc, argv);

    if(args.has("help")) {
        std::cout << "Usage: " << argv[0] << " [--dataset=<filename>] [--delimiter=<delimiter>] [--problem=<1, 2>] [--target_column=<target_column>]" << std::endl;
        return 0;
    }

    std::vector<std::string> essentialArguments{"dataset", "problem", "target_column"};

    for (size_t i{0}; i < essentialArguments.size(); i++) {
        std::string arg{essentialArguments[i]};
        if (!args.has(arg)) {
            std::cerr << "Error: Missing required argument --" << arg << std::endl;
            return 1;
        }
    }

    //Pegando o problema
    int problem{args.getInt("problem")};
    if (problem != 1 && problem != 2) {
        std::cerr << "Error: Invalid problem type. Use 1 for classification or 2 for regression." << std::endl;
        return 1;
    }

    //Pegando o nome do arquivo
    std::string fileName{args.getString("dataset")};

    //Pegando a target column
    std::string targetColumn{args.getString("target_column")};
    if (targetColumn.empty()) {
        std::cerr << "Error: Missing target column." << std::endl;
        return 1;
    }

    //Pegando o delimitador
    char delimiter{args.getChar("delimiter", ',')};
    if (delimiter == '\0') {
        std::cerr << "Error: Invalid delimiter." << std::endl;
        return 1;
    }

    std::unique_ptr<Dataframe> df;

    try {
        df = std::make_unique<Dataframe>(fileName, delimiter);
    } catch (const std::ios_base::failure& e) {
        std::cerr << "[File Error] " << e.what() << std::endl;
        return 1;
    } catch (const std::invalid_argument& e) {
        std::cerr << "[Parsing Error] " << e.what() << std::endl;
        return 1;
    }

    //Pegando o target column
    std::vector<float> y;

    try{
        y = df->popColumn(targetColumn);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    BaseRegression * model{nullptr};

    if (problem == 1) {
        model = new LogisticRegression(df->getData(), y);
    } else if (problem == 2) {
        model = new LinearRegression(df->getData(), y);
    } else {
        std::cerr << "Error: Invalid problem type." << std::endl;
        return 1;
    }

    if (model == nullptr) {
        std::cerr << "Error: Failed to create model." << std::endl;
        return 1;
    }

    model->print();

    std::vector <float> y_pred{model->predict(df->getData())};
    // std::cout << "Predictions: " << std::endl;
    // int i{0};
    // for (const auto& value : predictions) {
    //     std::cout << i << ": " << value << std::endl;
    //     i++;
    // }

    ModelEvaluator evaluator{y, y_pred};

    if(problem == 1) {
        evaluator.evaluateClassification();
    } 
    else if (problem == 2) {
        evaluator.evaluateRegression();
    }
    else {
        std::cerr << "Error: Invalid problem type." << std::endl;
        return 1;
    }

    delete model;
    model = nullptr;

    return 0;
    

}