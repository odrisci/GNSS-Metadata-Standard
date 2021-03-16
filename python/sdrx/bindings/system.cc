#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "System.h"

void bind_system(py::module &m)
{
    using System = ::GnssMetadata::System;

    py::class_<System> system (m,"System");
    system.def(py::init<>())

        .def("BaseFrequency", py::overload_cast<>(
                    &System::BaseFrequency, py::const_) )

        .def("Equipment", py::overload_cast<>(
                    &System::Equipment, py::const_) )

        .def("Sources", py::overload_cast<>(
                    &System::Sources, py::const_) )

        .def("Clusters", py::overload_cast<>(
                    &System::Clusters, py::const_) )

        .def("__repr__",
                []( const System &f ){
                    return "<sdrx.system with value: " + f.toString() + ">";
                }
            )

        .def("__str__",
                [](const System &f ){
                    return f.toString();
                }
            );

}




