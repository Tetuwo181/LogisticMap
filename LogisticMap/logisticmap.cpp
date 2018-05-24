#define NOMINMAX
#define CRT_SECURE_NOWARNINGS


#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#include "LogisticMap.h"



LogisticMap::LogisticMap():recordNum(100), iterateNum(10000)
{
}


LogisticMap::~LogisticMap()
{
}

LogisticMap::LogisticMap(const uint64_t recordNumBase, const uint64_t iterateNumBase):recordNum(recordNumBase), iterateNum(iterateNumBase)
{
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


/*
��Ƀ��W�X�e�B�b�N�ʑ����s���ۂ�
a�̒l�����������Ă���
x�̏����l�ɂ���Ēl���r�������ۂɎg��
*/
std::function<vector<double>(double)> LogisticMap::InitA(const double a)
{
	return [&](double initValue) {return Fit(a, initValue);};
}

/*
��Ƀ��W�X�e�B�b�N�ʑ����s���ۂ�
x�̒l�����������Ă���
a�̏����l�ɂ���Ēl���r�������ۂɎg��
*/
std::function<vector<double>(double)> LogisticMap::InitValue(const double baseValue)
{
	return [&](double a) {return Fit(a, baseValue);};
}

/*
LogisticMap�N���X���쐬����
*/
LogisticMap Initializer(const uint64_t recordNum = 100, const uint64_t iterateNum = 100000)
{
	if (recordNum < iterateNum) {
		return LogisticMap(recordNum, iterateNum);
	}
	else {
		return LogisticMap(iterateNum, recordNum);
	}
}

/*
a�̒l�����炩���ߏ����������֐���p�ӂ���
*/
std::function<vector<double>(double)> BuildLogisticMapInitializedA(double a, const uint64_t recordNum = 100, const uint64_t iterateNum = 10000)
{
	auto baseLogisticMap = Initializer(recordNum, iterateNum);
	return baseLogisticMap.InitA(a);
}

/*
x�̒l�����炩���ߏ����������֐���p�ӂ���
*/
std::function<vector<double>(double)> BuildLogisticMapInitializedX(double initValue, const uint64_t recordNum = 100, const uint64_t iterateNum = 10000)
{
	auto baseLogisticMap = Initializer(recordNum, iterateNum);
	return baseLogisticMap.InitValue(initValue);
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
	m.def("initializer", Initializer);
	m.def("build_logisticmap_initialized_a", BuildLogisticMapInitializedA);
	m.def("build_logisticmap_initialized_x", BuildLogisticMapInitializedX);
}