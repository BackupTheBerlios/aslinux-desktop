####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = poof2

## INCLUDES were found outside kdevelop specific part

poof2_SOURCES = dcopdemoiface_skel.cpp dcoper.cpp mainWin.ui main.cpp \
	dcopdemoiface.kidl
poof2_LDADD = -lkio $(LIB_KDEUI) $(LIB_KDECORE) $(LIB_QT) $(LIBSOCKET)


EXTRA_DIST = main.cpp poof2.cpp poof2.h lo16-app-poof2.png mainWin.ui dcoper.cpp dcoper.h dcopdemoiface.h dcopdemoiface_skel.cpp 

install-data-local:
	$(mkinstalldirs) $(kde_icondir)/locolor/16x16/apps/
	$(INSTALL_DATA) $(srcdir)/lo16-app-poof2.png $(kde_icondir)/locolor/16x16/apps/poof2.png

uninstall-local:
	-rm -f $(kde_icondir)/locolor/16x16/apps/poof2.png

####### kdevelop will overwrite this part!!! (end)############
# These paths are KDE specific. Use them:
# kde_appsdir         Where your application's menu entry (.desktop) should go to.
# kde_icondir         Where your icon should go to - better use KDE_ICON.
# kde_sounddir        Where your sounds should go to.
# kde_htmldir         Where your docs should go to. (contains lang subdirs)
# kde_datadir         Where you install application data. (Use a subdir)
# kde_locale          Where translation files should go to. (contains lang subdirs)
# kde_cgidir          Where cgi-bin executables should go to.
# kde_confdir         Where config files should go to (system-wide ones with default values).
# kde_mimedir         Where mimetypes .desktop files should go to.
# kde_servicesdir     Where services .desktop files should go to.
# kde_servicetypesdir Where servicetypes .desktop files should go to.
# kde_toolbardir      Where general toolbar icons should go to (deprecated, use KDE_ICON).
# kde_wallpaperdir    Where general wallpapers should go to.
# kde_templatesdir    Where templates for the "New" menu (Konqueror/KDesktop) should go to.
# kde_bindir          Where executables should go to. Use bin_PROGRAMS or bin_SCRIPTS.
# kde_libdir          Where shared libraries should go to. Use lib_LTLIBRARIES.
# kde_moduledir       Where modules (e.g. parts) should go to. Use kde_module_LTLIBRARIES.
# kde_styledir        Where Qt/KDE widget styles should go to (new in KDE 3).
# kde_designerdir     Where Qt Designer plugins should go to (new in KDE 3).

# set the include path for X, qt and KDE
INCLUDES= $(all_includes)

METASOURCES = AUTO

# the library search path. 
poof2_LDFLAGS = $(all_libraries) $(KDE_RPATH) -lkio

# Uncomment the following two lines if you add a ui.rc file for your application to make use of
# KDE?s XML GUI builing
#rcdir = $(kde_datadir)/poof2
#rc_DATA = poof2ui.rc

#WARNING: if you use a ui.rc file above, use:

# messages: rc.cpp

# instead of 

# messages:

messages: 
	LIST=`find . -name \*.h -o -name \*.hh -o -name \*.H -o -name \*.hxx -o -name \*.hpp -o -name \*.cpp -o -name \*.cc -o -name \*.cxx -o -name \*.ecpp -o -name \*.C`; \
	if test -n "$$LIST"; then \
	 $(XGETTEXT) $$LIST -o $(podir)/poof2.pot; \
	fi

pkgdata_SCRIPTS = libasinsfaz.sh
