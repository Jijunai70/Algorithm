//
// Created by w00896870 on 2026/1/9.
//

#ifndef CPP26_ADABOOSTING_H
#define CPP26_ADABOOSTING_H

#include <vector>

struct ClassifierInfo {
    // 分段区间
    int x;
    // 是否反向区间
    bool isTrans;
    // 错误数量
    int errSampleNum;
    // 权重错误率
    float errRate;
    // 分类器权重
    float weight;
};

struct SampleInfo {
    // 坐标x
    int x;
    // 类型
    int type;
    // 权重
    float weight;
};

class AdaBoosting
{
public:
    AdaBoosting(const std::vector<std::pair<int, int>> &samples);

    bool Run();

    void Output();

private:
    // 判定分类是否结束
    bool JudgeFinish();
    // 得到当前样本权重的最小错误分类方法
    ClassifierInfo GetClassifierInfo();
    // 更新样本权重
    void UpdateSamplesRate(float errRate);
    void OutputSamplesRate();

    std::vector<SampleInfo> m_samples; // 入参样本
    std::vector<ClassifierInfo> m_classifier; // 弱分类器权重
};


#endif //CPP26_ADABOOSTING_H
