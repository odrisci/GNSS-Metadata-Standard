#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "Band.h"

void bind_band(py::module &m)
{
    using Band = ::GnssMetadata::Band;

    py::class_<Band>(m,"band")
        .def(py::init<const std::string &>())

        .def("CenterFrequency", py::overload_cast<>(
                    &Band::CenterFrequency, py::const_) )

        .def("TranslatedFrequency", py::overload_cast<>(
                    &Band::TranslatedFrequency, py::const_) )

        .def("Inverted", py::overload_cast<>(
                    &Band::Inverted, py::const_) )

        .def("Bandwidth", py::overload_cast<>(
                    &Band::Bandwidth, py::const_) )

        .def("DelayBias", py::overload_cast<>(
                    &Band::DelayBias, py::const_) )

        .def("__repr__",
                []( const Band &b ){
                    return "<sdrx.Band with value: " + b.toString() + ">";
                }
            )

        .def("__str__",
                [](const Band &b ){
                    return b.toString();
                }
            );


}


