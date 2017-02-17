#!/bin/bash

num_tasks=3
build_target=build-t
run_target=run-t

input_dir=./input
output_dir=./output
ref_dir=./ref

points_per_task[1]=40
points_per_task[2]=40
points_per_task[3]=20

num_tests[1]=8
num_tests[2]=8
num_tests[3]=4

task_timeout[1]=20
task_timeout[2]=10
task_timeout[3]=10


function prepare_checker {
    total_points=0
}

function prepare_task {
    task_points=0

    echo "TASK "$i":"
    mkdir -p $output_dir/task${1}
}

function print_task_results {
    echo "  Total points for task" $1":" $task_points
}

function print_total {
    echo "TOTAL:" $total_points
}

function check_test {
    input=$input_dir/task${1}/test${2}.in
    ref=$ref_dir/task${1}/test${2}.ref
    output=$output_dir/task${1}/test${2}.out

    make -s run-t$1 <$input >$output 2>/dev/null
    if [ $? -ne 0 ]; then
        echo "    Test" $2 "failed - no such target."
    else
        diff -w $output $ref &>/dev/null
        if [ $? -eq 0 ]; then
            task_points=$((task_points+points_per_test))
            echo "    Test" $2": OK!"
        else
            echo "    Test" $2": Wrong!"
        fi
    fi
}

function clean {
    make clean
}


# Prepare checker
prepare_checker

# Check each task
for ((i=1; i<=$num_tasks; i++)); do

    # Prepare task i
    prepare_task "$i"

    # Compile for task i
    make $build_target${i} &>/dev/null
    if [ $? -ne 0 ]; then
        echo "  Makefile failed!"
    else
        num_tests=$(ls $input_dir/task${i} | wc -w)
        points_per_test=$((points_per_task[$i]/num_tests[$i]))
   
        for ((j=1; j<=$((num_tests[$i])); j++)); do
            check_test "$i" "$j"
        done
    fi

    # Print results for task i
    print_task_results "$i"

    # Add to total
    total_points=$((total_points+task_points))
done

# Print total
print_total
clean

