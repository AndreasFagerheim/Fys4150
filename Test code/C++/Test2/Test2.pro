TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt




LIBS += \
    -LMacintosh HD\armadillo-9.700.2\examples\lib_win64 \
    -llapack_win64_MT \
    -lblas_win64_MT
SOURCES += \
        main.cpp

INCLUDEPATH += /usr/local/Cellar/armadillo/9.700.2/include/
LIBS += -L/usr/local/Cellar/armadillo/9.700.2/lib/ -larmadillo
