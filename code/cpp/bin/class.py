#!/usr/bin/python

import os
import sys
import re
import copy

import utils
import files


class Test:
	# *****************
	# *** Constants ***
	# *****************
	m_sClassHeaderInName    = "ClassName.h"
	m_sClassCppInName       = "ClassName.cpp"

		
	# ************
	# *** Data ***
	# ************
	m_sClassOutName                = ""
	m_sClassInheritName            = ""
	m_cmd_args                     = []
	m_sScriptsPath                 = ""       

	# *******************
	# *** Constructor ***
	# *******************
	def __init__(self, cmd_args):
		self.m_cmd_args = copy.copy(cmd_args)
		self.m_sScriptsPath = utils.GetPathOfFile(sys.argv[0])
		
		utils.CheckAndRemoveArg(self.m_cmd_args, sys.argv[0])	# Remove script name from cmd_args

		if ( len(self.m_cmd_args) == 0 ):
			print "Must specify class name !!"
			print "self.m_sScriptsPath: %s" % (self.m_sScriptsPath)
			
			sys.exit(0)

		self.m_sClassOutName = self.m_cmd_args[0]

		if ( len(self.m_cmd_args) == 2 ):
			self.m_sClassInheritName		= self.m_cmd_args[1]
		else:
			self.m_sClassInheritName		= ""

		print self.m_cmd_args
		self.CheckFilesExist()
		self.CreateHeaderFile()
		self.CreateCppFile()


	def CreateHeaderFile(self):
		sFile = open(self.ClassHeaderInFile(), "r").read()
		sRepName		= self.m_sClassOutName
		sIncludeFile	= ""
		if (self.m_sClassInheritName != "" ):
			sRepName = sRepName + " : public " + self.m_sClassInheritName
			sIncludeFile = '#include "%s"' % (self.ClassInheritHeaderName())
		
		sFile = sFile.replace("$CLASSNAME$", self.m_sClassOutName.upper())
		sFile = sFile.replace("$AuthorName$", "Veriquin")
		sFile = sFile.replace("$ClassName$", sRepName)
		sFile = sFile.replace("$IncludeFile$", sIncludeFile)
			
				
		open(self.ClassHeaderOutFile(), "w").write(sFile)


	def CreateCppFile(self):
		sFile = open(self.ClassCppInFile(), "r").read()
		sInclude = '#include "%s.h"' % (self.m_sClassOutName)
		sFile = sFile.replace("$IncludeOwnHeader$", sInclude)
		open(self.ClassCppOutFile(), "w").write(sFile)


	def CheckFilesExist(self):
		if files.FileExists(self.ClassHeaderOutFile()):
			print "Err File exist: " + self.ClassHeaderOutFile()
			print "Must remove manually"
			sys.exit(0)
		if files.FileExists(self.ClassCppOutFile()):
			print "Err File exist: " + self.ClassCppOutFile()
			print "Must remove manually"
			sys.exit(0)


	# ********************************
	# *** Simple utility functions ***
	# ********************************
	def ClassHeaderInFile(self):
		return self.m_sScriptsPath + self.m_sClassHeaderInName

	def ClassCppInFile(self):
		return self.m_sScriptsPath + self.m_sClassCppInName

	def ClassHeaderOutFile(self):
		return (os.getcwd() + "/" + self.m_sClassOutName + ".h")

	def ClassCppOutFile(self):
		return (os.getcwd() + "/" + self.m_sClassOutName + ".cpp")


	def ClassInheritHeaderName(self):
		return (self.m_sClassInheritName + ".h")
		
	def show(self):
		print "show", self.a
	
	
	



# This check detects that the script is being run stand-alone, rather
# than being imported as a module.
if __name__ == '__main__':
	#Main(sys.argv)
	Test(sys.argv)



