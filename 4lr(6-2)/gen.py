#!python3

# will make several tests and record time

# your program mast output only sorted sequence
# so you have to rewrite "generate_tests(qty)"
# and just check for correct unswer

import os, sys
import random
import string

import subprocess

import time

str_length = 40
# exec_path  = "../build/run" # path to yours executable
exec_path  = "solution/solution" # path to yours executable
pic_fold = ""
out_test_file = "./generated.tst"

invalid_val = -1
invalid_key = ""

output_process   = False
output_main_test = False
run_tests        = True
save_tests       = True
load_tests       = True
save_main_test   = True
build_benchmark  = True

# create array of array

def generate_tests(qty):
    val_min = 0
    val_max = 200

    tests = ""
    tests += ("1 2 3 4 ? 2 3 ? 1 2 2 3 ? 0 1\n")
    for _ in range(qty):
        key = random.randint(val_min, val_max)
        tests += (str(key) + '\n')
    print(tests)
    return tests


def check(inp,out):
    return True

# create array of str inp




nums  = []
times = []
num_qty = 10;
num_max = int(sys.argv[1])
if len(sys.argv) > 2: num_qty = int(sys.argv[2])
if output_process: print("running tests for", nums)

if output_main_test or run_tests: 
    test_set = generate_tests(num_max)  # generate main test
    
#preprocess_tests(test_set)  # append some chars, key words, etc
inp = test_set
print("generated")
if output_main_test: 
    print("output main test:")
    print("\n".join(inp))
if save_main_test:
    with open(out_test_file, "w") as fl:
        fl.write((inp))
if run_tests: 
    for i in range(num_qty):
        num = int(num_max / (2 ** i))
        if output_process: 
            print("\n\nrunning test for", num)
        sub_input = inp[:num]

        if output_process: 
            print("\n\nInput:\n{}".format(sub_input))

        process = subprocess.Popen(
                exec_path, stdin=subprocess.PIPE,
                # stderr=sys.stdout, bufsize=16384,
                stderr=sys.stdout, bufsize=8192,
                stdout=subprocess.PIPE)
        start_time = time.time() # start recording time
        # sub_output = ""
        # for i, line in enumerate(sub_input):
        #     print("entering {} entry {}".format(i, str(line)))
            # process.stdin.write((str(line)+"\n").encode('utf-8'))   # write to out prog
        out, err = process.communicate("\n".join(sub_input).encode('utf-8'))
        if err is not None:
            print("Error: {}".format(err.decode()))
        sub_output = out.decode()      # read from prog
        time_taken = str((time.time() - start_time) / 60)  # capture the time
        process.stdin.close()

        if output_process: print("\n\nOutput:\n{}".format(sub_output))
        if output_process: print("Time taken (sec): {}".format(time_taken))

        print("time taken {} for numbers: \t{}".format(num, time_taken))
        nums.append(num)
        times.append(str(time_taken)[:7])
        assert check(test_set[:num], sub_output.split("\n")), "Not right check :(\n"

if build_benchmark:
    import matplotlib.pyplot as plt
    plt.suptitle('Benchmark')
    # plt.plot(nums, times)
    plt.plot(nums, times)
    plt.gca().invert_yaxis()
    
    plt.xlabel('entries quantity')
    plt.ylabel('time taken (sec)')

    print("saving plt")
    plt.savefig(os.path.join(pic_fold, "benchmark.png"), bbox_inches='tight')
    # plt.savefig("test.png",bbox_inches='tight')
    print("saved")
    plt.show()
    
