#!/bin/bash
testdir="$(cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd)"
expected_output="${testdir}/expected_lorem.txt"

if diff -u --color <("${testdir}/../cpy" < "${testdir}/lorem_many_trailing.txt") "$expected_output"; then
	echo "passed!"
	exit 0
else
	echo "failed!"
	exit 1
fi
