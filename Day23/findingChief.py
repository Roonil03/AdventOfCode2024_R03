# filename = 'Day23/input23.txt'
filename = 'Day23/test23.txt'
with open(filename, 'r') as f:
    lines = f.readlines()
    lines = [line.strip() for line in lines]
lan = {}
for line in lines:
    comp1, comp2 = line.split('-')
    if comp1 not in lan:
        lan[comp1] = set()
    if comp2 not in lan:
        lan[comp2] = set()
    lan[comp1].add(comp2)
    lan[comp2].add(comp1)
count = 0
for comp in lan:
    near = list(lan[comp])
    for i in range(len(near)):
        for j in range(i + 1, len(near)):
            if near[j] in lan[near[i]]:
                tri = sorted([comp, near[i], near[j]])
                if any(c.startswith('t') for c in tri):
                    count += 1
print(count / 3)
