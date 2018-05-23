#define NOMINMAX
#define CRT_SECURE_NOWARNINGS


#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#include "LogisticMap.h"



LogisticMap::LogisticMap()
{
}


LogisticMap::~LogisticMap()
{
}

LogisticMap::LogisticMap(const uint64_t recordNumBase, const uint64_t iterateNumBase)
{
	if (recordNumBase < iterateNumBase) {
		recordNum = recordNumBase;
		iterateNum = iterateNumBase;
	}
	else {
		recordNum = iterateNumBase;
		iterateNum = recordNumBase;
	}
}

/*
ロジスティック写像を行う
引数の説明
double a: a*x(1.0-x)のaの部分
double value: 現在の値
*/
double LogisticMap::Run(const double a, const double value)
{
	return a*value*(1.0-value);
}


/*
引数を基に指定した回数分だけロジスティック写像を行い
値を記録しておく
a: ロジスティック写像を行う際のパラメータ
initValue: xの初期値
*/
std::vector<double> LogisticMap::Fit(const double a, const double initValue)
{
	double x = initValue;
	std::vector<double> recordValue;
	uint64_t record_start_point = iterateNum - recordNum;
	for (auto iteration = 0; iteration < iterateNum; iteration++) {
		x = Run(a, x);
		if (iteration > record_start_point) {
			recordValue.push_back(x);
		}
	}
	return recordValue;
}


/*
先にロジスティック写像を行う際の
aの値を初期化しておく
xの初期値によって値を比較したい際に使う
*/
std::function<vector<double>(double)> LogisticMap::InitA(const double a)
{
	return [=](double initValue) {return Fit(a, initValue);};
}

/*
先にロジスティック写像を行う際の
xの値を初期化しておく
qの初期値によって値を比較したい際に使う
*/
std::function<vector<double>(double)> LogisticMap::InitValue(const double baseValue)
{
	return [=](double a) {return Fit(a, baseValue);};
}


namespace py = pybind11;

PYBIND11_MODULE(LogisticMap, m) {
	m.doc() = "logisticmap";
	py::class_<LogisticMap>(m, "LogisticMap")
		.def(py::init<const uint64_t, const uint64_t>())
		.def("run", &LogisticMap::Run)
		.def("fit", &LogisticMap::Fit)
		.def("init_a", &LogisticMap::InitA)
		.def("init_value", &LogisticMap::InitValue);
}