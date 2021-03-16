#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "Block.h"

void bind_block(py::module &m)
{
    using Block = ::GnssMetadata::Block;

    py::class_<Block> block (m,"Block");
    block.def(py::init<>())

        .def("IsDefined", &Block::IsDefined )
        
        .def("Cycles", py::overload_cast<>(
                    &Block::Cycles, py::const_) )

        .def("SizeHeader", py::overload_cast<>(
                    &Block::SizeHeader, py::const_) )

        .def("SizeFooter", py::overload_cast<>(
                    &Block::SizeFooter, py::const_) )

        .def("Chunks", py::overload_cast<>(
                    &Block::Chunks, py::const_) )

        .def("__repr__",
                []( const Block &f ){
                    return "<sdrx.block with value: " + f.toString() + ">";
                }
            )

        .def("__str__",
                [](const Block &f ){
                    return f.toString();
                }
            );

}




