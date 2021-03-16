#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "Session.h"

void bind_session(py::module &m)
{
    using Session = ::GnssMetadata::Session;

    py::class_<Session> session (m,"Session");
    session.def(py::init<>())

        .def("Toa", py::overload_cast<>(
                    &Session::Toa, py::const_) )
        
        .def("Campaign", py::overload_cast<>(
                    &Session::Campaign, py::const_) )
        
        .def("Contact", py::overload_cast<>(
                    &Session::Contact, py::const_) )
        
        .def("Position", py::overload_cast<>(
                    &Session::Position, py::const_) )
        
        .def("Poc", py::overload_cast<>(
                    &Session::Poc, py::const_) )
        
        .def("Scenario", py::overload_cast<>(
                    &Session::Scenario, py::const_) )

        .def("__repr__",
                []( const Session &f ){
                    return "<sdrx.session with value: " + f.toString() + ">";
                }
            )

        .def("__str__",
                [](const Session &f ){
                    return f.toString();
                }
            );

}




