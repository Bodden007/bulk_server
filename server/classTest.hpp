#pragma once
#include <iostream>
#include <vector>

class classTest
{

public:
    void method(std::string strBuf)
    {
        std::cout << "strBuf: " << strBuf << std::endl;
        if (strBuf.compare("all") != 0)
        {
            vec.push_back(strBuf);
            std::cout << "ALL Vector size:  " << vec.size() << std::endl;
        }
        else
        {
            std::cout << "Buffer: " << strBuf << std::endl;
            std::cout << "Vector size:  " << vec.size() << std::endl;
            for (auto v : vec)
            {
                std::cout << "vec:  " << v << std::endl;
            }
        }
    }

private:
    std::vector<std::string> vec;
};
