import os
import re

PkgConfigDir="SDL2_Library/lib/pkgconfig"

def FixAbsolutePath(filename):	
	# open file with r+b (allow write and binary mode)
	f = open(filename, 'r+b')   
	# read entire content of file into memory
	lines = f.readlines()
	#find the line that define prefix and fix it
	PrefixFoundFlag = False
	for i in xrange(len(lines)):
		if re.match(r'^prefix=', lines[i]) and not PrefixFoundFlag:
			PrefixFoundFlag = True
			CurrentPath=os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(filename))))
			lines[i] = 'prefix=' + CurrentPath + '\n'
			break
	assert PrefixFoundFlag, "Can't find line prefix= in file " + os.path.dirname(os.path.abspath(filename))
	# return pointer to top of file so we can re-write the content with replaced string
	f.seek(0)
	# clear file content 
	f.truncate()
	# re-write the content with the updated content
	for line in lines:
		f.write(line)
	# close file
	f.close()
	
for file in os.listdir(PkgConfigDir):
	if file.endswith(".pc"):
		FixAbsolutePath (PkgConfigDir + "/" + file)
        

