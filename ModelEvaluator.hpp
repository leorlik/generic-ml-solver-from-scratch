#ifndef MODEL_EVALUATOR_HPP
#define MODEL_EVALUATOR_HPP

#include <vector>
#include <string>

class ModelEvaluator {

public:
    ModelEvaluator(const std::vector<float>& y_true, const std::vector<float>& y_pred);

    // Metricas classificacao
    float accuracy() const;
    float precision() const;
    float recall() const;
    float f1() const;

    // Metricas regressao
    float mae() const;
    float mse() const;
    float rmse() const;
    float mape() const;

    // Evaluators
    void evaluateClassification() const;
    void evaluateRegression() const;

private:
    std::vector<float> y_true;
    std::vector<float> y_pred;
};

#endif
