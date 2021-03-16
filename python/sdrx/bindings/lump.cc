#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "Lump.h"

void bind_lump(py::module &m)
{
    using Lump = ::GnssMetadata::Lump;
    using LumpShift = ::GnssMetadata::Lump::LumpShift;

    py::class_<Lump> lump (m,"Lump");
    lump.def(py::init<>())

        .def("Streams", py::overload_cast<>(
                    &Lump::Streams, py::const_) )

        .def("Shift", py::overload_cast<>(
                    &Lump::Shift, py::const_) )

        .def("__repr__",
                []( const Lump &f ){
                    return "<sdrx.lump with value: " + f.toString() + ">";
                }
            )

        .def("__str__",
                [](const Lump &f ){
                    return f.toString();
                }
            );

    py::enum_<LumpShift>(m,"LumpShift")
        .value("Left",   LumpShift::shiftLeft)
        .value("Right",  LumpShift::shiftRight)
        .value("Undefined",  LumpShift::shiftUndefined);

}






