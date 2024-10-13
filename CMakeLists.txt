cmake_minimum_required(VERSION 3.12)

project(cgui
    LANGUAGES CXX
    VERSION 1.0.0
)

set(CMAKE_CXX_STANDARD 20)

add_library(CGUI
    include/cgui/components/basicImage.h
    include/cgui/components/basicProgressBar.h
    include/cgui/components/basicText.h
    include/cgui/components/component.h
    include/cgui/components/multiLineText.h
    include/cgui/components/sameLine.h
    include/cgui/utils/string.h
    include/cgui/logicPos.h
    include/cgui/page.h
    include/cgui/cgui.h
    src/basicImage.cpp
    src/basicProgressBar.cpp
    src/basicText.cpp
    src/multiLineText.cpp
    src/page.cpp
    src/sameLine.cpp
    src/string.cpp
)

target_include_directories(CGUI PUBLIC
    include/
)

add_subdirectory(sandbox)