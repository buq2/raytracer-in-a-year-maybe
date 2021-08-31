```
cmake -S . -B build
cmake --build build --parallel 12

# On Windows with VCC
# ./build/src/Debug/raytracer.exe
```

# Release build Windows
```
cmake --build build --parallel 12 --config Release
```

# cppcheck

On git bash on Windows
```
docker run --rm -v `pwd -W`:/data frankwolf/cppcheck --verbose --enable=all --inconclusive --language=c++ --suppress=missingIncludeSystem --suppress=unusedFunction --error-exitcode=1 src
```

# clang-format

On git bash on Windows
```
docker run --rm -it -v `pwd -W`:/workdir unibeautify/clang-format -i -style=Google **/{*.cpp,*.hh}
``` 
