/*
pandasやmatplotlibのようなグラフ化機能が強力なので
pythonから呼び出せるようにする
*/
#include "LogisticMap.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h> 


namespace py = pybind11;
PYBIND11_PLUGIN(LogisticPyWrapper) {
    py::module m("LogisticMap", "LogisticMap made by pybind11");

     py::class_<LogisticMap>(m, "LogisticMap")
         .def(py::init<uint64_t, uint64_t>())
         .def("Run", &LogisticPyWrapper::Run)
         .def("CalcLimit", &LogisticPyWrapper::CalcLimit);
    return m;
}