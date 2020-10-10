#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct 10 16:28:37 2020

Displays contour spectrogram of a given file.
This is mostly equivalent to a regular spectrogram,
but may reveal different things, due to the way contours
are presented.

@author: kkuosman
@version: 0.9
"""


from scipy.io import wavfile
import matplotlib.pyplot as plt
import numpy as np

#TODO: make these optional arguments
fft_size = 2048 # Decent balance between time- and frequency-domain resolutions
channel = 0 # First (left) channel

def contour_spectrogram(filename):
    fs, audio = wavfile.read(filename)
    #: Determine spectrogram size
    spectrum_length = len(audio) // fft_size
    spectral_data = []
    #Cut audio into chunks
    for idx in range(0, len(audio), fft_size):
        print(idx)
        audio_slice = audio[idx:idx+fft_size, channel]
        #TODO: OPTIONAL: Apply windows
        #Take spectra
        spectral_data.append(np.abs(np.fft.fft(audio_slice, fft_size))[:fft_size//2])
        #print(len(spectral_data))
        
    
    #Plot data
    spectral_data = np.array(spectral_data)
    plt.contourf(spectral_data.T)
    plt.ylabel("Frequency")
    plt.xlabel("Time")
    #plt.ylim([0,200]) #Often most of the audio energy is at lower frequencies. Use this to limit displayed freq range.
    