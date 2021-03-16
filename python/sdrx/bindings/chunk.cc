#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "Chunk.h"

void bind_chunk(py::module &m)
{
    using Chunk = ::GnssMetadata::Chunk;
    using WordEndian = ::GnssMetadata::Chunk::WordEndian;
    using WordPadding = ::GnssMetadata::Chunk::WordPadding;
    using WordShift = ::GnssMetadata::Chunk::WordShift;

    py::class_<Chunk> chunk (m,"Chunk");
    chunk.def(py::init<>())

        .def("IsDefined", &Chunk::IsDefined )
        
        .def("CountWords", py::overload_cast<>(
                    &Chunk::CountWords, py::const_) )

        .def("SizeWord", py::overload_cast<>(
                    &Chunk::SizeWord, py::const_) )

        .def("Endian", py::overload_cast<>(
                    &Chunk::Endian, py::const_) )

        .def("Padding", py::overload_cast<>(
                    &Chunk::Padding, py::const_) )

        .def("Shift", py::overload_cast<>(
                    &Chunk::Shift, py::const_) )

        .def("Lumps", py::overload_cast<>(
                    &Chunk::Lumps, py::const_) )

        .def("__repr__",
                []( const Chunk &f ){
                    return "<sdrx.chunk with value: " + f.toString() + ">";
                }
            )

        .def("__str__",
                [](const Chunk &f ){
                    return f.toString();
                }
            );

    py::enum_<WordEndian>(m,"WordEndian")
        .value("Big",   WordEndian::Big)
        .value("Little",  WordEndian::Little)
        .value("Undefined", WordEndian::Undefined);

    py::enum_<WordPadding>(m,"WordPadding")
        .value("None",   WordPadding::None)
        .value("Head",  WordPadding::Head)
        .value("Tail", WordPadding::Tail);

    py::enum_<WordShift>(m,"WordShift")
        .value("Left",   WordShift::Left)
        .value("Right",  WordShift::Right);

}





