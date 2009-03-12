set(QT_DONT_USE_QTGUI)
find_package(PulseAudio REQUIRED)
find_package(Qt4 REQUIRED)
find_package(GLIB2 REQUIRED)

include(${QT_USE_FILE})
set(pa-libs-qt_SRCS
    context.cpp
    mainloop.cpp
    sink.cpp
)

set(pa-libs-qt_MOC_HDRS
    context.h
    sink.h
)

qt4_wrap_cpp(pa-libs-qt_MOC_SRCS ${pa-libs-qt_MOC_HDRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${QT_INCLUDES} ${GLIB2_INCLUDE_DIR})

add_definitions(${QT_DEFINITIONS})

add_library(pulse-qt SHARED ${pa-libs-qt_SRCS} ${pa-libs-qt_MOC_SRCS})

target_link_libraries(pulse-qt ${QT_LIBRARIES} ${PULSEAUDIO_LIBRARY} pulse-mainloop-glib ${GLIB2_LIBRARIES})

install(TARGETS pulse-qt DESTINATION lib)
