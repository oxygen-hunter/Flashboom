#!/bin/bash
for file in /data/lixiao/workspace/rallm_auditor/data/vuln-10/blind/add_fixed_re_entrancy/*_*.sol; do
  # Extract the number (n) part before the first underscore
  new_name=$(echo "$file" | sed -r 's/(.*\/)([0-9]+)_.*/\1\2.sol/')
  
  # Rename the file
  mv "$file" "$new_name"
done