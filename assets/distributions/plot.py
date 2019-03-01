import matplotlib.pyplot as plt
import os

files = [f for f in os.listdir() if '.txt' in f]
# files = ['friendster.txt']

def read_file(filename):

    def decode_line(line):
        x = line[:-1].split(' ')
        return int(x[0]), int(x[1])


    fd = open(filename)
    return list(map(decode_line, fd.readlines()))


dds = { file: read_file(file) for file in files }
fig, axes = plt.subplots(nrows=len(files))

for i, file in enumerate(files):
    axes[i].set_yscale('log')
    # axes[i].set_xscale('log')
    axes[i].plot(*zip(*dds[file]), label=file)
    axes[i].legend()
    # plt.plot(*zip(*dds[file]), label=file)

plt.show()
