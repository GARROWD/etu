#include <iostream>
#include <cmath>

#include "stack.cpp"

using std::cout;
using std::min;

int get_min_run_length(int array_length) {
    int other_bits_det = 0;
    while (array_length >= 64) {
        other_bits_det |= array_length & 1; // if(array_length & 1 == 1) other_bits_det = 1;
        array_length >>= 1;
    }

    return array_length + other_bits_det;
}

int gallop_mode(int *array, int &gallop_p, int gallop_val, int gallop_end) {
    int gallop_start = gallop_p;
    int left = 0, right = 0, middle = 0, degree = 0;

    while (true) {
        gallop_p += pow(2, degree);
        if (array[gallop_p] > gallop_val || gallop_p >= gallop_end) {
            left = gallop_start;

            if (gallop_p >= gallop_end - 1) {
                right = gallop_end - 1;
            } else {
                right = gallop_p;
            }

            do {
                middle = (left + right) / 2;

                if (array[middle] < gallop_val) {
                    left = middle + 1;
                } else {
                    right = middle - 1;
                }
            } while (left <= right);

            gallop_p = left;
            return left;
        } else {
            degree++;
        }
    }
}

void bin_ins_sort(int *array, int array_start_index, int array_length) {
    for (int i = array_start_index; i < array_start_index + array_length - 1; i++) {
        if (array[i] > array[i + 1]) {
            int insert_value = array[i + 1];
            int left = array_start_index;
            int right = i;
            int middle = 0;

            do {
                middle = (left + right) / 2;

                if (array[middle] < insert_value) {
                    left = middle + 1;
                } else {
                    right = middle - 1;
                }
            } while (left <= right);

            for (int j = i; j >= left; j--) {
                array[j + 1] = array[j];
            }
            array[left] = insert_value;
        }
    }
}

void bin_merge_sort(int *array, node first_run, node second_run) {
    int runs_length = first_run.length + second_run.length;
    int first_p = first_run.start_index, second_p = second_run.start_index;
    int first_run_end = first_run.length + first_run.start_index, second_run_end =
            second_run.length + second_run.start_index;
    int first_gallop_count = 0, second_gallop_count = 0;
    int gallop_start = 0, gallop_end = 0;

    int *tmp = new int[runs_length];

    for (int i = 0; i < runs_length; i++) {
        if (first_p >= first_run_end) {
            tmp[i] = array[second_p];
            second_p++;
        } else if (second_p >= second_run_end) {
            tmp[i] = array[first_p];
            first_p++;
        } else if (array[first_p] < array[second_p]) {
            tmp[i] = array[first_p];
            first_p++;
            first_gallop_count++;
            second_gallop_count = 0;
        } else {
            tmp[i] = array[second_p];
            second_p++;
            second_gallop_count++;
            first_gallop_count = 0;
        }

        if (first_gallop_count > 7) {
            gallop_start = first_p;
            gallop_end = gallop_mode(array, first_p, array[second_p], first_run_end);

            for (int j = 0; j < gallop_end - gallop_start; j++) {
                tmp[i + j + 1] = array[j + gallop_start];
            }

            i += gallop_end - gallop_start;
            first_gallop_count = 0;
        } else if (second_gallop_count > 7) {
            gallop_start = second_p;
            gallop_end = gallop_mode(array, second_p, array[first_p], second_run_end);

            for (int j = 0; j < gallop_end - gallop_start; j++) {
                tmp[i + j + 1] = array[j + gallop_start];
            }

            i += gallop_end - gallop_start;
            second_gallop_count = 0;
        }
    }

    int array_start_index = std::min(first_run.start_index, second_run.start_index);
    for (int i = 0; i < runs_length; i++) {
        array[i + array_start_index] = tmp[i];
    }
}

void merge_runs(int *array, stack &runs) {
    node x, y, z;
    x = runs.peek(2);
    y = runs.peek(1);
    z = runs.peek(0);

    while (!(x.length > y.length + z.length || runs.size < 3) || !(y.length > z.length || runs.size < 2)) {
        runs.pop();

        if (x.length) {
            runs.pop();

            if (z.length > x.length) {
                bin_merge_sort(array, y, x);
                runs.edit(std::min(y.start_index, x.start_index), y.length + x.length);
                runs.push(z.start_index, z.length);
            } else {
                bin_merge_sort(array, y, z);
                runs.push(std::min(y.start_index, z.start_index), y.length + z.length);
            }
        } else {
            bin_merge_sort(array, y, z);
            runs.edit(std::min(y.start_index, z.start_index), y.length + z.length);
        }

        x = runs.peek(2);
        y = runs.peek(1);
        z = runs.peek(0);
    }
}

void final_merge(int *array, stack &runs) {
    while (!runs.is_empty()) {
        node first_run = runs.peek(1), second_run = runs.peek(0);
        bin_merge_sort(array, first_run, second_run);
        runs.pop();
        runs.edit(min(first_run.start_index, second_run.start_index), first_run.length + second_run.length);
    }
}

void divide_to_runs(int *array, stack &runs, int array_length) {
    int i = 0, min_run_length = get_min_run_length(array_length);
    while (i < array_length) {
        int run_start_index = i, run_length = min_run_length;

        if (i + min_run_length < array_length) {
            bin_ins_sort(array, i, min_run_length);
            i += min_run_length;

            while (array[i - 1] <= array[i]) {
                run_length++;
                i++;
            }
        } else {
            bin_ins_sort(array, i, array_length - i);
            run_length = array_length - i;
            i = array_length;
        }

        runs.push(run_start_index, run_length);
    }
}

void tim_sort(int *array, int array_length) {
    stack runs;

    divide_to_runs(array, runs, array_length);
    merge_runs(array, runs);
    final_merge(array, runs);
}

#include <chrono>
#include "merge_sort.cpp"

int main() {
    const int array_size = 1000;
    int tim_sort_array[array_size];
    int merge_sort_array[array_size];

    srand(time(0));

    for (int i = 0; i < array_size; ++i) {
        int number = rand();
        tim_sort_array[i] = number;
        merge_sort_array[i] = number;
    }

    auto start = std::chrono::system_clock::now();
    tim_sort(tim_sort_array, sizeof(tim_sort_array) / sizeof(int)); // tim_sort
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << " [i] Tim sort - " << std::fixed << elapsed_seconds.count() << " sec\n";

    start = std::chrono::system_clock::now();
    merge_sort(merge_sort_array, sizeof(merge_sort_array) / sizeof(int)); // merge_sort (from_net
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << " [i] Merge sort - " << std::fixed << elapsed_seconds.count() << " sec\n";

    system("pause");

    return 0;
}
