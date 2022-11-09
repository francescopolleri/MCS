from ROOT import *
import time
import math as m

rnd = TRandom3 ( )
rnd . SetSeed ( int ( time.time () ) )

h = TH1D( "h" , "" , 20 , 0 , 10 )
lam = 0.5

for i in range (0 ,1000 ) :
   x = -1./lam*m.log(1-rnd.Rndm() )
   h.Fill(x)

h . Draw ( )
gApplication.Run ( True )