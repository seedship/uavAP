# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = uavAP

HEADERS += $$system(find -name "*.h")
HEADERS += $$system(find -name "*.hpp")
HEADERS += $$system(find -name "CMakeLists.txt")

SOURCES += $$system(find -name "*.c")
SOURCES += $$system(find -name "*.cpp")
SOURCES += $$system(find -name "CMakeLists.txt")

OTHER_FILES += $$system(find -type f)

#DEFINES =
