
import os
import shutil
import re
import sys
import time

#***********************
#*** Print Functions ***
#***********************
def Print(str, bInsertNewLine= 1):
	""" Prints the string to std_out and calls flush. """
	if bInsertNewLine:
		print str
	else:
		print str,
	sys.stdout.flush()


#***********************************
#*** File/Path Name Manipulation ***
#***********************************


def ConvertToForwardSlashes(fileName):
	""" Slashes stuff ... '\' and '/'.
		Convert to forward slashes. """
	fileNme = fileName.replace("\\", "/")
	return fileNme


def ConvertToBackwardSlashes(fileName):
	""" Slashes stuff ... '\' and '/'.
		Convert to backward slashes. """
	fileNme = fileName.replace("/", "\\")
	return fileNme


def SplitFileNameToPathAndName(fileName):
	""" Splits a scene name form ('Singleplayer/C03A/FF-C03A_MAIN') in to 
		path and name like this: returns tuple (Singleplayer/C03A/ , FF-C03A_MAIN)."""
	
	fileNameScan	= re.compile(r"(.*)[/\\]([^/\\]*)$", re.I)

	match			= fileNameScan.match(fileName)
	try:			path = match.group(1) + "/"
	except:			path = ""

	try:			name = match.group(2)
	except:			name = fileName

	return path, name


def GetPathOfFile(fileName):
	""" Returns the path of a file. """
	fileName = os.path.abspath(fileName)
	path, name = SplitFileNameToPathAndName(fileName)
	return path


def RemovePathFromFileName(fileName):
	""" Removes the path section of a file name and returns just the name. """
	path, name = SplitFileNameToPathAndName(fileName)
	return name


def removeLastSlashFromPathName(pathName):
	""" """
	#pathNameScan	= re.compile(r"(.*)[/\\]([^/\\]*)$", re.I)
	pathNameScan	= re.compile(r"(.*)[/\\]$", re.I)

	match			= pathNameScan.match(pathName)
	try:			path = match.group(1)
	except:			path = pathName

	return path


def InsertEndSlashInPathName(pathName):
	""" Inserts an end slash '/' at the end of the path name or changes 
		to a '/' if the last char in pathname is a backslash '\'. """
	
	path = pathName
	
	lenName		= len(pathName)
	lastChar	= lenName -1
	
	path = ""
	for i in range(0,lenName):
		if i == lastChar:
			if pathName[i] == '/':
				path += pathName[i]
#			elif pathName[i] == r'\'
#				path += '/'
			else:
				path += pathName[i]
				path += '/'
		else:
			path += pathName[i]

	return path



def GetParentAndLeafDir(pathName):
	""" Gets the parent dir of a directory. Also gets
		the leaf dir. Eg. if orgPath = 'q:/freedomfighter/final/'.
		Then this function returns ('q:/freedomfighter/', final/'). """
	
	pathName = RemoveLastSlashFromPathName(pathName)
	parentPath, leafPath = SplitFileNameToPathAndName(pathName)

	leafPath = InsertEndSlashInPathName(leafPath)
	parentPath = InsertEndSlashInPathName(parentPath)

	return parentPath, leafPath
		

def ConvertToWindowsPath(path):
	path = path.replace("/", "\\")
	#path = path.replace("\\", "\\\\") # only needed when running under Cygwin
	return path



def ConvertToWindowsNetPath(netPath):
	netPath = netPath.replace("//", "\\\\")
	netPath = netPath.replace("/", "\\")
	netPath = RemoveLastSlashFromPathName(netPath)	# Experimental XX but hopefully works
	return netPath


def ConvertToCygwinPath(path):
	""" Converts a windows style path with drive letter to cygwin path.
		Fx. 'z:/code/engine' -> '/cygdrive/z/code/engine/'. Needed eg. 
		when modifying PATH environment variable. """
	
	return path	# XXXXXXXXXXXXXXXX	 

	if path == "": return path
	driveLetter = path[0]
	replaceStr	= "%s:/" % (driveLetter)
	path = path.replace(replaceStr, "/cygdrive/%s/" % (driveLetter))
	return path


# ******************************
# *** Run commands functions ***
# ******************************

def RunOsSystem(cmd, bDry, bPrintCmd):
	""" Runs the command using 'os.system()' but only if bDry is not set. """

	if bPrintCmd:
		Print(cmd)

	if bDry	:	
		return
	else	:	
		return os.system(cmd)


def RunOsPopen(cmd, bDry=0, bPrintCmd = 1):
	""" Runs the command using 'os.popen()' but only if bDry is not set. """

	if bPrintCmd:
		Print(cmd)

	if bDry	:	
		return os.popen("")
	else	:	
		return os.popen(cmd)


