#search in an integer array
searchkey=input("enter the integer you want to search") #enter the term within "" double quotes.
l=[1,2,4,3,43]
if searchkey in l:
	print("search successful")
	m=l.index(searchkey) #for displaying index
	print("search key lies at %d th position" %m)
else:
	print("number not found")