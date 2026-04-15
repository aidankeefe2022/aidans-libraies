#!/usr/bin/env bash
set -uo pipefail # Removed -e to manually handle background job failures

CC=gcc
CFLAGS="-g -O0 -fsanitize=address,undefined -I../include -fno-omit-frame-pointer"
RUN_DIR="../.test_bins"
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

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
            status=$?
            # Print the grouped output once the subshell is done
            echo -e "$output\n"
            exit "$status"
        ) &
    pids+=($!) # Track the Process ID of the background job
done

# Wait for all background processes to finish
number_passed=$number_found
exit_code=0
for pid in "${pids[@]}"; do
    if ! wait "$pid"; then
        number_passed=$((number_passed - 1))
        exit_code=1
    fi
done

if ! $found_any; then
    echo "No Tests Found"
else
    echo -e "${GREEN}Found $number_found Tests${NC}"
    if (( number_found > number_passed )); then
      echo -e "${RED}$number_passed/$number_found Tests Have Passed${NC}"
    else
      echo -e "${GREEN}$number_passed/$number_found Tests Have Passed${NC}"
    fi
fi

exit $exit_code
