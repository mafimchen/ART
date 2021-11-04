# ART with Forgetting
This is an implementation of adaptive random testing with forgetting.

## Usage
### Setup the following const variables before compile:
* total_tc: the total number of test cases in test suite
* candidate_size: the size of candidate set
* memory_size: the size of the set that used by forgetting
###Compile the code and execute it with the following arguments:
* input: the path of the file that contains the id of failure-causing test cases
* output: the path of result file
* runtimes: how many time the execution will repeat
