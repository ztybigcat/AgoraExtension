#include <pybind11/pybind11.h>
#include "AgoraChannelSender.h"

namespace py = pybind11;

PYBIND11_MODULE(agora_extension, m) {
    py::class_<AgoraChannelSender>(m, "AgoraChannelSender")
            .def(py::init<const std::string&, const std::string&, const std::string&>())
            .def("send_string", &AgoraChannelSender::sendString)
            .def("listen", &AgoraChannelSender::listen,
                 py::arg("audio_file"),
                 py::arg("sample_rate"),
                 py::arg("num_of_channels"));
}
