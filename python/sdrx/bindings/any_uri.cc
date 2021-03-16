#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "AnyUri.h"

void bind_any_uri(py::module &m)
{
    using AnyUri = ::GnssMetadata::AnyUri;

    py::class_<AnyUri> any_uri (m,"AnyUri");
    any_uri
        .def(py::init<const std::string &>())

        .def("IsDefined", &AnyUri::IsDefined)

        .def("Value", py::overload_cast<>(&AnyUri::Value, py::const_))

        .def("__repr__",
             [](const AnyUri &f) {
               return "<sdrx.any_uri with value: " + f.toString() + ">";
             })

        .def("__str__", [](const AnyUri &f) { return f.toString(); });
}



