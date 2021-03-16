#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "Frequency.h"

void bind_frequency(py::module &m)
{
    using Frequency = ::GnssMetadata::Frequency;
    using FrequencyFormat = ::GnssMetadata::Frequency::FrequencyFormat;

    py::class_<Frequency> frequency (m,"Frequency");
    frequency.def(py::init<const double>())
        .def(py::init<const double, FrequencyFormat>())

        .def("Format", py::overload_cast<>(
                    &Frequency::Format, py::const_) )

        .def("Value", py::overload_cast<const double, FrequencyFormat>(
                    &Frequency::Value ),
                "Set the value of the frequency with a given format",
                py::arg("value"), py::arg("format"))

        .def("toHertz", py::overload_cast<>(
                    &Frequency::toHertz, py::const_ ),
                "Get the value of the frequency in Hz")

        .def("__repr__",
                []( const Frequency &f ){
                    return "<sdrx.frequency with value: " + f.toString() + ">";
                }
            )

        .def("__str__",
                [](const Frequency &f ){
                    return f.toString();
                }
            );

    py::enum_<FrequencyFormat>(m,"FrequencyFormat")
        .value("Hz",   FrequencyFormat::Hz)
        .value("kHz",  FrequencyFormat::kHz)
        .value("MHz",  FrequencyFormat::MHz)
        .value("GHz",  FrequencyFormat::GHz)
        .value("Ratio", FrequencyFormat::Ratio);

}

