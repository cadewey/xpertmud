#! /bin/sh
#
# cvs.sh
#
# This file contains support code from Makefile.common
# It defines a shell function for each known target
# and then does a case to call the correct function.

call_and_fix_autoconf()
{
  $AUTOCONF || exit 1
  if test -r configure.in.in ; then
    perl -pi -e "print \"if test \\\"x\\\$with_fast_perl\\\" = \\\"xyes\\\"; then\
    \\n  perl -i.bak \\\$ac_aux_dir/conf.change.pl \\\$CONFIG_STATUS\
    \\\\\\n    || mv \\\$CONFIG_STATUS.bak \\\$CONFIG_STATUS\
    \\n  rm -f \\\$CONFIG_STATUS.bak\\nfi\
    \\n\" if /^\\s*chmod\\s+.*\\+x\\s+.*CONFIG_STATUS/; s,^#line.*LINENO.*\$,/* \$& */, ;" configure
  fi
}

strip_makefile()
{
  if test -f $makefile_wo; then :; else
    perl -e '$in=0; while ( <> ) { $in = 1 if ($_=~ m/^if /); print $_ unless ($in); $in = 0 if ($_ =~ m/^endif/); }' < Makefile.am.in > $makefile_wo
  fi
}

check_autotool_versions()
{
AUTOCONF_VERSION=`$AUTOCONF --version | head -n 1`
case $AUTOCONF_VERSION in
  Autoconf*2.5* | autoconf*2.5* | autoconf*2.6*) : ;;
  "" )
    echo "*** AUTOCONF NOT FOUND!."
    echo "*** KDE requires autoconf 2.52, 2.53 or 2.54"
    exit 1
    ;;
  * )
    echo "*** YOU'RE USING $AUTOCONF_VERSION."
    echo "*** KDE requires autoconf 2.52, 2.53 or 2.54"
    exit 1
    ;;
esac
 
AUTOHEADER_VERSION=`$AUTOHEADER --version | head -n 1`
case $AUTOHEADER_VERSION in
  Autoconf*2.5* | autoheader*2.5* | autoheader*2.6*) : ;;
  "" )
    echo "*** AUTOHEADER NOT FOUND!."
    echo "*** KDE requires autoheader 2.52 or 2.53 (part of autoconf)"
    exit 1
    ;;
  * )
    echo "*** YOU'RE USING $AUTOHEADER_VERSION."
    echo "*** KDE requires autoheader 2.52 or 2.53 (part of autoconf)"
    exit 1
    ;;
esac

AUTOMAKE_STRING=`$AUTOMAKE --version | head -n 1`
case $AUTOMAKE_STRING in
  automake*1.5d* | automake*1.5* | automake*1.5-* )
    echo "*** YOU'RE USING $AUTOMAKE_STRING."
    echo "*** KDE requires automake 1.6.1 or newer"
    exit 1
    ;;
  automake*1.6.* | automake*1.7* | automake*1.8.* | automake*1.9* | automake*1.10*) : ;;
  "" )
    echo "*** AUTOMAKE NOT FOUND!."
    echo "*** KDE requires automake 1.6.1 or newer"
    exit 1
    ;;
  unsermake* ) :
    echo "*** YOU'RE USING UNSERMAKE."
    echo "*** GOOD LUCK!! :)"
    ;;
  * )
    echo "*** YOU'RE USING $AUTOMAKE_STRING."
    echo "*** KDE requires automake 1.6"
    exit 1
    ;;
esac
}

