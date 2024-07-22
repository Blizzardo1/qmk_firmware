#!/bin/bash

# Function to convert a keyboard name to a human-readable label
to_human_friendly() {
    echo "$1" | sed -e 's|/| |g' -e 's|_| |g' -e 's/\b\(.\)/\u\1/g'
}

# Run the command and capture the output
keyboards=$(qmk list-keyboards)

# Initialize JSON array
echo "["

# Process each keyboard and convert to JSON
first=true
while IFS= read -r keyboard; do

    # Sanitize the keyboard name
    sanitized_keyboard=$(echo "$keyboard" | sed 's/[^a-zA-Z0-9_\/-]//g')
    human_friendly_label=$(to_human_friendly "$sanitized_keyboard")
    echo "{\"label\": \"$human_friendly_label\", \"value\": \"$sanitized_keyboard\"},"
done <<<"$keyboards"

# Close JSON array
echo "]"
