#include "LogisticRegression.hpp"
#include "BaseRegression.hpp"  

#include <cmath>
#include <cstdint>
#include <vector>

LogisticRegression::LogisticRegression() : BaseRegression() {
}

LogisticRegression::LogisticRegression(const std::vector<std::vector<float>>& x, const std::vector<float>& y) : BaseRegression(x, y) {
}

float LogisticRegression::sigmoid(float z) {

    return 1.0f / (1.0f + std::exp(-1 * z));

}

std::vector<float> LogisticRegression::predict_proba(const std::vector<std::vector<float>>& x) const {

    std::vector<float> predictions(x.size(), 0.0f);

    for (size_t i{0}; i < x.size(); ++i) {
        float z = this->intercept;
        for (size_t j = 0; j < x[i].size(); ++j) {
            z += this->slope[j] * x[i][j];
        }
        predictions[i] = this->sigmoid(z);
    }

    return predictions;
}

std::vector<float> LogisticRegression::predict(const std::vector<std::vector<float>>& x) const {

    std::vector<float> predictions(x.size(), 0.0f);

    predictions = this->predict_proba(x);
    for (size_t i{0}; i < predictions.size(); ++i) {

        if(predictions[i] >= 0.5f) {
            predictions[i] = 1.0f;
        } else {
            predictions[i] = 0.0f;
        }
    }

    return predictions;

}
