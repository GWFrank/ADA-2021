from random import sample
n = 20
print(f"{n} 0")
for i in sample(range(n), n):
    print(i, end=" ")
print("")