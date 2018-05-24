# -*- coding: utf-8 -*-
import LogisticMap as LM
import pandas as pd
from typing import List
from collections import namedtuple
from numba import jit


Result = namedtuple("Result", ("a," "limits"))

def initializer(record_num:int = 1000, iterate_num:int = 100000)->LM.LogisticMap:
    return LM.initializer(record_num, iterate_num)


def record_limit(init_x:float = 0.1,
                 record_num:int = 500,
                 iterate_num:int = 5000,
                 a_interval:float = 0.005,
                 a_min:float = 2.5)->List[Result]:
    logistic_map_base = initializer(record_num, iterate_num)
    logistic_map = logistic_map_base.init_value(init_x)
    loop_num = int((4.0-a_min)/a_interval)
    a = a_min
    results = [Result(a, logistic_map(a))]
    for i in range(loop_num):
        a = a + a_interval        
        results.append(Result(a, logistic_map(a)))
    return results


def convert_result_to_dataframe(a:float, result:List[float])->pd.DataFrame:
    return pd.DataFrame([[a, value] for value in result],
                        columns = ["a", "limit"])


@jit    
def convert_for_plot(result_set:List[Result])->pd.DataFrame:
    df = convert_result_to_dataframe(result_set[0].a, result_set[0].limits)
    for result in result_set[1:]:
        df = df.append(convert_result_to_dataframe(result.a, result.limits))
    return df


def run(init_x:float = 0.1,
        record_num:int = 500,
        iterate_num:int = 5000,
        a_interval:float = 0.005,
        a_min:float = 2.5)->pd.DataFrame:
    limit = record_limit(init_x, record_num, iterate_num, a_interval, a_min)
    return convert_for_plot(limit)


