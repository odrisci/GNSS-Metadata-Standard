#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "Position.h"

void bind_position(py::module &m)
{
    using Position = ::GnssMetadata::Position;

    py::class_<Position> position (m,"Position");
    position
        .def(py::init<double, double, double>())

        .def("Latitude", py::overload_cast<>(&Position::Latitude, py::const_))

        .def("Longitude", py::overload_cast<>(&Position::Longitude, py::const_))

        .def("Height", py::overload_cast<>(&Position::Height, py::const_))

        .def("__repr__",
             [](const Position &f) {
               return "<sdrx.position with value: " + f.toString() + ">";
             })

        .def("__str__", [](const Position &f) { return f.toString(); });
}

