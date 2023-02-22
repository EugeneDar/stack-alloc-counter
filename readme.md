Build:

    $ cd stack-allocations-counter
    $ mkdir build && cd build && cmake .. && make && cd ..

Quick start:

    $ clang -flegacy-pass-manager -Xclang -load -Xclang build/estimator/libSkeletonPass.* resourses/example.c resourses/logging_lib.c
    $ ./a.out

How to use:

    $ clang -flegacy-pass-manager -Xclang -load -Xclang build/estimator/libSkeletonPass.* <input_file> resourses/logging_lib.c
    $ ./a.out
