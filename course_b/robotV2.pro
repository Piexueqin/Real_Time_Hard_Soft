TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt



INCLUDEPATH +=\
    /usr/local/include/antlr4-runtime

LIBS +=\
    /usr/local/lib/libantlr4-runtime.so

DISTFILES += \
    file/program1.tid \
    file/program1.tip \
    grammar/robData.g4 \
    grammar/robProgram.g4 \
    xml/configs/calibration.xml \
    xml/configs/config.xml \
    xml/zecm_demo.xml

HEADERS += \
    include/myarithmetic.h \
    include/mycommand.h \
    include/myvisitor.h \
    include/network.h \
    include/read_xml_function.h \
    include/robot_datastruct.h

SOURCES += \
    course_b.cpp \
    src/myarithmetic.cpp \
    src/mycommand.cpp \
    src/myvisitor.cpp \
    src/network.cpp \
    src/read_xml_function.cpp
