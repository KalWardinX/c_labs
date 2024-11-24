import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("./cpu_fib.txt")


print(df)
clients = df['num_clients']
requests = df['tot_iter']
time = df['time']
plt.xlabel('Requests')
plt.ylabel('Time (in s)')
plt.plot(requests, time, color='red', marker='X', linewidth=2)
plt.title("Time v/s Requests")
plt.savefig("Req_vs_time_2.png", dpi=100)
plt.clf()
# plt.show()

thruput = requests/time
plt.xlabel('Requests')
plt.ylabel('Througput (Req/sec)')
plt.plot(requests, thruput, color='red', marker='X', linewidth=2)
plt.title("Throughput v/s Requests")
plt.savefig("Throughput_vs_Req_2.png", dpi=100)

# plt.show()