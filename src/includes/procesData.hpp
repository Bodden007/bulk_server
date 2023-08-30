#pragma once
#include <iostream>
#include <vector>
#include <boost/signals2.hpp>
#include "../includes/dataTime.hpp"
#include "../includes/writeFile.hpp"
#include "../includes/outConsole.hpp"

class procesData
{
private:
    // FIXME commit out N
    // int N;
    int step = 1;
    bool dynamicBlock = false;
    bool staticBlock = true;
    int openBracket = 0;
    std::vector<std::string> bulk;

public:
    procesData(){};
    // procesData(int out_N)
    // {
    //     N = out_N;
    // }
    ~procesData(){};
    // TODO Added variable N
    void sortData(std::string in_data, int N);
    void outBulk(std::vector<std::string> &bulk);
};