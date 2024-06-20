#!/bin/bash

# Description: Deletes every .log file inside test/ directory

# Get script directory
directory=$(dirname "$0")
chmod -R +x $directory
cd $directory

find . -type f -name "*.log" -delete