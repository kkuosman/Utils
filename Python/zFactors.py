#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Oct  8 18:55:49 2020

Determines a factored form of z-transform
Adapted from Mitra.

@author: kkuosman
"""

import scipy.signal as signal
import numpy as np

num1 = input("Enter transfer function numerator values [b1, b2, b3]:\n")[1:-1].split(',')
num = list(map(int, num1))
den1 = input("Enter transfer function numerator values [a1, a2, a3]:\n")[1:-1].split(',')
den = list(map(int, den1))


(z, p, k) = signal.tf2zpk(num, den)

m = abs(p)
print('Zeros ', z)
print('Poles ', p)
print('Gain constant ', k)
print('Pole radius', m)
sos = signal.zpk2sos(z,p,k)
print('Second-order sections: ', np.real(sos))