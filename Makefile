#############################################################################
# Makefile for building: backupsoft
# Generated by qmake (2.01a) (Qt 4.7.1) on: Fri Nov 12 07:42:15 2010
# Project:  backupsoft.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile backupsoft.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/local/qt-4.7.1/mkspecs/linux-g++ -I. -I/usr/local/qt-4.7.1/include/QtCore -I/usr/local/qt-4.7.1/include/QtGui -I/usr/local/qt-4.7.1/include -I.
LINK          = g++
LFLAGS        = -Wl,-O1 -Wl,-rpath,/usr/local/qt-4.7.1/lib
LIBS          = $(SUBLIBS)  -L/usr/local/qt-4.7.1/lib -lQtGui -L/usr/local/qt-4.7.1/lib -L/usr/X11R6/lib -ljpeg -pthread -pthread -pthread -lpng -pthread -lgobject-2.0 -lSM -lICE -lXrender -lfontconfig -lfreetype -lXext -lX11 -lQtCore -lz -lm -ldl -pthread -lgthread-2.0 -lrt -lglib-2.0 -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = mainwindow.cpp \
		settings.cpp \
		profilemanager.cpp \
		alertwindow.cpp \
		helper.cpp \
		backup.cpp \
		about.cpp moc_mainwindow.cpp \
		moc_settings.cpp \
		moc_profilemanager.cpp \
		moc_alertwindow.cpp \
		moc_backup.cpp \
		moc_about.cpp
OBJECTS       = mainwindow.o \
		settings.o \
		profilemanager.o \
		alertwindow.o \
		helper.o \
		backup.o \
		about.o \
		moc_mainwindow.o \
		moc_settings.o \
		moc_profilemanager.o \
		moc_alertwindow.o \
		moc_backup.o \
		moc_about.o
DIST          = /usr/local/qt-4.7.1/mkspecs/common/g++.conf \
		/usr/local/qt-4.7.1/mkspecs/common/unix.conf \
		/usr/local/qt-4.7.1/mkspecs/common/linux.conf \
		/usr/local/qt-4.7.1/mkspecs/qconfig.pri \
		/usr/local/qt-4.7.1/mkspecs/features/qt_functions.prf \
		/usr/local/qt-4.7.1/mkspecs/features/qt_config.prf \
		/usr/local/qt-4.7.1/mkspecs/features/exclusive_builds.prf \
		/usr/local/qt-4.7.1/mkspecs/features/default_pre.prf \
		/usr/local/qt-4.7.1/mkspecs/features/release.prf \
		/usr/local/qt-4.7.1/mkspecs/features/default_post.prf \
		/usr/local/qt-4.7.1/mkspecs/features/static.prf \
		/usr/local/qt-4.7.1/mkspecs/features/warn_on.prf \
		/usr/local/qt-4.7.1/mkspecs/features/qt.prf \
		/usr/local/qt-4.7.1/mkspecs/features/unix/thread.prf \
		/usr/local/qt-4.7.1/mkspecs/features/moc.prf \
		/usr/local/qt-4.7.1/mkspecs/features/resources.prf \
		/usr/local/qt-4.7.1/mkspecs/features/uic.prf \
		/usr/local/qt-4.7.1/mkspecs/features/yacc.prf \
		/usr/local/qt-4.7.1/mkspecs/features/lex.prf \
		/usr/local/qt-4.7.1/mkspecs/features/include_source_dir.prf \
		backupsoft.pro
QMAKE_TARGET  = backupsoft
DESTDIR       = 
TARGET        = backupsoft

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: backupsoft.pro  /usr/local/qt-4.7.1/mkspecs/linux-g++/qmake.conf /usr/local/qt-4.7.1/mkspecs/common/g++.conf \
		/usr/local/qt-4.7.1/mkspecs/common/unix.conf \
		/usr/local/qt-4.7.1/mkspecs/common/linux.conf \
		/usr/local/qt-4.7.1/mkspecs/qconfig.pri \
		/usr/local/qt-4.7.1/mkspecs/features/qt_functions.prf \
		/usr/local/qt-4.7.1/mkspecs/features/qt_config.prf \
		/usr/local/qt-4.7.1/mkspecs/features/exclusive_builds.prf \
		/usr/local/qt-4.7.1/mkspecs/features/default_pre.prf \
		/usr/local/qt-4.7.1/mkspecs/features/release.prf \
		/usr/local/qt-4.7.1/mkspecs/features/default_post.prf \
		/usr/local/qt-4.7.1/mkspecs/features/static.prf \
		/usr/local/qt-4.7.1/mkspecs/features/warn_on.prf \
		/usr/local/qt-4.7.1/mkspecs/features/qt.prf \
		/usr/local/qt-4.7.1/mkspecs/features/unix/thread.prf \
		/usr/local/qt-4.7.1/mkspecs/features/moc.prf \
		/usr/local/qt-4.7.1/mkspecs/features/resources.prf \
		/usr/local/qt-4.7.1/mkspecs/features/uic.prf \
		/usr/local/qt-4.7.1/mkspecs/features/yacc.prf \
		/usr/local/qt-4.7.1/mkspecs/features/lex.prf \
		/usr/local/qt-4.7.1/mkspecs/features/include_source_dir.prf \
		/usr/local/qt-4.7.1/lib/libQtGui.prl \
		/usr/local/qt-4.7.1/lib/libQtCore.prl
	$(QMAKE) -o Makefile backupsoft.pro
