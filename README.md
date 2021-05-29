# What is it?
ImageViewer helps to find all photos at the specified path in a quick way! It's multithreaded, works rapidly, and you can interact with results while ImageViewer's still working on searching your forgotten photos!

This project requires Qt >= 5.15

# Build

You can build the project using either CMake or qmake. Both CMake and pro files are provided, it's recommended to build the project using CMake, as the pro file is going to be removed in the future.


```
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=~/Qt/5.15.0/clang_64/
cmake --build .
```

# Preview
![How the application works?](/images/preview.gif)
