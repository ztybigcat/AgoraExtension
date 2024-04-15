# Start with a CUDA-enabled base image
FROM nvidia/cuda:12.4.1-base-ubuntu22.04

# Install necessary packages for building and compiling
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    python3.11 \
    python3-pip \
    python3.11-dev \
    git \
    gdb \
    libxfixes3 \
    libdrm2 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

COPY ./agora_sdk/libagora-fdkaac.so /usr/local/lib/libagora-fdkaac.so
COPY ./agora_sdk/libagora-ffmpeg.so /usr/local/lib/libagora-ffmpeg.so
COPY ./agora_sdk/libagora_rtc_sdk.so /usr/local/lib/libagora_rtc_sdk.so

ENV Python_EXECUTABLE=/usr/bin/python3.11
ENV Python_INCLUDE_DIRS=/usr/include/python3.11
ENV Python_LIBRARIES=/usr/lib/x86_64-linux-gnu/libpython3.11.so

# Command to run your application
CMD ["/bin/bash"]