cvs()
{
check_autotool_versions
 
### Produce acinclude.m4
if grep '\$(top_srcdir)/acinclude.m4:' $makefile_am >/dev/null; then
  echo "*** Creating acinclude.m4"
  rm -f acinclude.m4 configure.files
  
  strip_makefile
  $MAKE -f $makefile_wo top_srcdir=. ./acinclude.m4
fi

### Make new subdirs and configure.in.
### The make calls could be optimized away here,
### with a little thought.
if test -r configure.in.in; then
    rm -f configure.in
    echo "*** Creating list of subdirectories"
    create_subdirs

    if test -r Makefile.am.in; then
        echo "*** Creating Makefile.am"
        if grep '\$(top_srcdir)/Makefile.am:' $makefile_am >/dev/null; then 
            strip_makefile
            $MAKE -f $makefile_wo top_srcdir=. ./Makefile.am || exit 1
        else
            Makefile_am
        fi
     fi
     echo "*** Creating configure.in"
     configure_files
     strip_makefile
     $MAKE -f $makefile_wo top_srcdir=. ./configure.in || exit 1
fi

echo "*** Creating aclocal.m4"
$ACLOCAL || exit 1
echo "*** Creating configure"
call_and_fix_autoconf

if egrep "^AM_CONFIG_HEADER" configure.in >/dev/null 2>&1; then
  echo "*** Creating config.h template"
  $AUTOHEADER || exit 1
fi

echo "*** Creating Makefile templates"
$AUTOMAKE || exit 1
if test -z "$UNSERMAKE"; then
  echo "*** Postprocessing Makefile templates"
  perl -w admin/am_edit || exit 1
fi

if egrep "^cvs-local:" $makefile_am >/dev/null; then \
  strip_makefile
  $MAKE -f $makefile_wo cvs-local top_srcdir=. || exit 1
fi

echo "*** Creating date/time stamp"
touch stamp-h.in

echo "*** Finished"
echo "    Don't forget to run ./configure"
echo "    If you haven't done so in a while, run ./configure --help"
}

dist()
{
check_autotool_versions

###
### First build all of the files necessary to do just "make"
###
if grep '\$(top_srcdir)/acinclude.m4:' $makefile_am >/dev/null; then
  strip_makefile
  $MAKE -f $makefile_wo top_srcdir=. ./acinclude.m4
fi
if test -r configure.in.in; then
  create_subdirs
  Makefile_am
  configure_files
  strip_makefile
  $MAKE -f $makefile_wo top_srcdir=. ./configure.in
fi
$ACLOCAL
$AUTOHEADER
$AUTOMAKE --foreign --include-deps
perl -w admin/am_edit
call_and_fix_autoconf
touch stamp-h.in
if grep "^cvs-local:" $makefile_am >/dev/null; then
  strip_makefile
  $MAKE -f $makefile_wo cvs-local top_srcdir=.
fi

###
### Then make messages
###
if test -d po; then
 LIST=`find ./po -name "*.po"`
 for i in $LIST; do
  file2=`echo $i | sed -e "s#\.po#\.gmo#"`
  msgfmt -o $file2 $i || touch $file2
 done
fi
if grep "^cvs-dist-local:" $makefile_am >/dev/null; then
  strip_makefile
  $MAKE -f $makefile_wo cvs-dist-local top_srcdir=.
fi
}

subdir_dist()
{
$ACLOCAL
$AUTOHEADER
$AUTOMAKE
perl -w ../admin/am_edit
call_and_fix_autoconf
touch stamp-h.in
}

