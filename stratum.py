import ctypes
import pandas as pd
import numpy as np
import timeit
import time

libtrie = ctypes.CDLL('./libtrie.so')


with open('./ids.txt', 'r') as file:
    ids = file.readlines()

ids = [id.strip() for id in ids]

dataframe = pd.DataFrame({"stratum_id":ids})
print(dataframe)


def python_way():
    print("The python way")
    dataframe["stratum_count"] = dataframe.groupby("stratum_id")["stratum_id"].transform("size")   
    #print(dataframe)


def c_way():
    print("The C (ctypes) way")
    stratum_ids = np.array(dataframe["stratum_id"])
    
    arr = (ctypes.c_char_p * len(stratum_ids))()
    arr[:] = [s.encode('utf-8') for s in stratum_ids]  
    
    _time_call_start_c = time.time()
    libtrie.count_occurances(arr, len(stratum_ids))
    _time_call_end_c = time.time()



    return _time_call_end_c - _time_call_start_c

time_python = timeit.timeit(python_way,number=1)
time_c = timeit.timeit(c_way, number=1)
time_c_call = c_way()

print(f"Python took: {time_python}")
print(f"C took: {time_c}")
print(f"C (just the clib call) took: {time_c_call}")