def RunOsPopen2(cmd, bDry=0, bPrintCmd = 1):
	""" Runs the command using 'os.popen2()' but only if bDry is not set. """

	if bPrintCmd:
		Print(cmd)

	if bDry	:	
		return os.popen2("")
	else	:	
		return os.popen2(cmd)



def RunOsPopen3(cmd, bDry=0, bPrintCmd = 1):
	""" Runs the command using 'os.popen3()' but only if bDry is not set. """

	if bPrintCmd:
		Print(cmd)

	if bDry	:	
		return os.popen3("")
	else	:	
		return os.popen3(cmd)




#*******************************
#*** Drive Related Functions ***
#*******************************

def SubstDrive(driveLetter, path, bDry = 0):
	""" Subst a path to a driveLetter. The driveLetter is 
		first 'un-substed'. """
	path	= RemoveLastSlashFromPathName(path)
	cmd		= 'subst %s: /D' % (driveLetter[0])
	RunOsSystem(cmd, bDry, 0)
	cmd		= 'subst %s: %s' % (driveLetter[0], path)
	RunOsSystem(cmd, bDry, 0)


#**************************
#*** Registry functions ***
#**************************

def RegAdd(keyName, valueName, type, data, bForce=1, bDry=0):
	""" Adds keyName, but only if bDry is not set. """
	import sys_conf

	strForce = ""
	if bForce:	strForce = '/f'
	cmd	= '"%s" ADD "%s" /v "%s" /t %s /d "%s" %s  ' % (sys_conf.g_regExe, keyName, valueName, type, data, strForce)
	RunOsSystem(cmd, bDry, 0)



#*********************
#*** ENV functions ***
#*********************
def AddToSystemPath(path):
	""" Adds the specified path to the system path. """
	
	path = ConvertToCygwinPath(path)
	sysPath = '%s:%s' % ( os.environ["PATH"], path)
	os.environ["PATH"] = sysPath


#*********************************
#*** Agument related functions ***
#*********************************


def CheckArg(cmd_args, arg):
	""" Looks for 'arg' in cmd_args then returns a boolean value 
		indicating whether the arg was set or not. """
	bSet = 0
	if  arg in cmd_args:
		bSet = 1
	return  bSet


def CheckAndRemoveArg(cmd_args, arg):
	""" Looks for 'arg' in cmd_args and removes it if present.
		Then returns a boolean value indicating whether the 
		arg was set or not. """
	
	bSet = 0
	if  arg in cmd_args:
		cmd_args.remove(arg)		# Remove arg from cmd_args
		bSet = 1
	return  bSet


def FindAndRemoveArg(cmd_args, arg, default=""):
	""" Looks for 'arg' in cmd_args and removes it if present.
		Then returns the argument if found, otherwise default
		string is returned. """
	
	bFoundArg = CheckAndRemoveArg(cmd_args, arg)
	if bFoundArg:
		return arg
	else:
		return default


def	FindAndRemoveIntegerArg(cmd_args, iDefault = 0):
	""" Search thru command line for a valid integer and returns it. If none 
		is found iDefault is returned. """ 

	bFoundValidInt	= 0
	iRetVal			= iDefault
	for arg in cmd_args:
		try:
			bFoundValidInt	= 1
			iRetVal			= int(arg)
		except ValueError:
			bFoundValidInt	= 0
			iRetVal			= iDefault
		
		if bFoundValidInt:
			break
	
	if bFoundValidInt:
		cmd_args.remove(arg) 

	return iRetVal



def CheckAndRemoveDryCmd(cmd_args):
	""" Looks for 'dry' in cmd_args and remove it if present.
		Modify cmd_args and return aboolean value for the dry parameter.
		\return bDry"""
	return CheckAndRemoveArg(cmd_args, "dry")


def GetParamOfArg(arg, cmd_args):
	""" Looks for arg in command args and returns the argument following
		it (ie. parameter of the arg) if it exists, or default. """

	strParam = ""
	lastArg = len(cmd_args)-1
	for i in range(0, len(cmd_args)):
		if ( (cmd_args[i] == arg) and (i != lastArg) ):
			strParam = cmd_args[i+1]

	return strParam



