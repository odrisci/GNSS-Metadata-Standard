#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "File.h"

void bind_file(py::module &m)
{
    using File = ::GnssMetadata::File;

    py::class_<File> file (m,"File");
    file.def(py::init<>())

        .def("Url", py::overload_cast<>(
                    &File::Url, py::const_) )

        .def("TimeStamp", py::overload_cast<>(
                    &File::TimeStamp, py::const_) )

        .def("Offset", py::overload_cast<>(
                    &File::Offset, py::const_) )

        .def("Owner", py::overload_cast<>(
                    &File::Owner, py::const_) )

        .def("Copyright", py::overload_cast<>(
                    &File::Copyright, py::const_) )

        .def("Next", py::overload_cast<>(
                    &File::Next, py::const_) )

        .def("Previous", py::overload_cast<>(
                    &File::Previous, py::const_) )

        .def("Lane", py::overload_cast<>(
                    &File::Lane, py::const_) )

        .def("__repr__",
                []( const File &f ){
                    return "<sdrx.file with value: " + f.toString() + ">";
                }
            )

        .def("__str__",
                [](const File &f ){
                    return f.toString();
                }
            );

}


