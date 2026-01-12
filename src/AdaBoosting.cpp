//
// Created by w00896870 on 2026/1/9.
//

#include <complex>
#include "AdaBoosting.h"

AdaBoosting::AdaBoosting(const std::vector<std::pair<int, int>> &samples)
{
    float rate = 1.0f / samples.size();
    for (auto sample : samples) {
        this->m_samples.push_back({sample.first, sample.second, rate});
    }
    OutputSamplesRate();
}

bool AdaBoosting::Run()
{
    while (!JudgeFinish()) {
        // 1. 得到err
        ClassifierInfo classifierInfo = GetClassifierInfo();

        if (classifierInfo.errSampleNum == 0) {
            m_classifier.clear();
            m_classifier.push_back(classifierInfo);
            return true;
        }

        // 2. 添加弱分类器，若err为0或1则退出
        m_classifier.push_back(classifierInfo);
        Output();

        // 3. 更新样本权重
        float rate = (1 - classifierInfo.errRate) / classifierInfo.errRate;
        rate = std::sqrt(rate);
        UpdateSamplesRate(rate);
        OutputSamplesRate();
    }
    return true;
}

ClassifierInfo AdaBoosting::GetClassifierInfo()
{
    ClassifierInfo classifierInfo = {};
    classifierInfo.errRate = 0;
    classifierInfo.errSampleNum = m_samples.size();

    int errSampleNum = 0;
    float errRate = 0;
    int transErrSampleNum = 0;
    float transErrRate = 0;
    for (auto &sample : m_samples) {
        if (sample.type != 1) {
            errSampleNum++;
            errRate += sample.weight;
        } else {
            transErrSampleNum++;
            transErrRate += sample.weight;
        }
    }

    if (errRate < transErrRate) {
        classifierInfo.errSampleNum = errSampleNum;
        classifierInfo.errRate = errRate;
    } else {
        classifierInfo.errSampleNum = transErrSampleNum;
        classifierInfo.errRate = transErrRate;
    }
    classifierInfo.x = m_samples[0].x;


    for (int i = 0; i < m_samples.size(); i++) {
        if (m_samples[i].type == 1) {
            errSampleNum++;
            errRate += m_samples[i].weight;
            transErrSampleNum--;
            transErrRate -= m_samples[i].weight;
        } else {
            errSampleNum--;
            errRate -= m_samples[i].weight;
            transErrSampleNum++;
            transErrRate += m_samples[i].weight;
        }

        if (errRate <= classifierInfo.errRate - 0.000001f) {
            classifierInfo.errSampleNum = errSampleNum;
            classifierInfo.errRate = errRate;
            classifierInfo.x = (i + 1 < m_samples.size()) ? m_samples[i + 1].x : m_samples[i].x + 2;
            classifierInfo.isTrans = false;
        }
        if (transErrRate <= classifierInfo.errRate - 0.000001f) {
            classifierInfo.errSampleNum = transErrSampleNum;
            classifierInfo.errRate = transErrRate;
            classifierInfo.x = (i + 1 < m_samples.size()) ? m_samples[i + 1].x : m_samples[i].x + 2;
            classifierInfo.isTrans = true;
        }
    }

    classifierInfo.weight = std::log((1 - classifierInfo.errRate) / classifierInfo.errRate) / 2;
    return classifierInfo;
}

bool AdaBoosting::JudgeFinish()
{
    if (m_classifier.empty()) {
        return false;
    }

    for (auto &sample : m_samples) {
        float sum = 0;
        for (auto &classifierInfo : m_classifier) {
            float weight = (sample.x >= classifierInfo.x) ? classifierInfo.weight : -classifierInfo.weight;
            if (classifierInfo.isTrans) {
                weight = -weight;
            }
            sum += weight;
        }
        if (sum > 0 ^ sample.type == 1) {
            return false;
        }
    }
    return true;
}

void AdaBoosting::UpdateSamplesRate(float errRate)
{
    for (auto &sample : m_samples) {
        sample.weight *= (sample.x >= m_classifier.back().x ^ sample.type != 1 ^ m_classifier.back().isTrans)
                ? (1.0f / errRate) : errRate;
    }
    float sum = 0;
    for (auto &sample : m_samples) {
        sum += sample.weight;
    }
    for (auto &sample : m_samples) {
        sample.weight /= sum;
    }
}

void AdaBoosting::Output()
{
    for (auto classifierInfo : m_classifier) {
        if (classifierInfo.isTrans) {
            printf("x < %d, weight = %f\n", classifierInfo.x, classifierInfo.weight);
        } else {
            printf("x >= %d, weight = %f\n", classifierInfo.x, classifierInfo.weight);
        }
    }
}

void AdaBoosting::OutputSamplesRate()
{
    for (auto sample : m_samples) {
        printf("%d %d %f\n", sample.x, sample.type, sample.weight);
    }
    printf("\n");
}