configure_in()
{
rm -f configure.in configure.in.new
kde_use_qt_param=
test -f configure.files || { echo "need configure.files for configure.in"; exit 1; }
cat `fgrep -v "configure.in.bot" < configure.files | fgrep -v "configure.in.mid"` > configure.in.new
echo "KDE_CREATE_SUBDIRSLIST" >> configure.in.new
if test -f Makefile.am.in; then
  subdirs=`cat subdirs`
  for dir in $subdirs; do
    dir=`echo $dir | sed -e "s,[-+.],_,g"`
    echo "AM_CONDITIONAL($dir""_SUBDIR_included, test \"x\$$dir""_SUBDIR_included\" = xyes)" >> configure.in.new
  done
fi

echo "AC_CONFIG_FILES([ Makefile ])" >> configure.in.new
if test -n "$UNSERMAKE"; then
  echo "AC_CONFIG_FILES([ Makefile.rules ])" >> configure.in.new
  echo "AC_CONFIG_FILES([ Makefile.calls ])" >> configure.in.new
fi

if test -f inst-apps; then
    topleveldirs=`cat inst-apps`
else
    topleveldirs=
    for dir in `ls -1d * | sort`; do
	if test "$dir" != "debian" && test -d $dir; then
	    topleveldirs="$topleveldirs $dir"
	fi
    done
fi

for topleveldir in $topleveldirs; do 
  if test -f $topleveldir/configure.in; then
	continue
  fi
  if test -f $topleveldir/Makefile.am; then :; else
	continue
  fi

  mfs=`find $topleveldir -name Makefile.am -print | fgrep -v "/." | \
       sed -e 's#\./##; s#/Makefile.am$##' | sort | sed -e 's#$#/Makefile#'`
  for i in $mfs; do
     echo "AC_CONFIG_FILES([ $i ])" >> configure.in.new
     if test -n "$UNSERMAKE"; then
        echo "AC_CONFIG_FILES([ $i.rules ])" >> configure.in.new
	echo "AC_CONFIG_FILES([ $i.calls ])" >> configure.in.new
     fi
  done
done

files=`cat configure.files`
list=`egrep '^dnl AC_OUTPUT\(.*\)' $files | sed -e "s#^.*dnl AC_OUTPUT(\(.*\))#\1#"`
for file in $list; do 
    echo "AC_CONFIG_FILES([ $file ])" >>  configure.in.new
done

if test -n "$UNSERMAKE"; then
  echo "AC_CONFIG_FILES([ MakeVars ])" >> configure.in.new
fi

midfiles=`cat configure.files | fgrep "configure.in.mid"`
test -n "$midfiles" && cat $midfiles >> configure.in.new

echo "AC_OUTPUT" >> configure.in.new
modulename=
if test -f configure.in.in; then
   if head -n 2 configure.in.in | egrep "^#MIN_CONFIG\(.*\)$" > /dev/null; then
      kde_use_qt_param=`cat configure.in.in | sed -n -e "s/#MIN_CONFIG(\(.*\))/\1/p"`
   fi
   if head -n 2 configure.in.in | egrep "^#MIN_CONFIG" > /dev/null; then
      line=`grep "^AM_INIT_AUTOMAKE(" configure.in.in`
      if test -n "$line"; then
	  modulename=`echo $line | sed -e "s#AM_INIT_AUTOMAKE(\([^,]*\),.*#\1#"`
	  VERSION=`echo $line | sed -e "s#AM_INIT_AUTOMAKE([^,]*, *\([^)]*\)).*#\1#"`
      fi
      sed -e "s#AM_INIT_AUTOMAKE([^@].*#dnl PACKAGE set before#" \
          configure.in.new > configure.in && mv configure.in configure.in.new
   fi
fi
if test -z "$VERSION" || test "$VERSION" = "@VERSION@"; then
     VERSION="\"3.1.0\""
fi
if test -z "$modulename" || test "$modulename" = "@MODULENAME@"; then
   modulename=`pwd`; 
   modulename=`basename $modulename`
   esc_VERSION=`echo $VERSION | sed -e "s#[^.0-9a-zA-Z]##g"`
   modulename=`echo $modulename | sed -e "s#-$esc_VERSION##"`   

fi
if test -n "$kde_use_qt_param"; then
      sed -e "s#^dnl KDE_USE_QT#KDE_USE_QT($kde_use_qt_param)#" \
      	configure.in.new > configure.in && mv configure.in configure.in.new
fi
sed -e "s#@MODULENAME@#$modulename#" configure.in.new |
	sed -e "s#@VERSION@#$VERSION#" > configure.in
botfiles=`cat configure.files | egrep "configure.in.bot"`
test -n "$botfiles" && cat $botfiles >> configure.in
cat $admindir/configure.in.bot.end >> configure.in
rm -f configure.in.new
}

