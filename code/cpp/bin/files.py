
import os
import shutil
import re
import sys
import time
import utils
import text


#**************************
#*** FileUtil functions ***
#**************************


def FileExists(fullFileName):
	bFileExists	= 1
	try				: os.stat(fullFileName)
	except OSError	: bFileExists = 0
	return bFileExists


def DeleteFile(fullFileName, bDry= 0):
	#cmd = "rm -f %s" % (fullFileName)
	#utils.RunOsSystem(cmd, bDry, 0)
	os.remove(fullFileName)
	
def MakeFileWritable(fullFileName):
	fullFileName = text.ConvertToBackwardSlashes(fullFileName)
	fullFileName = fullFileName.replace("\\", "\\\\")
	cmd = "attrib -R %s" % (fullFileName)
	os.system(cmd)

def SafeDeleteFile(fullFileName, bDry= 0):
	if FileExists(fullFileName):
		MakeFileWritable(fullFileName)
		DeleteFile(fullFileName, bDry)


def MakeFileExecuteable(fullFileName):
	return # Windows version :-)
#
#	# Cygwin version
#	cmd = "chmod a=rwx %s" % (fullFileName)
#	os.system(cmd)




def SafeMakeDirs(path):
	""" Makes all dirs in path."""
	if FileExists(path): return
	try:		os.makedirs(path)
	except:		print



def SafeDeletePath(fullPathName):
	SafeMakeDirs(fullPathName)
	shutil.rmtree(fullPathName)
#	try				: shutil.rmtree(fullPathName)
#	except OSError	: print "ERROR Deleting Path: " + fullPathName


 

#****************************
#*** File Stats Functions ***
#****************************



#********************************
#*** File/Dirs Copy Functions ***
#********************************

def forceCopyFile(srcFile, dstFile):
	try:
		shutil.copy(srcFile, dstFile)
	except IOError:
		print "Safe Copy!" 

def forceRemoveTree(dir):
	if os.path.exists(dir):
		shutil.rmtree(dir)	

def forceCopyTree(srcDir, dstDir):
	if os.path.exists(dstDir):
		shutil.rmtree(dstDir)	
	shutil.copytree(srcDir, dstDir)



def zipDir(dirToZip, zipFile, bDry):
	""" Zips files in dir to a zip file."""

	saveDir = os.getcwd()		# Save current directory
	os.chdir(dirToZip)
	
	try		:	os.remove(zipFile)
	except	:	print "Note: File %s does not exist!" % (zipFile)

	cmdLine = "find -iname '*.*' | zip -q -@ %s" % (zipFile)

	print cmdLine
	Print("Packing to zip file %s... " % (zipFile), 0)
	utils.RunOsSystem(cmdLine, bDry, 0)
	os.chdir(saveDir)			# restore original dir
	print "Done"




