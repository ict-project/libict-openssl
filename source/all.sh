#!/bin/bash
HEADER_NAME="all.hpp"

rm -f $HEADER_NAME

HEADER_LIST=`ls -1 *.hpp`
MACRO_DEF_STRING="_LIBICT_HEADER_${RANDOM}_${RANDOM}"

echo "#ifndef ${MACRO_DEF_STRING}" >> $HEADER_NAME
echo "#define ${MACRO_DEF_STRING}" >> $HEADER_NAME

for HEADER in $HEADER_LIST
do
    if [[ "$HEADER" != "test.hpp" && "$HEADER" != "$HEADER_NAME" ]]; then
        echo "#include \"$HEADER\"" >> $HEADER_NAME
    fi
done

echo "#endif" >> $HEADER_NAME
