#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "SampleFrontEnd.h"
#include "GnssMetadata.h"
#include "Xml/XmlProcessor.h"



class WrappedFrontEnd : public SampleFrontEnd
{
    using GnssMetadata = ::GnssMetadata::Metadata;
    using XmlProcessor = ::GnssMetadata::XmlProcessor;
public:
  std::string format_descriptor;
  std::size_t output_size;
  //using SampleFrontEnd::GetSourceInfo;
  //using SampleFrontEnd::GetHeaderFooterSources;

  WrappedFrontEnd(const std::string &fileName,
                  const std::string &output_format = "float") {
    auto new_md = std::make_unique<GnssMetadata>(fileName);
    XmlProcessor xmlProc;
    xmlProc.Load(fileName.c_str(), false, *new_md);

    if (output_format == "int8") {
      this->Open<int8_t>(*new_md);
      format_descriptor = py::format_descriptor<int8_t>::format();
      output_size = 1;
    } else if (output_format == "int16") {
      this->Open<int16_t>(*new_md);
      format_descriptor = py::format_descriptor<int16_t>::format();
      output_size = 2;
    } else if (output_format == "int32") {
      this->Open<int32_t>(*new_md);
      format_descriptor = py::format_descriptor<int32_t>::format();
      output_size = 4;
    } else if (output_format == "int64") {
      this->Open<int64_t>(*new_md);
      format_descriptor = py::format_descriptor<int64_t>::format();
      output_size = 8;
    } else if (output_format == "float") {
      this->Open<float>(*new_md);
      format_descriptor = py::format_descriptor<float>::format();
      output_size = 4;
    } else if (output_format == "double") {
      this->Open<double>(*new_md);
      format_descriptor = py::format_descriptor<double>::format();
      output_size = 8;
    }
  }

  const py::memoryview GetSource( const std::string sinkName ) const
  {

      const int8_t *ptr;
      uint32_t num_bytes = SampleFrontEnd::GetSource(sinkName)->GetSamples( ptr );
      ssize_t num_els = num_bytes/output_size;
      py::buffer_info bi(const_cast<void *>(static_cast<const void *>(ptr)),
                         output_size, format_descriptor, 1, {num_els}, {1});

      std::cout << "Got a source with format descriptor: " << format_descriptor;
      std::cout << " read " << num_bytes << " bytes";
      std::cout << " which is " << num_els << " elements";
      std::cout << "\n";

      return py::memoryview(bi);
  }

  std::map< std::string, std::pair<const py::memoryview, const SampleStreamInfo*> > GetSources( ) const
  {
      auto cpp_map = SampleFrontEnd::GetSources();

      std::map<std::string, std::pair<const py::memoryview, const SampleStreamInfo*>>
          ret;
      for( auto const & cpp_el : cpp_map )
      {
        ret.emplace(cpp_el.first, std::make_pair(GetSource(cpp_el.first),
                                                 cpp_el.second.second));
      }
      return ret;
  }
};

void bind_front_end(py::module &m)
{

  py::class_<WrappedFrontEnd>(m, "frontend")
      .def(py::init([](const std::string &fileName,
                       const std::string &output_format) {
             return std::make_unique<WrappedFrontEnd>(fileName, output_format);
           }),
           "A source of samples using the ION GNSS Metadata standard",
           py::arg("sdrx_file"), py::arg("output_format") = "float")

      .def("GetSource", py::overload_cast<const std::string>(
                            &WrappedFrontEnd::GetSource, py::const_))

      .def("GetSourceInfo", py::overload_cast<const std::string>(
                                &WrappedFrontEnd::GetSourceInfo, py::const_))

      .def("GetSources",
           py::overload_cast<>(&WrappedFrontEnd::GetSources, py::const_))

      .def("GetHeaderFooterSources",
           py::overload_cast<>(&WrappedFrontEnd::GetHeaderFooterSources,
                               py::const_))

      .def("Load", &WrappedFrontEnd::Load)

      .def("__repr__",
           [](const WrappedFrontEnd &fe) {
             std::string res = "<sdrx.frontend with sources: ";
             for (auto const &iter : fe.GetSources()) {
               fe.GetSourceInfo(iter.first)->Print();
             }
             res += ">";
             return res;
           })

      .def("__str__",
           [](const WrappedFrontEnd &fe) { return "<sdrx.frontend>"; });
}
