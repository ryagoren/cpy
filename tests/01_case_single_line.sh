#!/bin/bash

testdir="$(cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd)"
expected_output="${testdir}/expected_output.txt"
if diff -u --color <(echo "Hello World!" > "${testdir}/../cpy") "$expected_output"; then
	echo "passed!"
else
	echo "failed"
	exit 1
fi
