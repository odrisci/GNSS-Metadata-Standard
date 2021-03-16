#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "IonStream.h"

void bind_stream(py::module &m)
{
    using Stream = ::GnssMetadata::IonStream;
    using StreamAlignment = ::GnssMetadata::IonStream::StreamAlignment;
    using StreamShift = ::GnssMetadata::IonStream::StreamShift;
    using SampleFormat = ::GnssMetadata::IonStream::SampleFormat;

    py::class_<Stream> stream(m,"stream");

    stream
        .def(py::init<const std::string &>())

        .def("Alignment", py::overload_cast<>(
                    &Stream::Alignment, py::const_) )

        .def("Encoding", py::overload_cast<>(
                    &Stream::Encoding, py::const_) )

        .def("Format", py::overload_cast<>(
                    &Stream::Format, py::const_) )

        .def("Packedbits", py::overload_cast<>(
                    &Stream::Packedbits, py::const_) )

        .def("Quantization", py::overload_cast<>(
                    &Stream::Quantization, py::const_) )

        .def("Shift", py::overload_cast<>(
                    &Stream::Shift, py::const_) )

        .def("RateFactor", py::overload_cast<>(
                    &Stream::RateFactor, py::const_) )

        .def("Bands", py::overload_cast<>(
                    &Stream::Bands, py::const_) )

        .def("__repr__",
                []( const Stream &b ){
                    return "<sdrx.Stream with value: " + b.toString() + ">";
                }
            )

        .def("__str__",
                [](const Stream &b ){
                    return b.toString();
                }
            );

    py::enum_<StreamAlignment>(m, "StreamAlignment")
        .value("Left", StreamAlignment::Left)
        .value("Right", StreamAlignment::Right)
        .value("Undefined", StreamAlignment::Undefined);

    py::enum_<StreamShift>(m, "StreamShift")
        .value("Left", StreamShift::shiftLeft)
        .value("Right", StreamShift::shiftRight)
        .value("Undefined", StreamShift::shiftUndefined);

    py::enum_<SampleFormat>(m, "SampleFormat")
        .value("IF", SampleFormat::IF)
        .value("IFn", SampleFormat::IFn)
        .value("IQ", SampleFormat::IQ)
        .value("IQn", SampleFormat::IQn)
        .value("InQ", SampleFormat::InQ)
        .value("InQn", SampleFormat::InQn)
        .value("QI", SampleFormat::QI)
        .value("QIn", SampleFormat::QIn)
        .value("QnI", SampleFormat::QnI)
        .value("QnIn", SampleFormat::QnIn)
        .value("Int8IQ", SampleFormat::Int8IQ)
        .value("Int16IQ", SampleFormat::Int16IQ);

}



