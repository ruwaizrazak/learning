#This is about testing the basic math in python
area=0
length=2
breadth=3
#area of triangle
area=length*breadth/2
print ("the area is %.2f" %area)
# Why are we using %.2f ? 
#the %F is the same in the cpp language, the %2.f denotes that we can display up to two decimal places
#why the print('area =' + area) dont work? because string and numerics wont catenate.
#Lets fdo the same thing using .format to test it
print("the area is {0:d}".format(area))
print(" we are going to input three values,\n first one is {0:04d} \n second one is {1:d} \n third one is {2:2f}".format(7,8,9))