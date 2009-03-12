find_package(Qt4 REQUIRED)

set(pulse-qt-test_SRCS
	main.cpp
    testapp.cpp
)

set(pulse-qt-test_MOC_HDRS
    testapp.h
)

include(${QT_USE_FILE})
qt4_wrap_cpp(pulse-qt-test_MOC_SRCS ${pulse-qt-test_MOC_HDRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${QT_INCLUDES})
add_definitions(${QT_DEFINITIONS})

add_executable(pulse-qt-test ${pulse-qt-test_SRCS} ${pulse-qt-test_MOC_SRCS})

target_link_libraries(pulse-qt-test pulse-qt ${QT_LIBRARIES})
