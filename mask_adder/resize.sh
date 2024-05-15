#!/bin/bash

# Input and output directories
input_dir="./mask_output/"
output_dir="./mask_output_resize/"

# Create output directory if it doesn't exist
mkdir -p "$output_dir"

# Iterate over each image file in the input directory
for file in "$input_dir"/*; do
    # Check if the file is a regular file
    if [ -f "$file" ]; then
        # Extract the filename without extension
        filename=$(basename -- "$file")
        filename_no_extension="${filename%.*}"

        # Execute ffmpeg command to resize the image while preserving aspect ratio
        ffmpeg -i "$file" -vf "scale=7680:-2" -preset ultrafast "${output_dir}/${filename_no_extension}_resized.png"
    fi
done
