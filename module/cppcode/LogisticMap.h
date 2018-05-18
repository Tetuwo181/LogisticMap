#pragma once

class LogisticMap{
    private:
        uint64_t record_num;// 値を記録しておく配列長
        uint64_t iterate_num;//極限を求める際の繰り返しの回数　record_numより大きくなければならない
    public:
        LogisticMap(double base_val, uint64_t record_num = 100, uint64_t iterate_num = 100000);
        double Run(const double a, const double value);
        std::vector<double> CalcLimit(const double a, const double init_value);

};

LogisticMap::LogisticMap(uint64_t record_num, uint64_t iterate_num){
    if(record_num < iterate_num){
        this.record_num = record_num;
        this.iterate_num = iterate_num;
    }else{
        this.record_num = iterate_num;
        this.iterate_num = record_num;
    }
}

double LogisticMap::Run(const double a, const double value){
    /*
    ロジスティック写像を行う
    引数の説明
    double a: a*x(1.0-x)のaの部分  
    double value: 現在の値
    */
   return a*value(1.0-value);
}

std::vector<double> LogisticMap::CalcLimit(const double a, const double init_value){
    /*
    引数を基に指定した回数分だけロジスティック写像を行い
    値を記録しておく
    Params params: ロジスティック写像を行う際のパラメーター
    */
    double x = initial_value;   
    std::vector<double> record_value;
    uint64_t record_start_point = params.iterate_num - params.record_num;
    for(iteration = 0: iteration < params.iterate_num; iteration++){
        x = this.Run(a, x);
        if(iteration > record_start_point){
            record_value.add(x);
        }
    }
    return record_value
}


