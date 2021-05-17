import itertools
import time

def all_combos_func(arguments):
    data = list(arguments)
    return itertools.chain.from_iterable(itertools.combinations(data, r) for r in range(len(data)+1))

start_time = time.time()

all_comb= []
for i in range (25):
    all_comb.append(i+1)
all_combos = all_combos_func(all_comb)
all_combos_count = []
for i in all_combos:
    if(len(i) == 10):
        all_combos_count.append(i)
        # print(i)
print("this is the total length", len(all_combos_count))
end_time = time.time()

print(end_time-start_time)