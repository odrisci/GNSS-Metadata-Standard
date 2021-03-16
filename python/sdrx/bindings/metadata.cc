#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "GnssMetadata.h"
#include "Xml/XmlProcessor.h"

void bind_metadata(py::module &m)
{
    using Metadata = ::GnssMetadata::Metadata;
    using XmlProcessor = ::GnssMetadata::XmlProcessor;

    py::class_<Metadata>(m, "metadata")
        .def(py::init([](const std::string &fileName) {
          auto new_md = std::make_unique<Metadata>(fileName);
          XmlProcessor xmlProc;

          xmlProc.Load(fileName.c_str(), false, *new_md);

          return new_md;
        }))

        .def("Files", py::overload_cast<>(&Metadata::Files, py::const_))

        .def("Files", py::overload_cast<>(&Metadata::Files))

        .def("Bands", py::overload_cast<>(&Metadata::Bands))

        .def("Streams", py::overload_cast<>(&Metadata::Streams))

        .def("Lanes", py::overload_cast<>(&Metadata::Lanes))

        .def("Sessions", py::overload_cast<>(&Metadata::Sessions))

        .def("Systems", py::overload_cast<>(&Metadata::Systems))

        .def("__repr__",
             [](const Metadata &md) {
               return "<sdrx.metadata with Id: " + md.Id() + ">";
             })

        .def("__str__", [](const Metadata &md) {
          std::string res = "";
          for (auto const &bnd : md.Bands()) {
            res += "Band: " + bnd.toString() + "\n";
          }
          for (auto const &file : md.Files()) {
            res += "File: " + file.toString() + "\n";
          }
          for (auto const &stream : md.Streams()) {
            res += "Stream: " + stream.toString() + "\n";
          }
          return res + md.toString();
        });
}
