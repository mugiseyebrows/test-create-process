pushd %~dp0
    mkdir build
    pushd build
        cmake .. && cmake --build . --config release
    popd
popd