#!/bin/bash
HEADER_NAME="info.hpp"
SOURCE_NAME="info.cpp"
LIBRARY_NAME="$1"

rm -f $HEADER_NAME $SOURCE_NAME

MACRO_DEF_STRING="_LIBICT_INFO_HEADER_${RANDOM}_${RANDOM}"
FIRST_LINE="static char out[]={"
LAST_LINE=",0x00};return(out);"

echo "#ifndef ${MACRO_DEF_STRING}" >> $HEADER_NAME
echo "#define ${MACRO_DEF_STRING}" >> $HEADER_NAME
echo "namespace ict { namespace ${LIBRARY_NAME} {" >> $HEADER_NAME
echo "  const char * getVersion();" >> $HEADER_NAME
echo "  const char * getLicense();" >> $HEADER_NAME
echo "  const char * getName();" >> $HEADER_NAME
echo "} }" >> $HEADER_NAME
echo "#endif" >> $HEADER_NAME

echo "#include \"info.hpp\"" >> $SOURCE_NAME
echo "namespace ict { namespace ${LIBRARY_NAME} {" >> $SOURCE_NAME

echo "const char * getVersion(){" >> $SOURCE_NAME
echo "$FIRST_LINE" >> $SOURCE_NAME
git describe | xxd -i  >> $SOURCE_NAME
echo "$LAST_LINE" >> $SOURCE_NAME
echo "}" >> $SOURCE_NAME

echo "const char * getLicense(){" >> $SOURCE_NAME
echo "$FIRST_LINE" >> $SOURCE_NAME
cat ../LICENSE | xxd -i  >> $SOURCE_NAME
echo "$LAST_LINE" >> $SOURCE_NAME
echo "}" >> $SOURCE_NAME

echo "const char * getName(){" >> $SOURCE_NAME
echo "$FIRST_LINE" >> $SOURCE_NAME
echo "libict-${LIBRARY_NAME}" | xxd -i  >> $SOURCE_NAME
echo "$LAST_LINE" >> $SOURCE_NAME
echo "}" >> $SOURCE_NAME

echo "} }" >> $SOURCE_NAME