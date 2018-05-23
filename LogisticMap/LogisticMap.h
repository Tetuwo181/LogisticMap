#pragma once
#include <vector>
#include <functional>

using namespace std;
class LogisticMap
{

private:
	uint64_t recordNum;// �l���L�^���Ă����z��
	uint64_t iterateNum;//�Ɍ������߂�ۂ̌J��Ԃ��̉񐔁@record_num���傫���Ȃ���΂Ȃ�Ȃ�
public:
	LogisticMap();
	~LogisticMap();
	LogisticMap(const uint64_t recordNumBase = 100,const uint64_t iterateNumBase = 100000);
	double Run(const double a, const double value);
	std::vector<double> Fit(const double a, const double initValue);
};
