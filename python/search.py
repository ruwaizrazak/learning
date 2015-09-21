#search for string in a string
searchkey=input("enter the string term you want to search") #enter the term within "" double quotes.
phrase="hey world, hows the python moves?"
if searchkey in phrase:
	print("search successful")
	l=phrase.find(searchkey) 
	print("search key lies at %d th position" %l)