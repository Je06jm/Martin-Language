#!/bin/python3

from glob import glob
from platform import platform
from threading import Thread, Lock
from json import loads as json_loads
from os import cpu_count

# Try to read build settings
conf = None
try:
    file = open("build.json", "r")
    conf = json_loads(file.read())
    file.close()

except:
    print("Cannot open config file build.json")
    quit(0)

# Read the database

# A convenient place to store our build settings
settings = {
    # Can be windows or posix
    "platform": "unknown",
    # Can be msbuild or clang-gcc
    "compiler": "unknown",
    "debug": False,
    "tests": False,
    "threads": cpu_count() - 1,
    "clean": False
}

# Parse command line for build settings

# Check to make sure that settings is in a valid state
if not (settings["platform"] in ["windows", "posix"]):
    print("Unknown platform: " + settings["platform"])
    quit(0)

if not (settings["compiler"] in ["msbuild", "clang-gcc"]):
    print("Unknown compiler: " + settings["compiler"])
    quit(0)

# Create command matrix
commands = {
    "build-file": "",
    "link-files": "",
    "delete-files": "",
    "src": [],
    "includes": [],
    "flags": [],
    "linker": [],
    "defines": []
}

# Transfer build settings into the command matrix

# Gather outdated files / Clean files

# Define threading structures
list_unfinished = []
list_finished = []
lock_unfinished = Lock()
lock_finished = Lock()
threads = []
threads_running = True

# Define threading method

# Create and run threads

# Cleanup threads

# Update database

# Create target file
