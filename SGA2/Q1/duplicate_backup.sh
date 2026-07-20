#!/bin/bash

SOURCE_DIR="submissions"
BACKUP_DIR="backup"
REPORT_FILE="report.txt"
ERROR_LOG="errors.log"

mkdir -p "$BACKUP_DIR"

> "$REPORT_FILE"
> "$ERROR_LOG"

processed=0
duplicates=0
backedup=0

declare -A hashes

while read file
do
    ((processed++))

    hash=$(md5sum "$file" 2>>"$ERROR_LOG" | awk '{print $1}')

    if [[ -n "${hashes[$hash]}" ]]; then
        ((duplicates++))
    else
        hashes[$hash]=1
        cp "$file" "$BACKUP_DIR/" 2>>"$ERROR_LOG"
        ((backedup++))
    fi
done < <(find "$SOURCE_DIR" -type f 2>>"$ERROR_LOG")

echo "Files Processed: $processed" >> "$REPORT_FILE"
echo "Duplicate Files: $duplicates" >> "$REPORT_FILE"
echo "Files Backed Up: $backedup" >> "$REPORT_FILE"

echo "Report Generated Successfully."
