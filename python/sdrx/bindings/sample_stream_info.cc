#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "SampleStreamInfo.h"

void bind_sample_stream_info(py::module &m)
{
    py::class_<SampleStreamInfo>(m, "SampleStreamInfo")
        .def(py::init())

        .def_readonly("laneID", &SampleStreamInfo::mLaneID)
        .def_readonly("centreFrequency", &SampleStreamInfo::mCenterFrequency)
        .def_readonly("translatedFrequency", &SampleStreamInfo::mTranslatedFrequency)
        .def_readonly("delayBias", &SampleStreamInfo::mDelayBias)
        .def_readonly("sampleFrequency", &SampleStreamInfo::mSampleFrequency)
        .def_readonly("quantization", &SampleStreamInfo::mQuantization)
        .def_readonly("isComplex", &SampleStreamInfo::mIsComplexSamples)

        .def("__repr__",
             [](const SampleStreamInfo &si) {
               std::string res = "<sdrx.SampleStreamInfo with :";
               res += " Lane: " + si.mLaneID;
               res += ", CentreFrequency: " + si.mCenterFrequency.toString();
               res += ", TranslatedFrequency: " + si.mTranslatedFrequency.toString();
               res += ", SampleFrequency: " + si.mSampleFrequency.toString();
               res += ", BaseFrequency: " + si.mBaseFrequency.toString();
               res += ", Duration: " + si.mDelayBias.toString();
               res += ">";
               return res;
             })

        .def("__str__",
             [](const SampleStreamInfo &si) { 
                std::string res;
                res += " CentreFrequency: " + si.mCenterFrequency.toString();
                res += ", TranslatedFrequency: " + si.mTranslatedFrequency.toString();
                res += ", SampleFrequency: " + si.mSampleFrequency.toString();
                res += ", BaseFrequency: " + si.mBaseFrequency.toString();
                res += ", Duration: " + si.mDelayBias.toString();
                return res; });
}


