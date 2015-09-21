#finding fibanocci series
def fib(n):
   "Recursive function"
   if n <= 1:
       return n
   else:
       return(fib(n-1) + fib(n-2))

# take input from the user
terms = int(input("How many terms? "))

# check if the number of terms is valid
if nterms <= 0:
   print("enter a positive integer")
else:
   print("Fibonacci sequence:")
   for i in range(terms):
       print(fib(i))