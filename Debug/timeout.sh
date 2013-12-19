#!/bin/bash
# orignially 2008 by Ortwin Glueck
# Permission to use, copy, modify, redistribute in any form is hereby granted to anyone. 
if [ $# -lt 2 ]; then
	echo "Starts a program and kills it if it is still alive"
	echo "after a given time."
	echo "Syntax: timeout [-signal] timespec program [arguments]"
	echo "  signal    the signal to send to the process, default is 9 (kill argument)"
	echo "  timespec  time in seconds (sleep argument)"
        echo "  program   the program to execute"
	echo "  arguments the arguments for program"
        echo "The exit code is preserved or 127 if it could not be determined"
	exit 1
fi

if [ "${1:0:1}" = "-" ]; then
	SIGNAL="${1}"
	shift
else
	SIGNAL="-9"
fi
TIME=${1}
shift

# start program in the background
$@ &
PID=$!
if [ "${PID}" = "0" ]; then
	# process has already ended
	exit 127;
fi
(sleep "${TIME}";  kill "${SIGNAL}" "${PID}") & 2>/dev/null
KILLER=$!
wait "${PID}" 2>/dev/null
R=$?
kill -HUP "${KILLER}" 2>/dev/null
exit ${R}