/usr/local/qt-4.7.1/mkspecs/common/g++.conf:
/usr/local/qt-4.7.1/mkspecs/common/unix.conf:
/usr/local/qt-4.7.1/mkspecs/common/linux.conf:
/usr/local/qt-4.7.1/mkspecs/qconfig.pri:
/usr/local/qt-4.7.1/mkspecs/features/qt_functions.prf:
/usr/local/qt-4.7.1/mkspecs/features/qt_config.prf:
/usr/local/qt-4.7.1/mkspecs/features/exclusive_builds.prf:
/usr/local/qt-4.7.1/mkspecs/features/default_pre.prf:
/usr/local/qt-4.7.1/mkspecs/features/release.prf:
/usr/local/qt-4.7.1/mkspecs/features/default_post.prf:
/usr/local/qt-4.7.1/mkspecs/features/static.prf:
/usr/local/qt-4.7.1/mkspecs/features/warn_on.prf:
/usr/local/qt-4.7.1/mkspecs/features/qt.prf:
/usr/local/qt-4.7.1/mkspecs/features/unix/thread.prf:
/usr/local/qt-4.7.1/mkspecs/features/moc.prf:
/usr/local/qt-4.7.1/mkspecs/features/resources.prf:
/usr/local/qt-4.7.1/mkspecs/features/uic.prf:
/usr/local/qt-4.7.1/mkspecs/features/yacc.prf:
/usr/local/qt-4.7.1/mkspecs/features/lex.prf:
/usr/local/qt-4.7.1/mkspecs/features/include_source_dir.prf:
/usr/local/qt-4.7.1/lib/libQtGui.prl:
/usr/local/qt-4.7.1/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile backupsoft.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/backupsoft1.0.0 || $(MKDIR) .tmp/backupsoft1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/backupsoft1.0.0/ && $(COPY_FILE) --parents mainwindow.h settings.h profilemanager.h alertwindow.h helper.h backup.h about.h .tmp/backupsoft1.0.0/ && $(COPY_FILE) --parents mainwindow.cpp settings.cpp profilemanager.cpp alertwindow.cpp helper.cpp backup.cpp about.cpp .tmp/backupsoft1.0.0/ && $(COPY_FILE) --parents deutsch.ts .tmp/backupsoft1.0.0/ && (cd `dirname .tmp/backupsoft1.0.0` && $(TAR) backupsoft1.0.0.tar backupsoft1.0.0 && $(COMPRESS) backupsoft1.0.0.tar) && $(MOVE) `dirname .tmp/backupsoft1.0.0`/backupsoft1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/backupsoft1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_settings.cpp moc_profilemanager.cpp moc_alertwindow.cpp moc_backup.cpp moc_about.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_settings.cpp moc_profilemanager.cpp moc_alertwindow.cpp moc_backup.cpp moc_about.cpp
moc_mainwindow.cpp: helper.h \
		mainwindow.h
	/usr/local/qt-4.7.1/bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_settings.cpp: helper.h \
		settings.h
	/usr/local/qt-4.7.1/bin/moc $(DEFINES) $(INCPATH) settings.h -o moc_settings.cpp

moc_profilemanager.cpp: helper.h \
		profilemanager.h
	/usr/local/qt-4.7.1/bin/moc $(DEFINES) $(INCPATH) profilemanager.h -o moc_profilemanager.cpp

moc_alertwindow.cpp: alertwindow.h
	/usr/local/qt-4.7.1/bin/moc $(DEFINES) $(INCPATH) alertwindow.h -o moc_alertwindow.cpp

moc_backup.cpp: helper.h \
		backup.h
	/usr/local/qt-4.7.1/bin/moc $(DEFINES) $(INCPATH) backup.h -o moc_backup.cpp

moc_about.cpp: about.h
	/usr/local/qt-4.7.1/bin/moc $(DEFINES) $(INCPATH) about.h -o moc_about.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

mainwindow.o: mainwindow.cpp mainwindow.h \
		helper.h \
		settings.h \
		profilemanager.h \
		alertwindow.h \
		backup.h \
		about.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

settings.o: settings.cpp mainwindow.h \
		helper.h \
		settings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o settings.o settings.cpp

profilemanager.o: profilemanager.cpp profilemanager.h \
		helper.h \
		alertwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o profilemanager.o profilemanager.cpp

alertwindow.o: alertwindow.cpp alertwindow.h \
		profilemanager.h \
		helper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o alertwindow.o alertwindow.cpp

helper.o: helper.cpp helper.h \
		alertwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o helper.o helper.cpp

backup.o: backup.cpp backup.h \
		helper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o backup.o backup.cpp

about.o: about.cpp about.h \
		alertwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o about.o about.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_settings.o: moc_settings.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_settings.o moc_settings.cpp

moc_profilemanager.o: moc_profilemanager.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_profilemanager.o moc_profilemanager.cpp

moc_alertwindow.o: moc_alertwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_alertwindow.o moc_alertwindow.cpp

moc_backup.o: moc_backup.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_backup.o moc_backup.cpp

moc_about.o: moc_about.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_about.o moc_about.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
