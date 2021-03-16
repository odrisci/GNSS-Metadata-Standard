#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "Duration.h"

void bind_duration(py::module &m)
{
    using Duration = ::GnssMetadata::Duration;
    using DurationFormat = ::GnssMetadata::Duration::DurationFormat;

    py::class_<Duration> duration (m,"Duration");
    duration.def(py::init<const double>())
        .def(py::init<const double, DurationFormat>())

        .def("Format", py::overload_cast<>(
                    &Duration::Format, py::const_) )

        .def("Value", py::overload_cast<const double, DurationFormat>(
                    &Duration::Value ),
                "Set the value of the duration with a given format",
                py::arg("value"), py::arg("format"))


        .def("__repr__",
                []( const Duration &f ){
                    return "<sdrx.duration with value: " + f.toString() + ">";
                }
            )

        .def("__str__",
                [](const Duration &f ){
                    return f.toString();
                }
            );

    py::enum_<DurationFormat>(m,"DurationFormat")
        .value("sec",   DurationFormat::sec)
        .value("msec",  DurationFormat::msec)
        .value("usec",  DurationFormat::usec)
        .value("nsec",  DurationFormat::nsec)
        .value("psec", DurationFormat::psec);

}


