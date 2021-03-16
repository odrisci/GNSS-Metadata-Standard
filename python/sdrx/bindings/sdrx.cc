#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

//#include "sample_source.hpp"

namespace py = pybind11;

void bind_any_uri(py::module &m);
void bind_band(py::module &m);
void bind_block(py::module &m);
void bind_chunk(py::module &m);
void bind_date(py::module &m);
void bind_duration(py::module &m);
void bind_file(py::module &m);
void bind_frequency(py::module &m);
void bind_front_end(py::module &m);
void bind_lane(py::module &m);
void bind_lump(py::module &m);
void bind_metadata(py::module &m);
void bind_position(py::module &m);
void bind_session(py::module &m);
void bind_sample_stream_info(py::module &m);
void bind_stream(py::module &m);
void bind_system(py::module &m);

//template< typename sample_base_t >
//void bind_sample_source(py::module &m);

PYBIND11_MODULE(sdrx_cpp_api, m)
{
    bind_any_uri(m);
    bind_band(m);
    bind_block(m);
    bind_chunk(m);
    bind_date(m);
    bind_duration(m);
    bind_file(m);
    bind_frequency(m);
    bind_lane(m);
    bind_lump(m);
    bind_position(m);
    bind_sample_stream_info(m);
    //bind_sample_source<int8_t>(m);
    //bind_sample_source<int16_t>(m);
    //bind_sample_source<float>(m);
    bind_session(m);
    bind_stream(m);
    bind_system(m);

    // Do this last:
    bind_metadata(m);
    bind_front_end(m);
}

