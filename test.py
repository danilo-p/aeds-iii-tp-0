from subprocess import run
from random import randint
import numpy as np
import resource as res
import matplotlib.pyplot as plt
import time

in_noop_filename_template = "test/set/in/in_{}_noop.in"
in_updateop_filename_template = "test/set/in/in_{}_updateop.in"
in_queryop_filename_template = "test/set/in/in_{}_queryop.in"

def get_graphics(title, np_array_results, log=False) :
    plt.clf()
    plt.cla()
    plt.close()

    x = np_array_results[:,0]
    y1 = np_array_results[:,4]
    y2 = np_array_results[:,5]
    y3 = np_array_results[:,6]

    plt.plot(
        x, y1,
        x, y2,
        x, y3
    )

    plt.title(title)
    plt.xlabel("Tamanho do vetor de entrada")
    plt.ylabel("Tempo (milisegundos)")
    if log :
        plt.yscale('log', basey=2)
    plt.legend(["Nenhuma operação", "10 operações Min", "10 operações Add"])
    plt.grid(True)
    plt.savefig("{}_{}.png".format(title, time.strftime("%d-%m-%Y_%H:%M:%S")))
    plt.show()

def get_normalized_execution_time(command) :
    time_array = []
    for i in range(0, 5) :
        time_array.append(get_execution_time(command))

    time_np_array = np.array(time_array)
    return np.median(time_np_array)

def get_execution_time(command):
    # initial_time = time()
    initial_time = res.getrusage(res.RUSAGE_CHILDREN)
    run(command, shell=True)
    # final_time = time()
    final_time = res.getrusage(res.RUSAGE_CHILDREN)
    return final_time.ru_utime - initial_time.ru_utime

def execute_and_get_execution_time(n, bin) :
    noop_time = get_normalized_execution_time([
        "./" + bin + " < " + in_noop_filename_template.format(n) + " > /dev/null"
    ])

    updateop_time = get_normalized_execution_time([
        "./" + bin + " < " + in_updateop_filename_template.format(n) + " > /dev/null"
    ])

    queryop_time = get_normalized_execution_time([
        "./" + bin + " < " + in_queryop_filename_template.format(n) + " > /dev/null"
    ])

    return (
        n,
        bin,
        "good" if (noop_time < queryop_time) else "bad",
        "good" if (noop_time < updateop_time) else "bad",
        noop_time,
        queryop_time,
        updateop_time
    )

def generate_input(n):
    print("generating input {}".format(n))
    random_set = []
    for i in range(n) :
        random_set.append(randint(-2147483648, 2147483647))

    in_noop_content_template = "{length} 0\n{input_array}\n"
    in_noop_content = in_noop_content_template.format(length=n, input_array=" ".join(str(x) for x in random_set))
    in_noop_filename = in_noop_filename_template.format(n)
    file = open(in_noop_filename, "w")
    file.write(in_noop_content)
    file.close()

    in_updateop_content_template = "{length} 10\n{input_array}\n"
    for i in range(0, 10) :
        in_updateop_content_template += "Add 1 {length}\n"
    in_updateop_content = in_updateop_content_template.format(length=n, input_array=" ".join(str(x) for x in random_set))
    in_updateop_filename = in_updateop_filename_template.format(n)
    file = open(in_updateop_filename, "w")
    file.write(in_updateop_content)
    file.close()

    in_queryop_content_template = "{length} 10\n{input_array}\nMin 1 1\n"
    for i in range(0, 10) :
        in_queryop_content_template += "Min 1 1\n"
    in_queryop_content = in_queryop_content_template.format(length=n, input_array=" ".join(str(x) for x in random_set))
    in_queryop_filename = in_queryop_filename_template.format(n)
    file = open(in_queryop_filename, "w")
    file.write(in_queryop_content)
    file.close()

def get_results_from_range(bin, start, end, step=1) :
    results = []
    for i in range(start, end, step) :
        result = execute_and_get_execution_time(i, bin)
        print(result)
        results.append(result)
    return results

# for i in range(0, 10000001, 1000) :
#     generate_input(i)

# arvore_results = get_results_from_range("bin/arvore", 0, 1000001, step=1000)
arvore_results = get_results_from_range("bin/arvore", 0, 101, step=10)
get_graphics("arvore", np.array(arvore_results))

# for i in range(0, 501, 10) :
#     generate_input(i)

matriz_results = get_results_from_range("bin/matriz", 0, 101, step=10)
get_graphics("matriz", np.array(matriz_results))