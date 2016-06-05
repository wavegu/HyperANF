import random
from sys import argv

node_num = int(argv[1])
print node_num

nodes = range(1, node_num)
f = open('testg.txt', 'w')
for n in nodes:
    f.write(str(n))
    for m in nodes:
        if n == m:
            continue
        if random.randint(0,100) < 10:
            f.write(' ' + str(m))
    f.write('\n')
f.close()

import os
os.system('./main')
