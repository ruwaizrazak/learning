def fact(n):
   if n == 1:
       return n
   else:
       return n * fact(n-1)

n = input("print the value of n")
i = 0
sum = 0
while (i <= n):
	a=fact(i)
	b=float (i)/ float (a)
	sum = float(sum) + float(a)
print(sum)
