```
cmake -S . -B build
cmake --build build --parallel 12

# On Windows with VCC
# ./build/src/Debug/raytracer.exe
```

# cppcheck

On Windows
```
docker run --rm -v `pwd -W`:/data frankwolf/cppcheck --verbose --enable=all --inconclusive --language=c++ --suppress=missingIncludeSystem --suppress=unusedFunction --error-exitcode=1 src
```
