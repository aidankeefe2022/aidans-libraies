#!/usr/bin/env bash
set -uo pipefail # Removed -e to manually handle background job failures

CC=gcc
CFLAGS="-O3 -I../include"
RUN_DIR="../.test_bins"

cd ./scripts

mkdir -p "$RUN_DIR"
shopt -s globstar

found_any=false
number_found=0
pids=()

for file in ../**/*_test.c; do
    found_any=true
    number_found=$((number_found + 1))

    (
            base=$(basename "$file" .c)
            out="$RUN_DIR/$base"

            # Capture all output (stdout + stderr) into a variable
            output=$(
                if ! $CC $CFLAGS "$file" -o "$out" 2>&1; then
                    echo "❌ Compile failed: $file"
                    exit 1
                fi
                if ! "$out" 2>&1; then
                    echo "❌ Test failed: $file"
                    exit 1
                fi
            )

            # Print the grouped output once the subshell is done
            echo -e "$output\n"
        ) &
    pids+=($!) # Track the Process ID of the background job
done

# Wait for all background processes to finish
exit_code=0
for pid in "${pids[@]}"; do
    if ! wait "$pid"; then
        exit_code=1
    fi
done

if ! $found_any; then
    echo "No Tests Found"
else
    echo "Found $number_found Tests"
fi

exit $exit_code
