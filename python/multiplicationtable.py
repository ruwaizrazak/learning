#multiplication table upto 10
m=input("enter the number")
count=1
while (count <= 10):
	ans = m * count
	print ("{0:0d} X {1:0d}  = {2:0d}".format(m,count,ans))