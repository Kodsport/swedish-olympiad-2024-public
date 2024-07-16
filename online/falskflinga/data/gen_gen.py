
def ptc(name, n, program):
    print(f"tc {name} {program} n={n}")


print("group group1")
for i in range(10):
    ptc(f"g1-random-{i+1}", 7, "gen_rand")
for i in range(5):
    ptc(f"g1-flake-{i+1}", 7, "gen_from_flake")


print("\ngroup group2")
for i in range(10):
    ptc(f"g1-random-{i+1}", 11, "gen_rand")
for i in range(5):
    ptc(f"g1-flake-{i+1}", 11, "gen_from_flake")

print("\ngroup group3")
for i in range(10):
    ptc(f"g1-random-{i+1}", 15, "gen_rand")
for i in range(20):
    ptc(f"g1-flake-{i+1}", 15, "gen_from_flake")
for i in range(20, 30):
    ptc(f"g1-flake-{i+1}", 15, "gen_from_flake" + " no_stem=1")
