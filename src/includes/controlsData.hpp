#pragma once

#include <iostream>
#include <memory>
#include <functional>
#include <string>
#include "procesData.hpp"

class controlsData
{
    // procesData prData{N};

private:
    int N;
    bool request = true;

public:
    controlsData(){};
    controlsData(int argN)
    {
        N = argN;
    }

    ~controlsData(){};

    void controls(std::string data);
};
