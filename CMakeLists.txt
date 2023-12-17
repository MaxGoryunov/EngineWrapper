# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project ("EngineWrapper")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (EngineWrapper "Source.cpp" "Engine.h" "Subject.h" "Wrapper.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET EngineWrapper PROPERTY CXX_STANDARD 17)
endif()