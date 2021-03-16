#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <ctime>
#include "Date.h"

void bind_date(py::module &m)
{
    using Date = ::GnssMetadata::Date;

    py::class_<Date> date (m,"Date");
    date.def(py::init<>())

        .def(py::init<int, int, int, int,int, double>()) // Y M D H m S

        .def(py::init<std::time_t, double>()) // time_t, fractional seconds

        .def(py::init<double, int, int>()) // GPS Seconds, GPS week, leaps

        .def(py::init<const char *, int>()) // date as string, leaps

        .def("Year", &Date::Year)
        .def("Month", &Date::Month)
        .def("Day", &Date::Day)
        .def("DayOfYear", &Date::DayOfYear)
        .def("DayOfWeek", &Date::DayOfWeek)
        .def("Hour", &Date::Hour)
        .def("Minute", &Date::Minute)
        .def("Second", &Date::Second)

        .def("GpsWeek", &Date::GpsWeek)
        .def("GpsSec", &Date::GpsSec)

        .def("__repr__",
                []( const Date &f ){
                    return "<sdrx.date with value: " + f.toString() + ">";
                }
            )

        .def("__str__",
                [](const Date &f ){
                    return f.toString();
                }
            );

}



