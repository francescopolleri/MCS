class Vector:
    def __init__(self,x,y):
     self.x = x
     self.y = y
    
    def __add__(self,b):
     return Vector(self.x+b.x, self.y+b.y)
    
    def __str__(self):
     return "(" +str(self.x)+ ","+ str(self.y)+ ")"


a=Vector(3,2)
b=Vector(4,5)
c=a+b

print(c)


import cmath
import numpy as np
import matplotlib.pyplot as plt

x=np.linspace(-5*np.pi,5*np.pi,100)
y=np.sin(x)/x

plt.plot(x,y)
plt.show()