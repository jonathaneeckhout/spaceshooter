#!/bin/bash

# Directory to search
DIR="assets"

# Extensions to look for
EXTENSIONS=("mp3" "wav" "ttf" "jpeg")

for ext in "${EXTENSIONS[@]}"; do
    find "$DIR" -type f -name "*.$ext" | while read -r file; do
        dir_name=$(dirname "$file")
        base_name=$(basename "$file" | sed 's/\.[^.]*$//')
        xxd -n "$base_name" -i "$file" >"${dir_name}/${base_name}.h"
        echo "Converted $file to ${dir_name}/${base_name}.h"
    done
done
