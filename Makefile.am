noinst_HEADERS= BaseApplication.h Racquetball.h Ball.h PlayingRoom.h Player.h Sound.h NetManager.h

bin_PROGRAMS= Racquetball
Racquetball_CPPFLAGS= -I$(top_srcdir)
Racquetball_SOURCES= BaseApplication.cpp Racquetball.cpp Ball.cpp PlayingRoom.cpp Player.cpp Sound.cpp NetManager.cpp
Racquetball_CXXFLAGS= $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS)
Racquetball_LDADD= $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS)
Racquetball_LDFLAGS= -lOgreOverlay -lboost_system -lSDL -lSDL_mixer -lSDL_net

EXTRA_DIST= buildit makeit
AUTOMAKE_OPTIONS= foreign
