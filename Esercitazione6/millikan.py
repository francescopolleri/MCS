import numpy as np
import matplotlib.pyplot as plt
from ROOT import *

h_mil=TH1D("h_mil","",100,0,0)

for line in open("millikan.dat"):
    h_mil.Fill(float(line))

h_mil.Draw()

gApplication.Run(True)
