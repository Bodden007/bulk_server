#include "../includes/procesData.hpp"

void procesData::sortData(std::string in_data, int N)
{

    if (staticBlock)
    {
        if (in_data.compare("{") == 0)
        {
            outBulk(bulk);
            step = 1;
            staticBlock = false;
            dynamicBlock = true;
            openBracket = 1;
        }
        else if (step == N && in_data.compare("null") != 0)
        {
            bulk.push_back(in_data);
            outBulk(bulk);
            step = 1;
        }
        else if (in_data.compare("null") == 0)
        {
            outBulk(bulk);
            step = 1;
        }
        else
        {
            bulk.push_back(in_data);
            step++;
        }
    }
    else if (dynamicBlock)
    {
        if (openBracket == 0 && in_data.compare("{") == 0)
        {
            outBulk(bulk);
            openBracket++;
        }
        else if (in_data.compare("}") == 0 && openBracket == 1)
        {
            outBulk(bulk);
            openBracket = 0;
        }
        else if (in_data.compare("{") == 0 && openBracket >= 1)
        {
            openBracket++;
        }
        else if (in_data.compare("}") == 0 && openBracket >= 1)
        {
            openBracket--;
        }
        else if (in_data.compare("null") == 0)
        {
            bulk.clear();
            openBracket = 0;
        }
        else
        {
            bulk.push_back(in_data);
        }
    }
}

void procesData::outBulk(std::vector<std::string> &bulk)
{
    std::string out_balk;

    dataTime dataT;
    std::string timeDat = dataT.timeSyst();
    std::string fileName = "bulk";
    fileName += timeDat + ".log";

    writeFile writeF;
    outConsole outCon;

    boost::signals2::signal<void(std::string)> sig;
    sig.connect(boost::bind(&writeFile::outFile,
                            &writeF, std::placeholders::_1));
    sig.connect(boost::bind(&outConsole::showConsol,
                            &outCon, std::placeholders::_1));

    if (!bulk.empty())
    {
        out_balk = "bulk: ";
        for (bool isFirst{true}; auto &outBal : bulk)
        {
            out_balk += (isFirst ? isFirst = false, "" : ", ") + outBal;
        }

        sig(out_balk);
        bulk.clear();
        std::cout << std::endl;
    }
}