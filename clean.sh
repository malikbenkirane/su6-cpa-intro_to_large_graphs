#!/bin/sh

# awk '{printf "%d %d\n%d %d\n", $1, $2, $2, $1}'

sed '/^#/d' \
	| awk '{if ($1 < $2) {print $1" "$2} else {print $2" "$1}}' \
	| sort -u
