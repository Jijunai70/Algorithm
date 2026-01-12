//
// Created by w00896870 on 2026/1/9.
//

#include "AdaBoosting.h"

AdaBoosting::AdaBoosting(const std::vector<std::pair<int, int>> &samples)
{
    float rate = 1.0f / samples.size();
    for (auto sample : samples) {
        this->samples.push_back({sample.first, sample.second, rate});
    }
}

bool AdaBoosting::Run()
{
    while (!JudgeFinish()) {
        // 1. 得到err
        ClassifierInfo classifierInfo = GetClassifierInfo();

        // 2. 更新样本权重
        float rate = (1 - classifierInfo.errRate) / classifierInfo.errRate;
        UpdateSamplesRate(rate);

        // 3. 添加弱分类器，若err为0或1则退出
        if (classifierInfo.errSampleNum == samples.size()) {
            return false;
        }

        if (classifierInfo.errSampleNum == 0) {
            classifier.clear();
            classifier.push_back(classifierInfo);
            return true;
        }

        classifier.push_back(classifierInfo);
    }
    return true;
}

ClassifierInfo AdaBoosting::GetClassifierInfo()
{

    return {};
}

bool AdaBoosting::JudgeFinish()
{
    if (classifier.empty()) {
        return false;
    }

    for (auto &sample : samples) {
        float sum = 0;
        for (auto &classifierInfo : classifier) {
            if ((sample.x >= classifierInfo.x) ^ (sample.type == 1)) {

            }
        }
    }
    return true;
}

void AdaBoosting::UpdateSamplesRate(float errRate)
{
    for (auto &sample : samples) {

    }
}
