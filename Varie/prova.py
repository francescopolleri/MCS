#!/usr/bin/python

print("Hello World")

l=[1, 2, 3, 4, 5, 6]

print(l[2:5])

thing=[23,45]

thing.append('cat')

thing[1]='dog'

print(thing)

a=2
if a==1:
    print(a)
elif a==2:
    print(a)
    print("a vale 2")

for word in ('qwerty','uiop','asdf'):
    print('%s' %word)

def sum(x=1,y=2,z=3):
    return x+y+z

print(sum(12,11,9))