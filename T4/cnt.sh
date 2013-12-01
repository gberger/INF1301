#!/bin/sh

cat *.C | grep 'CNT_CONTAR' | sed 's/[^\"]*\"\s?([^\"]*)\s?\"[^\"]*/\1/gip' -r | uniq
