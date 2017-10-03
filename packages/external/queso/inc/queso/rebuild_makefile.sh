#!/bin/sh

# This file was shamelessly stolen from the libmesh source tree
# See https://github.com/libMesh/libmesh

headers=`find ../../src -name "*.h" -a -not -name queso.h -a -not -name all.h -type f | grep -v 'ANN' | grep -v 'interface' | LC_COLLATE=POSIX sort`

cat <<EOF > Makefile.am
# Note - this file is automatically generated by $0 
# do not edit manually

#
# include the magic script!
EXTRA_DIST = rebuild_makefile.sh

BUILT_SOURCES =
EOF
for header_with_path in $headers ; do
  # Strip out path
  header=`basename $header_with_path`
  cat <<EOF >> Makefile.am
BUILT_SOURCES += $header
EOF
done

# Manually handle the auto-generated headers
cat <<EOF >> Makefile.am
BUILT_SOURCES += config_queso.h
BUILT_SOURCES += queso.h
EOF

cat <<EOF >> Makefile.am

DISTCLEANFILES = \$(BUILT_SOURCES)

EOF

# Now automatically handle our headers.
# Note:  $(AM_V_GEN) only works if AM_SILENT_RULES(yes) exists in configure.ac
#        and only works on autmake version 1.11 or greater.
cat <<EOF >> Makefile.am
#
# queso header rules
EOF
for header_with_path in $headers; do
  # Strip out path
  header=`basename $header_with_path`
  source=`echo $header_with_path | sed 's/..\/../$(top_srcdir)/'`
  cat <<EOF >> Makefile.am
$header: $source
	\$(AM_V_GEN)rm -f \$@ && \$(LN_S) \$< \$@
EOF
done

# Manually handle the auto-generated headers
cat <<EOF >> Makefile.am
config_queso.h: \$(top_builddir)/config_queso.h
	\$(AM_V_GEN)rm -f \$@ && \$(LN_S) \$< \$@
queso.h: \$(top_builddir)/src/core/inc/queso.h
	\$(AM_V_GEN)rm -f \$@ && \$(LN_S) \$< \$@
EOF
