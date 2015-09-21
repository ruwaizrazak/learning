#finding max and second max in an array
L=[1,2,4,9,6,5]
i=max(L) #max number in list
print(i)
L.remove(i) #removing the max number from list
j=max(L) #now finding the second max number in list
print(j)