# -*- coding: utf-8 -*-
"""
Created on Thu Nov 18 21:19:01 2021

@author: Louis
"""

import csv
import numpy as np
import sounddevice

import time as time

file='/home/martinho/Documents/embedded-machine-learning/Helpers/metal.00000.au'

sound_data = "/home/martinho/Documents/embedded-machine-learning/Helpers/sound_cpp.txt"

Fe=22050

def readAuFile(file):


    with open(file, 'rb') as au:
        magic = au.read(4)
        dataoffset = int.from_bytes(au.read(4), byteorder='big', signed=True)
        print(dataoffset)
        datasize = int.from_bytes(au.read(4), byteorder='big', signed=True)
        au.seek(0)
        au.read(dataoffset)
        data = au.read(datasize)

    d = []

    fichier = open("/home/martinho/Documents/embedded-machine-learning/Helpers/sound_python.csv", "w")
    writer = csv.writer(fichier)
    for i in range(0, datasize, 2):
        d.append(int.from_bytes(data[i:i + 2], byteorder='big', signed=True))

    d=np.asarray(d, dtype=np.int16)

    writer.writerow(d)

    # for l in d :
    #     fichier.write(str(l))
    #     # writer.writerow(l)
    #     fichier.write('  ')


    fichier.close()

    return d

def read_audio(sound_data) :
    with open(sound_data, 'r') as au:
        lines = au.readlines()
        au.close()
    d = []
    for line in lines:
        # print(line.strip())
        d.append(np.int8(line.strip()))

    d=np.asarray(d)

    return d

d1=readAuFile(file)
# sounddevice.play(d1[:5*Fe], samplerate=Fe)
# time.sleep(10)


##d2=read_audio(sound_data)
# print(d)

##sounddevice.play(d2[:5*Fe], samplerate=Fe)
##time.sleep(10)
