//
// Created by w00896870 on 2026/1/9.
//

#include <bits/stdc++.h>

#include <AdaBoosting.h>

using namespace std;

int main()
{
    std::vector<std::pair<int, int>> samples = {
            {-10, 1},
            {-8, 1},
            {-6, 0},
            {-4, 0},
            {-2, 1},
            {0, 1},
            {2, 1},
            {4, 1},
            {6, 0},
            {8, 0},
    };
    AdaBoosting ada(samples);
    ada.Run();

    return 0;
}