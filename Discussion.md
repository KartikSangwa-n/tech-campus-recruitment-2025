1. Solutions Considered

🔹 Approach 1: 
1. Load Entire File into Memory (Not Feasible for 1TB)
2. Read the entire log file into memory, process it, and extract relevant logs.
Rejected?
Not scalable for large files (1TB+) as it would consume too much RAM.
Slow performance due to excessive memory usage.

🔹 Approach 2: Line-by-Line File Processing (Efficient)
1. Read the file line by line, check for the required date, and write matching logs to an output file.
Why?
1. Memory Efficient: Reads only one line at a time, avoiding memory overload.
2. Fast Execution: Uses optimized string comparison (line.find(date) == 0).
3. Scalable: Works for very large files (1TB and beyond).



2. Final Solution Summary

Final Approach: Line-by-Line File Processing
1. Skips downloading if log file exists.
2. Ensures output/ directory exists before writing extracted logs.
3. Handles missing log files gracefully with clear error messages.

