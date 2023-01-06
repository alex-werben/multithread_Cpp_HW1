#!/usr/bin/env bash

#set -x
# if something will be wrong, exception shell stops
# set -e

path="./build/invoke"

output=$($path 0123)
if [[ $output == "0" ]]; then
  echo "OK"
else
  echo "FAILED"
fi

output=$($path 123 88)
if [[ $output == "Usage: ./<program> <some_input>" ]]; then
  echo "OK"
else
  echo "FAILED"
fi

output=$($path mad)
if [[ $output == "1" ]]; then
  echo "OK"
else
  echo "FAILED"
fi
