inf = float("inf")
prev = 3.3
for r in range(2**3):
    rs = []
    rs.append(5100*2 if r & (1<<len(rs)) else inf)
    rs.append(5100   if r & (1<<len(rs)) else inf)
    rs.append(5100/2 if r & (1<<len(rs)) else inf)

    x = sum([1/i for i in rs])
    rlow = 1/x if x else inf
    voltage = round(3.3 * rlow / (5100 + rlow), 2)
    print(r, "[" + ',\t'.join([str(i) for i in rs]) + "]", round(rlow,0), voltage, round(prev - voltage, 2), sep="\t")
    prev = voltage