configure_files()
{
admindir=NO
for i in . .. ../.. ../../..; do
  if test -x $i/admin; then admindir=$i/admin; break; fi
done
rm -f configure.files
touch configure.files
if test -f configure.in.in && head -n 2 configure.in.in | grep "^#MIN_CONFIG" > /dev/null; then
	echo $admindir/configure.in.min >> configure.files
fi
test -f configure.in.in && echo configure.in.in >> configure.files
# we collect files in the subdirs and do some sorting tricks, so subsubdirs come after subdirs
if test -f inst-apps; then
   inst=`cat inst-apps`
   list=""
   for i in $inst; do
      list="$list `find $i/ -name "configure.in.in" -o -name "configure.in.bot" -o -name "configure.in.mid" | \
		sed -e "s,/configure,/aaaconfigure," | sort | sed -e "s,/aaaconfigure,/configure,"`"
   done
else
   list=`find . -name "configure.in.in" -o -name "configure.in.bot" -o -name "configure.in.mid" | \
		sed -e "s,/configure,/aaaconfigure," | sort | sed -e "s,/aaaconfigure,/configure,"`
fi
for i in $list; do if test -f $i && test `dirname $i` != "." ; then
  echo $i >> configure.files
fi; done
test -f configure.in.mid && echo configure.in.mid >> configure.files
test -f configure.in.bot && echo configure.in.bot >> configure.files
}

create_subdirs()
{
if grep '\$(top_srcdir)/subdirs:' $makefile_am >/dev/null; then 
    # as many modules contain rules to create subdirs without any
    # dependencies make won't create it unless there is no file.
    # so we check if that's a dummy rule or one that works
    rm -f subdirs.cvs.sh.$$
    if test -f subdirs; then
	mv subdirs subdirs.cvs.sh.$$
    fi
    strip_makefile
    $MAKE -f $makefile_wo top_srcdir=. ./subdirs || exit 1
    if test -f subdirs.cvs.sh.$$; then
	if test -s subdirs; then
	    rm subdirs.cvs.sh.$$ 
	else
	    mv subdirs.cvs.sh.$$ subdirs
	fi
    fi
else
    subdirs
fi
}

subdirs()
{
dirs=
idirs=
if test -f inst-apps; then
   idirs=`cat inst-apps`
else
   idirs=`ls -1 | sort`
fi

compilefirst=`sed -ne 's#^COMPILE_FIRST[ ]*=[ ]*##p' $makefile_am | head -n 1`
compilelast=`sed -ne 's#^COMPILE_LAST[ ]*=[ ]*##p' $makefile_am | head -n 1`
for i in $idirs; do
    if test -f $i/Makefile.am; then
       case " $compilefirst $compilelast " in
         *" $i "*) ;;
         *) dirs="$dirs $i"
       esac
    fi
done

: > ./_SUBDIRS

for d in $compilefirst; do
   echo $d >> ./_SUBDIRS
done

(for d in $dirs; do 
   list=`sed -ne "s#^COMPILE_BEFORE_$d""[ ]*=[ ]*##p" $makefile_am | head -n 1`
   for s in $list; do
      echo $s $d
   done
   list=`sed -ne "s#^COMPILE_AFTER_$d""[ ]*=[ ]*##p" $makefile_am | head -n 1`
   for s in $list; do
      echo $d $s
   done
   echo $d $d
done ) | tsort >> ./_SUBDIRS

for d in $compilelast; do
   echo $d >> ./_SUBDIRS
done

if test -r subdirs && cmp -s subdirs _SUBDIRS; then
    rm -f _SUBDIRS
fi
test -r _SUBDIRS && mv _SUBDIRS subdirs || true
}

