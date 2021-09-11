from conanio/gcc10

# Following packages are required by conan packages (mostly xorg)
RUN sudo apt-get update && sudo apt-get install -y --no-install-recommends \
    libegl-dev xorg-dev libx11-xcb-dev libxcb-render0-dev libxcb-render-util0-dev \
    libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev \
    libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xfixes0-dev \
    libxcb-xinerama0-dev xkb-data libxcb-dri3-dev libxcb-util-dev \
    libglu1-mesa-dev && \
    sudo rm -rf /var/lib/apt/lists/*

COPY . .
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --parallel 12
 