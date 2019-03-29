TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_EXTRA_TARGETS += before_build makefilehook

makefilehook.target = $(MAKEFILE)
makefilehook.depends = .beforebuild

PRE_TARGETDEPS += .beforebuild

before_build.target = .beforebuild
before_build.depends = FORCE
before_build.commands = chcp 1251

SOURCES += \
        main.cpp

HEADERS += \
    vector3d.h \
    vector4d.h \
    line.h \
    matrix3d.h \
    matrix4d.h \
    plane.h \
    point3d.h \
    quaternion.h \
    transform4d.h