Makefile_am()
{
if test -f Makefile.am.in; then
  compilefirst=`sed -ne 's#^COMPILE_FIRST[ ]*=[ ]*##p' $makefile_am | head -n 1`
  compilelast=`sed -ne 's#^COMPILE_LAST[ ]*=[ ]*##p' $makefile_am | head -n 1`

  idirs=
  dirs=
  if test -f inst-apps; then
     idirs=`cat inst-apps`
  else
     idirs=`cat subdirs`
  fi
  for i in $idirs; do
    case " $compilefirst $compilelast " in
      *" $i "*) ;;
      *) dirs="$dirs $i"
    esac
  done

  if test -n "$UNSERMAKE"; then
    cp Makefile.am.in Makefile.am
    chmod u+w Makefile.am
    topsubdirs=
    for i in $compilefirst $dirs $compilelast; do
       vari=`echo $i | sed -e "s,[-+],_,g"`
       echo "if $vari""_SUBDIR_included" >> Makefile.am
       echo "$vari""_SUBDIR=$i" >> Makefile.am
       echo "endif" >> Makefile.am
       topsubdirs="$topsubdirs \$($vari""_SUBDIR)"
    done
    echo "SUBDIRS=$topsubdirs" >> Makefile.am
  else
    cat Makefile.am.in | \
        sed -e 's,^\s*\(COMPILE_BEFORE.*\),# \1,' | \
        sed -e 's,^\s*\(COMPILE_AFTER.*\),# \1,' > Makefile.am
    echo "SUBDIRS="'$(TOPSUBDIRS)' >> Makefile.am
  fi
fi
}

cvs_clean()
{
if test -d CVS; then :; else
  echo "You don't have a toplevel CVS directory."
  echo "You most certainly didn't use cvs to get these sources."
  echo "But this function depends on cvs's information."
  exit 1
fi
perl $admindir/cvs-clean.pl
}

package_merge()
{
catalogs=$POFILES
for cat in $catalogs; do
  msgmerge -o $cat.new $cat $PACKAGE.pot
  if test -s $cat.new; then
    grep -v "\"POT-Creation" $cat.new > $cat.new.2
    grep -v "\"POT-Creation" $cat >> $cat.new.1
    if diff $cat.new.1 $cat.new.2; then
	rm $cat.new
    else
	mv $cat.new $cat
    fi
    rm -f $cat.new.1 $cat.new.2
  fi
done
}

