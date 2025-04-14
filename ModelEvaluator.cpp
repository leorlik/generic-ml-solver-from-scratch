#include "ModelEvaluator.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>

ModelEvaluator::ModelEvaluator(const std::vector<float>& y_true, const std::vector<float>& y_pred)
    : y_true(y_true), y_pred(y_pred) {}


float ModelEvaluator::accuracy() const {

    float correct{0};
    for (size_t i{0}; i < y_true.size(); i++)
        if (y_true[i] == y_pred[i])
            correct = correct + 1;

    return correct / y_true.size();

}

float ModelEvaluator::precision() const {

    float tp{0};
    float fp{0};

    for (size_t i{0}; i < y_true.size(); i++) {

        float yt{y_true[i]};
        float yp{y_pred[i]};

        if (yp == 1) {
            if (yt == 1) 
                tp = tp + 1;
            else 
                fp = fp + 1;
        }

    }

    if(! (tp + fp)) {
        return 0.0f;
    }

    return tp / (tp + fp);

}

float ModelEvaluator::recall() const {

    float tp{0};
    float fn{0};

    for (size_t i = 0; i < y_true.size(); i++) {

        float yt{y_true[i]};
        float yp{y_pred[i]};

        if (yt == 1) {
            if (yp == 1) 
                tp++;
            else 
                fn++;
        }

    }

    if (!( tp + fn)) {
        return 0.0f;
    }

    return tp / (tp + fn);

}

float ModelEvaluator::f1() const {

    float p{precision()};
    float r{recall()};

    if(!(p + r)) {
        return 0.0f;
    }

    return 2 * (p * r) / (p + r);
}


float ModelEvaluator::mae() const {

    float error{0.0f};

    for (size_t i{0}; i < y_true.size(); i++)
        error += std::abs(y_true[i] - y_pred[i]);

    return error / y_true.size();

}

float ModelEvaluator::mse() const {

    float error{0.0f};

    for (size_t i{0}; i < y_true.size(); i++)
        error += std::pow(y_true[i] - y_pred[i], 2);

    return error / y_true.size();
}

float ModelEvaluator::rmse() const {

    return std::sqrt(mse());

}

float ModelEvaluator::mape() const {
    
    float error{0.0f};

    for (size_t i{0}; i < y_true.size(); i++)
        if (y_true[i] != 0)
            error += std::abs((y_true[i] - y_pred[i]) / y_true[i]);

    return error / y_true.size();

}

// Evaluations
void ModelEvaluator::evaluateClassification() const {

    std::cout << "Accuracy: " << accuracy() << std::endl;
    std::cout << "Precision: " << precision() << std::endl;
    std::cout << "Recall: " << recall() << std::endl;
    std::cout << "F1 Score: " << f1() << std::endl;

}

void ModelEvaluator::evaluateRegression() const {

    std::cout << "MAE: " << mae() << std::endl;
    std::cout << "MSE: " << mse() << std::endl;
    std::cout << "RMSE: " << rmse() << std::endl;
    std::cout << "MAPE: " << mape() << std::endl;

}
