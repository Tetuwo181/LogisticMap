#define NOMINMAX
#define CRT_SECURE_NOWARNINGS


#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

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
���W�X�e�B�b�N�ʑ����s��
�����̐���
double a: a*x(1.0-x)��a�̕���
double value: ���݂̒l
*/
double LogisticMap::Run(const double a, const double value)
{
	return a*value*(1.0-value);
}


/*
��������Ɏw�肵���񐔕��������W�X�e�B�b�N�ʑ����s��
�l���L�^���Ă���
a: ���W�X�e�B�b�N�ʑ����s���ۂ̃p�����[�^
initValue: x�̏����l
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


namespace py = pybind11;

PYBIND11_MODULE(logistic_map, m) {
	m.doc() = "Logistic Map";
	py::class_<LogisticMap>(m, "LogisticMap")
		.def(py::init<const uint64_t, const uint64_t>())
		.def("run", &LogisticMap::Run)
		.def("fit", &LogisticMap::Fit);
}