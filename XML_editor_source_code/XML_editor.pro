QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Compress_Decompress/huffman.cpp \
    Compress_Decompress/huffman_compress.cpp \
    Compress_Decompress/huffman_decompress.cpp \
    Formating/Formating.cpp \
    GUI_tabs/check/Stack.cpp \
    GUI_tabs/check/check.cpp \
    GUI_tabs/check/convertion.cpp \
    GUI_tabs/compress.cpp \
    GUI_tabs/convert_to_json.cpp \
    GUI_tabs/correct.cpp \
    GUI_tabs/formatter.cpp \
    GUI_tabs/inputfile.cpp \
    GUI_tabs/minifing.cpp \
    Minify/Minify.cpp \
    Syntax_Highlight/jshighlighter.cpp \
    Syntax_Highlight/xmlsyntaxhighlighter.cpp \
    XML_to_JSON/Node.cpp \
    XML_to_JSON/tree.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Compress_Decompress/huffman.h \
    Compress_Decompress/huffman_compress.h \
    Compress_Decompress/huffman_decompress.h \
    Formating/Formating.h \
    GUI_tabs/check/check.h \
    GUI_tabs/check/convertion.h \
    GUI_tabs/check/stack.h \
    GUI_tabs/compress.h \
    GUI_tabs/convert_to_json.h \
    GUI_tabs/correct.h \
    GUI_tabs/formatter.h \
    GUI_tabs/inputfile.h \
    GUI_tabs/minifing.h \
    Minify/Minify.h \
    Syntax_Highlight/jshighlighter.h \
    Syntax_Highlight/xmlsyntaxhighlighter.h \
    XML_to_JSON/Node.hpp \
    XML_to_JSON/tree.hpp \
    mainwindow.h

FORMS += \
    GUI_tabs/compress.ui \
    GUI_tabs/convert_to_json.ui \
    GUI_tabs/correct.ui \
    GUI_tabs/formatter.ui \
    GUI_tabs/inputfile.ui \
    GUI_tabs/minifing.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recource.qrc
RC_ICONS = XML_edior.ico

