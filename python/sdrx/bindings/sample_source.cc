#ifndef SDRX_SAMPLE_SOURCE_INCLUDED
#define SDRX_SAMPLE_SOURCE_INCLUDED (0)
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

#include "SampleSource.h"

// Need to "Trampoline" the pure virtual interface class here:

class WrappedSampleSource : public SampleSource
{
    protected:
        bool Open() override{
          PYBIND11_OVERRIDE_PURE(bool,                    // return type
                                 SampleSource<sample_base_t>, // parent type
                                 Open            // C++ function name
        }

    public:
        using SampleSource<sample_base_t>::SampleSource<sample_base_t>;

        uint32_t GetSamples( const  int8_t*& pbuff )  const override
        {
          PYBIND11_OVERRIDE_PURE(uint32_t,                    // return type
                                 SampleSource<sample_base_t>, // parent type
                                 GetSamples,            // C++ function name
                                 const int8_t *& // argument
          );
        }

        uint32_t GetSamples( const  int16_t*& pbuff )  const override
        {
          PYBIND11_OVERRIDE_PURE(uint32_t,                    // return type
                                 SampleSource<sample_base_t>, // parent type
                                 GetSamples,            // C++ function name
                                 const int16_t *& // argument
          );
        }

        uint32_t GetSamples( const  int32_t*& pbuff )  const override
        {
          PYBIND11_OVERRIDE_PURE(uint32_t,                    // return type
                                 SampleSource<sample_base_t>, // parent type
                                 GetSamples,            // C++ function name
                                 const int32_t *& // argument
          );
        }

        uint32_t GetSamples( const  float*& pbuff )  const override
        {
          PYBIND11_OVERRIDE_PURE(uint32_t,                    // return type
                                 SampleSource<sample_base_t>, // parent type
                                 GetSamples,            // C++ function name
                                 const float *& // argument
          );
        }

        uint32_t GetSamples( const  double*& pbuff )  const override
        {
          PYBIND11_OVERRIDE_PURE(uint32_t,                    // return type
                                 SampleSource<sample_base_t>, // parent type
                                 GetSamples,            // C++ function name
                                 const double *& // argument
          );
        }

        void Close() override
        {
          PYBIND11_OVERRIDE_PURE(void,                    // return type
                                 SampleSource<sample_base_t>, // parent type
                                 Close            // C++ function name
          );
        }

        void Clear() override
        {
          PYBIND11_OVERRIDE_PURE(void,                    // return type
                                 SampleSource<sample_base_t>, // parent type
                                 Clear            // C++ function name
          );
        }

};

void bind_sample_source(py::module &m)
{
    py::class_<SampleSourceTrampoline<sample_base_t>>(m, "SampleSource")
        .def(py::init())

        .def("GetSamples", []( const SampleSource &ss){
                sample_base_t const*ptr;
                auto num_samps = ss.GetSamples( ptr );

                return py::array( num_samps, ptr );
            })

        .def("__repr__",
             [](const SampleSource &si) {
               return "<sdrx.SampleSource>";
             })

        .def("__str__",
             [](const SampleSource &si) {return "<sdrx.SampleSource>";});
}


#endif /* ifndef SDRX_SAMPLE_SOURCE_INCLUDED */

