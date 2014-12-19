This program takes an input text file and generates a list of words where each adjacent pair has an edit distance one. For example, the following will be a word chain:

at ate hate hat

By modifying the run time parameters and input source, more interesting chains can be discovered.

Usage:./WordChainGenerator [OPTIONS] command command...
        --target-file [/path/to/file.txt]
        File to read words from. REQUIRED.

        --log-file [true/false]
        Stores all output into a file called chain_log.txt in current working directory. Recommended when using large target files. DEFAULT VALUE: false. OPTIONAL.

        --allow-duplicates [true/false]
        Prevents adding a word to a chain more than once. Caveat: can have drastic impact on run time when processing large text files. DEFAULT VALUE: true. OPTIONAL.

        --step-growth [true/false]
        Sets whether chains should grow at each step when being constructed. e.g. farm-form-for-nor-or. DEFAULT VALUE: false. OPTIONAL.

        --filter-length [integer]
        Filter out words that have a length less than or equal to the specified value. DEFAULT VALUE: 0. OPTIONAL.


