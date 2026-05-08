"""
HexPulse — Pre-build Script
Injects build timestamp and git hash into firmware
"""
Import("env")
import datetime
import subprocess
import os

def get_git_hash():
    try:
        return subprocess.check_output(
            ["git", "rev-parse", "--short", "HEAD"],
            stderr=subprocess.DEVNULL
        ).decode("utf-8").strip()
    except:
        return "unknown"

build_time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
git_hash = get_git_hash()

env.Append(CPPDEFINES=[
    ("BUILD_TIMESTAMP", env.StringifyMacro(build_time)),
    ("GIT_HASH", env.StringifyMacro(git_hash)),
])

print(f"[HexPulse] Build: {build_time} | Git: {git_hash}")
