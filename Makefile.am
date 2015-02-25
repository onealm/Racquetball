ACLOCAL_AMFLAGS= -I m4
noinst_HEADERS= BaseApplication.h Racquetball.h Ball.h PlayingRoom.h

bin_PROGRAMS= Racquetball
Racquetball_CPPFLAGS= -I$(top_srcdir)
Racquetball_SOURCES= BaseApplication.cpp Racquetball.cpp Ball.cpp PlayingRoom.cpp Player.cpp
Racquetball_CXXFLAGS= $(OGRE_CFLAGS) $(OIS_CFLAGS)
Racquetball_LDADD= $(OGRE_LIBS) $(OIS_LIBS)
Racquetball_LDFLAGS= -lOgreOverlay -lboost_system

EXTRA_DIST= buildit makeit
AUTOMAKE_OPTIONS= foreign
