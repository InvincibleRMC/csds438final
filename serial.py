import time
import numpy as np
N =  10000000

def addVectors(v1:np.ndarray ,v2: np.ndarray):
    return v1 + v2

def main():
    ones: np.ndarray = np.ones(N)
    print(ones)
    print(ones.size)
    negativeONes: np.ndarray = np.ones(N)*-1
    print(negativeONes)
    print(negativeONes.size)

    start = time.time()
    zeros: np.ndarray = addVectors(ones,negativeONes)
    end = time.time()
    print("Elapsed = %s" % (end - start))
    print(zeros)

    if(zeros.size != N):
        raise Exception("Summed Vector is Wrong Size")
    
    if not(np.array_equal(zeros,np.zeros(N))):
        raise Exception("Incorrect Summation for Zeros")

    print("Completed Summation")

main()
