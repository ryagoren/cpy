#!/bin/bash
testdir="$(cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd)"
expected_output="${testdir}/expected_lorem.txt"

if diff -u --color <("${testdir}/../cpy" < "${testdir}/lorem.txt") "$expected_output"; then
	echo "${0}passed!"
	exit 0
else
	echo "${0} failed!"
fi