def CheckForInteractiveConfig(cmd_args, localConfFile, options, optionsSeq, script_name, bDry):
	""" If '-i' in command args then interactive configuration of BOTH the 
		'prj_paths_conf.py' and the localConf-file is performed. If the 
		'prj_paths_conf.py' file does not exist in the buildscripts dir, 
		then interactive configuration of this file is performed. """

	import prj_paths, sys_conf, conf_writer, files

	prjPathsConfFile	= sys_conf.g_buildScriptsPath + "prj_paths_conf.py"
	localConfFile		= sys_conf.g_buildScriptsPath + localConfFile
	bDoPrjPathsConf		= 0
	bDoLocalConf		= 0
	if  CheckAndRemoveArg(cmd_args, "-i"):	# If interactive mode explicitly requested
		bDoPrjPathsConf = 1
		bDoLocalConf	= 1

	if not files.FileExists(prjPathsConfFile):
		bDoPrjPathsConf = 1

	if (not files.FileExists(localConfFile)) and (len(cmd_args) == 0):
		bDoLocalConf = 1
	
	if  bDoLocalConf:
		conf_writer.SetOptions(localConfFile, options, optionsSeq, script_name, bDry)

	if  bDoPrjPathsConf:
		prj_paths.SetProjectPathsInteractively(bDry)


def GetSceneNameFromCommandLine(cmd_args):
	""" Tries to find the first valid scene alias from the command line and returns	
		the full scene name as a string. Otherwise an empty string is returned."""
	import globals
	scenes_list		= globals.GetScenesFromAliasList(cmd_args)
	if (len(scenes_list) == 0):
		print "Please specify valid scene alias :-)"
		sys.exit(0)
	return scenes_list[0]


def GetLocaleStringFromCommandLine(cmd_args):
	""" Looks for 'english', 'french', 'german', 'spanish' , 'italian'
		and returns the one found. Returns 'english' if none 
		of the legal ones are found."""
	if		CheckAndRemoveArg(cmd_args, "french")	: return "french"
	elif	CheckAndRemoveArg(cmd_args, "german")	: return "german"
	elif	CheckAndRemoveArg(cmd_args, "spanish")	: return "spanish"
	elif	CheckAndRemoveArg(cmd_args, "italian")	: return "italian"
	elif	CheckAndRemoveArg(cmd_args, "english")	: return "english"
	else											: return "english"

	

def GetPlatformStringFromCommandLine(cmd_args):
	""" Looks for 'pc', 'ps2', 'xb', 'ngc' and returns the one found. 
		Returns 'pc' if none of the legal ones are found. The returned 
		argument is removed."""
	if		CheckAndRemoveArg(cmd_args, "ngc")	: return "ngc"
	elif	CheckAndRemoveArg(cmd_args, "xb")	: return "xb"
	elif	CheckAndRemoveArg(cmd_args, "ps2")	: return "ps2"
	elif	CheckAndRemoveArg(cmd_args, "pc")	: return "pc"
	else										: return "pc"


def GetPlatformListFromCommandLine(cmd_args):
	""" Looks for 'pc', 'ps2', 'xb', 'ngc' and returns a list with the ones found. 
		Returns ['pc'] if none of the legal ones are found. The found arguments are
		removed from cmd_args list."""
	platformList = []
	if		CheckAndRemoveArg(cmd_args, "pc")	: platformList.append("pc")
	if		CheckAndRemoveArg(cmd_args, "ps2")	: platformList.append("ps2")
	if		CheckAndRemoveArg(cmd_args, "xb")	: platformList.append("xb")
	if		CheckAndRemoveArg(cmd_args, "ngc")	: platformList.append("ngc")
	if ( len(platformList) == 0): platformList.append("pc")
	return platformList


def GetVideoModeFromCommandLine(cmd_args):
	""" Looks for 'pal', or 'ntsc' 'ntsc' if none of the legal ones are found. 
		The returned argument is removed."""
	if		CheckAndRemoveArg(cmd_args, "pal")	: return "pal"
	elif	CheckAndRemoveArg(cmd_args, "ntsc")	: return "ntsc"
	else										: return "ntsc"


def GetBuildNameFromCommandLine(cmd_args, default = ""):
	""" Looks for 'build_name NameOfBuild' and returns NameOfBuild if present.
		Otherwise default is returned. Both build_name and NameOfBuild 
		are removed afterwards. """

	sNameOfBuild = GetParamOfArg("build_name", cmd_args)
	if sNameOfBuild != "":
		cmd_args.remove(sNameOfBuild)
	else:
		sNameOfBuild = default
	if "build_name" in cmd_args: cmd_args.remove("build_name")

	return sNameOfBuild



#***************************************
#*** ZDebug Output Parsing Functions ***
#***************************************
def Find(lines, string):
	""" Looks for string in lines and returns true if found, otherwise false."""
	bFound	= 0
	for line in lines:
		if ( line.find(string) != -1):
			bFound = 1
	return bFound


