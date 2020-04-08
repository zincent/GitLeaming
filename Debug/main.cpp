#include <QCoreApplication>
#include <iostream>
#include <cstdio>
#include <vector>
#include <functional>
#include <memory>

using namespace std;
//helper function
typedef std::pair<std::function<bool(int)>
                 ,std::function<void(void)>> IfDoPair;
//指向类型为IfDoPair的对象的指针P_IfDoPair;
typedef std::shared_ptr<IfDoPair> P_IfDoPair;
typedef std::vector<P_IfDoPair> IfDoContainer;
IfDoContainer allcases;

template<typename F1, typename F2>
void add_case(F1& judgeFunc, F2& doFunc)
{
    auto ifDoPair = std::make_shared<IfDoPair>(judgeFunc,doFunc);
    allcases.push_back(ifDoPair);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //add all cases
    add_case([](int nPara1){return nPara1 > 0 && nPara1<= 10;},
                        [](){std::cout<<"show 1";});


    add_case([](int nPara1){return nPara1 > 11 && nPara1<= 20;},
                        [](){std::cout<<"show 2";});

    //replace if-else
    int nJudgeNumber = 15;
    for(IfDoContainer::iterator it = allcases.begin(); it!=allcases.end(); it++)
    {
        if((*it)->first(nJudgeNumber))
        {
            (*it)->second();
        }
    }

    int nPause = 0;
    std::cin>>nPause;

    return a.exec();
}
