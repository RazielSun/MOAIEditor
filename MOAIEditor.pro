TARGET = MOAIEditor
TEMPLATE = app

QT += core gui opengl widgets

win32 {
}
unix:!macx {
}
macx {
}

CONFIG += box2d spine audiosampler untz particles

LIBS += -L"$$PWD/libs/lib" -lmoai-core -lmoai-crypto -lmoai-http-client -lmoai-sim -lmoai-util
LIBS += -L"$$PWD/libs/lib" -lluacrypto -lluacurl -lluafilesystem -lliblua-static -lluasocket -lluasql -lmoai-luaext
LIBS += -L"$$PWD/libs/lib" -lssl -ltinyxml -lwebp
LIBS += -L"$$PWD/libs/lib" -ltess -lvorbis -lSDL2main  -lsfmt -ltlsf -lSDL2 -lglew -lcurl -ljansson -lcrypto -lcontrib -logg -lexpat -lmongoose  
LIBS += -L"$$PWD/libs/lib" -lsqlite3
LIBS += -L"$$PWD/libs/lib" -lfreetype
LIBS += -L"$$PWD/libs/lib" -lpng -ljpg
LIBS += -L"$$PWD/libs/lib" -lzlcore -lzlib -lzlcrypto -lzlvfs

INCLUDEPATH +=	. \
				src \
				src/Widgets \
				libs/include \
				resources/ui \

box2d {
	LIBS += -L"$$PWD/libs/lib" -lbox2d -lmoai-box2d
}

spine {
	LIBS += -L"$$PWD/libs/lib" -lspine -lmoai-spine
}

audiosampler {
	LIBS += -L"$$PWD/libs/lib" -lmoai-audiosampler
}
untz {
    LIBS += -framework AudioUnit -framework AudioToolbox -framework CoreFoundation
    LIBS += -L"$$PWD/libs/lib" -luntz -lmoai-untz
    macx {
    }
}

particles {
	INCLUDEPATH += src/particle

	HEADERS += src/particle/ParticlePresets.h

	SOURCES += src/particle/ParticlePresets.cpp
}


HEADERS +=	src/Widgets/*.h \
			src/host-modules/*.h \
			libs/include/* \

SOURCES += 	src/*.cpp \
			src/Widgets/*.cpp \
			src/host-modules/*.cpp \

RESOURCES = resources/images.qrc

FORMS    += resources/ui/*.ui