def FindI(lines, string):
	""" Looks for string in lines and returns true if found, otherwise false.
		IGNORES CASE"""

	foundScan		= re.compile(string, re.I)
	bFound = 0
	for line in lines:
		if foundScan.match(line):
			bFound = 1
	return bFound



#***********************************************
#*** PC freedomfighter exe related functions ***
#***********************************************
def GetPcGameCmd(configStr, sceneFileStr, runModeStr, allWaysPackStr, gameControllerStr, localeStr, stressTestStr, autoExitStr, bSmallStream):
	""" For composing commands for executing 'freedomfighter.exe' for either 
		packing or running scenes (on PC). 
		
		configStr	: Either 'release' (default) or 'debug'. Which version of the game exe You want 
		sceneFileStr: A valid scene name without extension (fx. 'Singleplayer/C01A/FF-C01A_MAIN')	 
		runModeStr Options: 
			'rn'	: Run normal
			'rppc'	: Run packed scene on PC
			'ppc'	: Pack scene for PC
			'pps2'	: Pack scene for PS2
			'pxb'	: Pack scene for XBox
			'pgc'	: Pack scene for GameCube (Not implemented yet)
		allWaysPackStr Options: 
			'ap'	: Enable AllWaysPack in ini-file
			''		: Don't force AllWaysPack
		gameControllerStr Options: 
			'gc'	: Use Game Controller
			''		: Use Mouse
		localeStr Options: 
					: 'english', 'german', 'french', 'spanish', 'italian'
		stressTestStr Options: 
			'-o "ConsoleCmd RunDemo2"'	: Hero runs and shoots along a spline
		autoExitStr Options: 
			'-o "AutoExit 20"'	: Engine exits with msg: "AutoExit Ok" after 20s
		bSmallStream:	Use small streams file (on PS2) XX Not implemented yet XX
		"""
	import globals
	prjPathStr		= RemoveLastSlashFromPathName(globals.g_projectPath)

	# Convert to windoze dir seperator or else our engine assumes that the scene allways needs to be packed
	#sceneFileStr	= sceneFileStr.replace("/", "\\\\")		# CygWin
	#prjPathStr		= prjPathStr.replace("/", "\\\\")		# Way of doing it ....
	
	sceneFileStr	= sceneFileStr.replace("/", "\\")	
	prjPathStr		= prjPathStr.replace("/", "\\")

	localeStr = "-d LOC=%s" % (localeStr)

	runCmd	=	'%s -i %s -dbg_ini -TC' % (globals.GetPcGameExeFile(configStr), globals.g_pcBuildIniFile)
	runCmd	=	runCmd	+\
				' -d PROJECT_PATH=%s -d sf=%s -d %s -d %s -d %s %s -o "%s" -o "%s"' %	\
				(prjPathStr, sceneFileStr, runModeStr, allWaysPackStr, gameControllerStr, localeStr, stressTestStr, autoExitStr)

	return runCmd


#**************************
#*** Main.ini Functions ***
#**************************
def AddBuildNameAndNumberToIniFile(iniFile, buildNameStr, iBuildNumber, iDemoMode):
	""" Opens an ini file and adds buildNameStr and buildNumber, 
		then writes it back to same name and location. """
	import files
	
	lines = open(iniFile, "r").readlines()
	if buildNameStr != "":
		lines.append("BuildVersion %s\n" % (buildNameStr))
	if iBuildNumber > -1:
		lines.append("BuildNumber %d\n" % (iBuildNumber))

	#Set demo mode
	lines.append("demo=%d\n" % (iDemoMode))

	#for line in lines: print line,
	files.SafeDeleteFile(iniFile)	
	open(iniFile, "w").writelines(lines)
		

#****************************
#*** Other Util functions ***
#****************************


def GetDateTime(fTime = 0.0):
	""" return a string with date and time"""
	if fTime == 0.0:
		fTime = time.time()
	return time.strftime("%a_%d_%b_%Y_%H_%M", time.localtime(fTime))

def GetDateSimple(fTime = 0.0):
	""" return a string with date simple numeric format"""
	if fTime == 0.0:
		fTime = time.time()
	return time.strftime("%d_%m_%Y", time.localtime(fTime))


def GetHeadLine(headLine, insertUpdateTime = 0):
	""" return a string with a nice formatted headline :-)."""
	import update
	retHeadLine  = "---------------------------------------------------\n"
	retHeadLine += headLine + ":\n"
	retHeadLine += "Time: " + GetDateTime() + "\n"
	if insertUpdateTime:
		retHeadLine += "Code/GFX updated at: " + update.GetLatestUpdateTime() + "\n"
	retHeadLine += "---------------------------------------------------\n"
	return retHeadLine




