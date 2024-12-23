from collections import defaultdict
import networkx as nx

lan = defaultdict(list)
comps = nx.Graph()
# filename = 'Day23/test23.txt'
filename = 'Day23/input23.txt'
with open(filename) as f:
    for line in f:
        line = line.strip().split('-')
        lan[line[0]].append(line[1])
        lan[line[1]].append(line[0])
        comps.add_edge(line[0], line[1])
uniques = set()
for comp in lan:
    for near in lan[comp]:
        for sec_near in lan[near]:
            if sec_near != comp and comp in lan[sec_near]:
                uniques.add(tuple(sorted([comp, near, sec_near])))
print(",".join(sorted(list(nx.enumerate_all_cliques(comps))[-1])))
