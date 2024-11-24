def is_prime(num):
    if num < 2:
        return False
    for i in range(2, int(num ** 0.5) + 1):
        if num % i == 0:
            return False
    return True

def find_primes(limit):
    primes = [n for n in range(limit) if is_prime(n)]
    print(f"Found {len(primes)} primes up to {limit}")

if __name__ == "__main__":
    find_primes(10**4)
