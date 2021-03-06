# Strong Python test file for HeliumLex
# Which implements the Eular Prime Sieve Algorithm and other bullshit language features
# By James Zhang

## import argument tests
import numpy as np
from functools import reduce
from scipy.optimize import *
import os

## variable declearation argument tests
MaxN = 100000
print("Welcome to python-like language test!")

## function and indent tests
# generate: returns a list with all primes lower than N
def generate(N):
    prime_list = []
    ## weird grammer tests
    is_prime = [True] * MaxN
    is_prime[0] = is_prime[1] = False
    for i in range(2, N):
        if (is_prime[i]):
            prime_list.append(i)
        j = 0
        while (j < len(prime_list) and i * prime_list[j] < N):
            is_prime[i * prime_list[j]] = False
            if (i % prime_list[j] == 0):
                break
            j += 1
    return prime_list

class test:
    def dict_test(self):
        dict_a = {}
        dict_b = { 'Hello' : dict_a }
        return dict_b
    def lambda_and_generative_test(self):
        targ = [i * 3 for i in range(0, 10)]
        els = np.array(targ)
        return reduce(lambda x, y: x * 2 + y, targ) * np.sum(targ)
    def call_and_math_test(self): ## using scipy
        f = lambda x, a, b: x**a + b * np.sin(x)
        xdata = np.linspace(-10, 10, num = 20)
        ydata = f(xdata, 1, 7) + np.random.randn(xdata.size)
        guess = [2, 2]
        params, params_covariance = curve_fit(f, xdata, ydata, guess)
        return params
    def raw_string_and_comment_test(self):
        '''
        Yes it is a nice way to comment large sections
        '''
        self.tested = """ Why don't do so?
When you can
                even if not pretty. # and here not comment
        """
        return self.tested + ' So laughing out loud'

## main provides string and more tests
def main():
    N = eval(input('This is the Eular Prime Generator, please input N as the upper limit of the generation:\n'))
    while (not isinstance(N, int)):
        N = eval(input('Please input an integer:'))
    print('Generating...')
    res = generate(N)
    print(res)

    ## more tests
    targ = test()
    print(targ.dict_test())
    print(targ.lambda_and_generative_test())
    print(targ.call_and_math_test())
    print(targ.raw_string_and_comment_test())
    print(
        "These",
        "kinds",
        "of",
        "crossing lines are allowed", \
        "in python"
    )

# some wierd code style test
    ifanyoneswitch=(1*23)
    ____________somebar1234___sad =ifanyoneswitch
    _m_o_n_u_m_e_n_t_=____________somebar1234___sad*2+ifanyoneswitch
    IF         = 0o31 ** 0O67 - _m_o_n_u_m_e_n_t_ +        0b100010111010110 - 0B110 / 0x1223144FDF89A
    WhIle="Hello\0no '' t\\"
    dEF=IF/____________somebar1234___sad
    MAIN = 30.2341 - 18.3j
    MAIN-= IF

    print(os.listdir())

if __name__ == "__main__":
    # execute only if run as a script
    main()
