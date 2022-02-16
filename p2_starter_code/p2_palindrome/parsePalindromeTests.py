import re

infile = open("sentence-palindromes.txt", 'r')
outfile = open("sentence-palindromes-modified.txt", 'w')

st = []

n_vp = 0

for each in infile:
	if each[0] == '*' and each[1] == '*':
		print(each, end = '', file = outfile)
		continue
	tempstr = ""
	for c in each:	
		if ord(c.lower()) <= 122 and ord(c.lower()) >= 97 or ord(c.lower()) == 32:
			#print(c, ord(c.lower()))
			tempstr+= c
		else:
			pass
	
	row = tempstr.split()
	
	addRow = 1

	for i in range(0, len(row)):
		for j in range(0, len(row)):
			if i != j and row[i].lower() == row[j].lower():
				# do not print row
				addRow = 0

	if addRow:
		n_vp += 1
		print(tempstr, file=outfile)

print("** ** ** Total valid palindromes for ECE 0302 palindrome program:", n_vp, "** ** **", file = outfile)
print("** ** ** Total valid palindromes for ECE 0302 palindrome program:", n_vp, "** ** **")
		
	