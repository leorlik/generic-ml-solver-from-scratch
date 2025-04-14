#include "LinearRegression.hpp"
#include "BaseRegression.hpp"
#include <iostream>
#include <cmath>
#include <cstdint>

LinearRegression::LinearRegression() : BaseRegression() {
}

LinearRegression::LinearRegression(const std::vector<std::vector<float>>& x, const std::vector<float>& y) : BaseRegression(x , y) {
}

std::vector<float> LinearRegression::predict(const std::vector<std::vector<float>>& x) const {
    
    std::vector<float> predictions(x.size(), 0.0f);

    for (size_t i = 0; i < x.size(); ++i) {
        for (size_t j = 0; j < x[i].size(); ++j) {
            predictions[i] += this->slope[j] * x[i][j];
        }
        predictions[i] += this->intercept;
    }

    return predictions;
}