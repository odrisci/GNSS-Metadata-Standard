#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "Lane.h"

void bind_lane(py::module &m)
{
    using Lane = ::GnssMetadata::Lane;

    py::class_<Lane> lane (m,"Lane");
    lane.def(py::init<>())

        .def(py::self == py::self)

        .def("Sessions", py::overload_cast<>(
                    &Lane::Sessions, py::const_) )

        .def("Systems", py::overload_cast<>(
                    &Lane::Systems, py::const_) )

        .def("Blocks", py::overload_cast<>(
                    &Lane::Blocks, py::const_) )

        .def("__repr__",
                []( const Lane &f ){
                    return "<sdrx.lane with value: " + f.toString() + ">";
                }
            )

        .def("__str__",
                [](const Lane &f ){
                    return f.toString();
                }
            );

}



