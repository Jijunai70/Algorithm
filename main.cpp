//
// Created by w00896870 on 2026/1/9.
//

#include <bits/stdc++.h>

#include <AdaBoosting.h>

using namespace std;

int main()
{
    std::vector<std::pair<int, int>> samples = {
            {-10, 0},
            {-8, 0},
            {-6, 1},
            {-4, 1},
            {-2, 0},
            {0, 0},
            {2, 0},
            {4, 0},
            {6, 1},
            {8, 1},
    };
    AdaBoosting ada(samples);
    ada.Run();
    ada.Output();

    return 0;
}