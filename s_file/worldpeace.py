import random

def calculate_pi(iterations):
    inside_circle = 0
    for _ in range(iterations):
        x, y = random.random(), random.random()
        if x**2 + y**2 <= 1:
            inside_circle += 1
    pi = 4 * inside_circle / iterations
    print(f"Approximated value of Pi: {pi}")

if __name__ == "__main__":
    calculate_pi(10**4)
