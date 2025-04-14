#include "BaseRegression.hpp"
#include <iostream>
#include <cmath>
#include <cstdint>
#include <vector>

BaseRegression::BaseRegression(){
}

BaseRegression::BaseRegression(const std::vector<std::vector<float>>& x, const std::vector<float>& y) {
    this->fit(x, y);
}



std::vector<std::vector<float>> BaseRegression::transpose(const std::vector<std::vector<float>>& matrix) {
    
    if (matrix.empty()) 
        return {};

    size_t rows{matrix.size()};
    size_t cols{matrix[0].size()};

    std::vector<std::vector<float>> result(cols, std::vector<float>(rows));

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            result[j][i] = matrix[i][j];

    return result;
}

float BaseRegression::calculateMean(const std::vector<float>& data) {

    float sum{0.0f};
    for (const auto& value : data) {
        sum += value;
    }
    return sum / data.size();

}

float BaseRegression::calculateSlope(const std::vector<float>& x, const std::vector<float>& y) {

    float x_mean{this->calculateMean(x)};
    float y_mean{this->calculateMean(y)};

    float numerator{0.0f};
    float denominator{0.0f};

    for (size_t i = 0; i < x.size(); ++i) {
        numerator += (x[i] - x_mean) * (y[i] - y_mean);
        denominator += (x[i] - x_mean) * (x[i] - x_mean);
    }

    float slope {numerator / denominator};

    return slope;

}

void BaseRegression::fit(const std::vector<std::vector<float>>& x, const std::vector<float>& y){

    size_t num_features{x[0].size()};

    this->slope.resize(num_features);
    this->intercept = 0.0f;

    auto x_T = transpose(x);

    for(size_t i = 0; i < num_features; i++){
        this->slope[i] = calculateSlope(x_T[i], y);
        this->intercept += this->slope[i] * this->calculateMean(x_T[i]);
    }

    this->intercept = this->calculateMean(y) - this->intercept;
}

std::vector<float> BaseRegression::getSlope() const {
    return this->slope;
}

float BaseRegression::getIntercept() const {
    return this->intercept;
}

void BaseRegression::print() const {
    std::cout << "Slope: ";
    for (const auto& s : this->slope) {
        std::cout << s << " ";
    }
    std::cout << "\nIntercept: " << this->intercept << std::endl;
}