package_messages()
{
rm -rf po.backup
mkdir po.backup

for i in `ls -1 po/*.pot 2>/dev/null | sed -e "s#po/##"`; do
  egrep -v '^#([^:]|$)' po/$i | egrep '^.*[^ ]+.*$' | grep -v "\"POT-Creation" > po.backup/$i
  cp po/$i po.backup/backup_$i
  touch -r po/$i po.backup/backup_$i
  rm po/$i
done

podir=${podir:-$PWD/po}
files=`find . -name Makefile.am | xargs egrep -l '^messages:' `
dirs=`for i in $files; do echo \`dirname $i\`; done`
tmpname="$PWD/messages.log"
if test -z "$EXTRACTRC"; then EXTRACTRC=extractrc ; fi
if test -z "$PREPARETIPS"; then PREPARETIPS=preparetips ; fi
export EXTRACTRC PREPARETIPS

for subdir in $dirs; do
  test -z "$VERBOSE" || echo "Making messages in $subdir"
  (cd $subdir
   if test -n "`grep -e '^messages:.*rc.cpp' Makefile.am`"; then
	$EXTRACTRC *.rc *.ui > rc.cpp
   else
	candidates=`ls -1 *.rc *.ui 2>/dev/null`
	if test -n "$candidates"; then
	    echo "$subdir has *.rc or *.ui files, but not correct messages line"
	fi
   fi
   if test -n "`grep -r KAboutData *.c* *.C* 2>/dev/null`"; then
	echo -e 'i18n("_: NAME OF TRANSLATORS\\n"\n"Your names")\ni18n("_: EMAIL OF TRANSLATORS\\n"\n"Your emails")' > _translatorinfo.cpp
   else echo " " > _translatorinfo.cpp
   fi
   perl -e '$mes=0; while (<STDIN>) { next if (/^(if|else|endif)\s/); if (/^messages:/) { $mes=1; print $_; next; } if ($mes) { if (/$\\(XGETTEXT\)/ && / -o/) { s/ -o \$\(podir\)/ _translatorinfo.cpp -o \$\(podir\)/ } print $_; } else { print $_; } }' < Makefile.am | egrep -v '^include ' > _transMakefile

   $MAKE -s -f _transMakefile podir=$podir EXTRACTRC="$EXTRACTRC" PREPARETIPS="$PREPARETIPS" \
	XGETTEXT="${XGETTEXT:-xgettext} -C -ki18n -ktr2i18n -kI18N_NOOP -ktranslate -kaliasLocale -x ${includedir:-${KDEDIR:-/usr/local/kde}/include}/kde.pot" \
	messages 
   exit_code=$?
   if test "$exit_code" != 0; then
       echo "make exit code: $exit_code"
   fi
   ) 2>&1 | grep -v '^make\[1\]' > $tmpname
   test -s $tmpname && { echo $subdir ; cat "$tmpname"; }
   test -f $subdir/rc.cpp && rm -f $subdir/rc.cpp
   rm -f $subdir/_translatorinfo.cpp
   rm -f $subdir/_transMakefile
done
rm -f $tmpname
for i in `ls -1 po.backup/*.pot 2>/dev/null | sed -e "s#po.backup/##" | egrep -v '^backup_'`; do
  test -f po/$i || echo "disappeared: $i"
done
for i in `ls -1 po/*.pot 2>/dev/null | sed -e "s#po/##"`; do
   msgmerge -q -o po/$i po/$i po/$i
   egrep -v '^#([^:]|$)' po/$i | egrep '^.*[^ ]+.*$' | grep -v "\"POT-Creation" > temp.pot
  if test -f po.backup/$i && test -n "`diff temp.pot po.backup/$i`"; then
	echo "will update $i"
	msgmerge -q po.backup/backup_$i po/$i > temp.pot
	mv temp.pot po/$i
  else
    if test -f po.backup/backup_$i; then
      test -z "$VERBOSE" || echo "I'm restoring $i"
      mv po.backup/backup_$i po/$i
      rm po.backup/$i
    else
      echo "will add $i"
    fi
  fi
done
rm -f temp.pot
rm -rf po.backup
}

unset CDPATH
admindir=`echo "$0" | sed 's%[\\/][^\\/][^\\/]*$%%'`
test "x$admindir" = "x$0" && admindir=.

test "x$MAKE" = x && MAKE=make
makefile_am=Makefile.am
makefile_wo=Makefile.am
if test -f Makefile.am.in; then
  makefile_am=Makefile.am.in
  makefile_wo=Makefile.am.in.wo
fi

# Suck in the AUTOCONF detection code
. $admindir/detect-autoconf.sh

###
### Main
###

arg=`echo $1 | tr '\-.' __`
case $arg in
  cvs | dist | subdir_dist | configure_in | configure_files | subdirs | \
  cvs_clean | package_merge | package_messages | Makefile_am ) $arg ;;
  configure ) call_and_fix_autoconf ;;
  * ) echo "Usage: cvs.sh <target>"
      echo "Target can be one of:"
      echo "    cvs cvs-clean dist"
      echo "    configure.in configure.files"
      echo "    package-merge package-messages"
      echo ""
      echo "Usage: anything but $1"
      exit 1 ;;
esac

if test -f Makefile.am.in.wo; then
  rm Makefile.am.in.wo
fi

exit 0
