#manipulaitng variables
#first we are using the + sign to concatenate
firstname = input("\nhey, what's your first name?\n")
lastname = input("last name please\n")
print ("Heloo " + firstname + " " + lastname)

#converting cases, like upper case, lower case and even swapping too

message = "Hello world"
print(message.lower())
print(message.upper())
print(message.swapcase())
name=firstname+lastname
name=name.lower()
#the above line converts the variable name to lower case. so tat we can use it for username as well
print(" hello " + name)



