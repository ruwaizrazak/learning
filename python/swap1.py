#swap without additional variable
x=input("enter number")
y=input("enter another number")
x=int(x)+int(y)
y=int(x)-int(y)
x=int(x)-int(y)
print(" new values")
print ("x's value changed to %d" %x)
print ("y's value changed to %d" %y)