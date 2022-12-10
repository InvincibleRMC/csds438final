import time
import numpy as np
N =  10000000

def addVectors(v1:np.ndarray ,v2: np.ndarray):
    v3: np.ndarray = np.ones(N)
    for i in range(len(v1)):
        v3[i] = v1[i] + v2[i]
    return v3

def main():
    ones: np.ndarray = np.ones(N)
    negativeONes: np.ndarray = np.ones(N)*-1
    
    start = time.time()
    zeros: np.ndarray = addVectors(ones,negativeONes)
    end = time.time()
    print("Elapsed = %s" % (end - start))
    

    if(zeros.size != N):
        raise Exception("Summed Vector is Wrong Size")
    
    if not(np.array_equal(zeros,np.zeros(N))):
        raise Exception("Incorrect Summation for Zeros")

    print("Completed Summation")

main()
