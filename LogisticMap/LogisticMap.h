#pragma once
#include <vector>
#include <functional>

using namespace std;
class LogisticMap
{

private:
	uint64_t recordNum;// 値を記録しておく配列長
	uint64_t iterateNum;//極限を求める際の繰り返しの回数　record_numより大きくなければならない
public:
	LogisticMap();
	~LogisticMap();
	LogisticMap(const uint64_t recordNumBase = 100,const uint64_t iterateNumBase = 100000);
	double Run(const double a, const double value);
	std::vector<double> Fit(const double a, const double initValue);
};

