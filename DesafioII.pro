QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        entidades/Equipo.cpp \
        entidades/Jugador.cpp \
        estadisticas/EstadisticasEquipo.cpp \
        estadisticas/EstadisticasJugador.cpp \
        main.cpp \
        partido/EstPartidoEquipo.cpp \
        partido/JugadorConvocado.cpp \
        partido/Partido.cpp \
        torneo/EntradaTabla.cpp \
        torneo/Etapa.cpp \
        torneo/Grupo.cpp \
        torneo/TablaClasificacion.cpp \
        torneo/Torneo.cpp \
        utils/GestorArchivos.cpp \
        utils/MedidorRecursos.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    entidades/Equipo.h \
    entidades/Jugador.h \
    estadisticas/EstadisticasEquipo.h \
    estadisticas/EstadisticasJugador.h \
    partido/EstPartidoEquipo.h \
    partido/JugadorConvocado.h \
    partido/Partido.h \
    torneo/EntradaTabla.h \
    torneo/Etapa.h \
    torneo/Grupo.h \
    torneo/TablaClasificacion.h \
    torneo/Torneo.h \
    utils/GestorArchivos.h \
    utils/Lista.h \
    utils/MedidorRecursos.h
