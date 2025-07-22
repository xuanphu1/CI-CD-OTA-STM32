FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    cmake \
    python3 \
    python3-pip \
    git \
    wget \
    unzip \
    ca-certificates

# Install ARM GCC toolchain (version 10.3-2021.10, bạn có thể đổi version nếu cần)
RUN wget -q https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 \
    && tar -xjf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 \
    && mv gcc-arm-none-eabi-10.3-2021.10 /opt/gcc-arm-none-eabi \
    && rm gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2

ENV PATH="/opt/gcc-arm-none-eabi/bin:${PATH}"

# Optional: install extra Python libraries if needed (websocket-client, ...)
RUN pip3 install --no-cache-dir websocket-client

# Set default working directory when run
WORKDIR /FirmwareSTM32

# Default command (can be overridden in CI/CD)
CMD ["make"]
