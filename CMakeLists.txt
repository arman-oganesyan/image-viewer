cmake_minimum_required(VERSION 3.10)

project(ImageViewer VERSION 1.0)

# Set c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
    src/events/imagedataevent.cpp
    src/events/imageeventfinished.cpp
    src/events/imageeventstarted.cpp
    src/events/imagetaskevent.cpp
    src/models/imagemodel.cpp
    src/core.cpp
    src/folderhandler.cpp
    src/main.cpp
    src/image-viewer.qrc
)

find_package(Qt5Quick REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories(./src)
include_directories(${Qt5Quick_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

if(WIN32)
  set(GUI_TYPE WIN32)
elseif(APPLE)
  set(GUI_TYPE MACOSX_BUNDLE)
endif()

set(TARGET_NAME ImageViewer)
add_executable(${TARGET_NAME} ${GUI_TYPE} ${SOURCES})
target_link_libraries(${TARGET_NAME} Qt5::Quick Qt5::Widgets)
