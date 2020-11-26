#DpdlLib V1.0      info@seesolutions.it
#
#Author: Armin Costa
#
#This library comes with the standard Dpdl core Engine, written in Dpdl-Control-Scripting.
#It contains basic system abstraction functions and internal system variables.
#
#Filename: dpdltypes.h
#License: GNU GPL
#
#return int array pos
function allocArr(int pos, int minSize)
     return allocMemArray(pos, minSize)
end

function sizeArr(int pos)
     return getMemArraySize(pos)
end

#return int element index
function putArrInt(int pos, int val)
     return putMemArrayInt(pos,  val)
end

#return int element value
function getArrInt(int pos, int index)
     return getMemArrayInt(pos, index)
end

#return int element index
function putArrStr(int pos,  string val)
     return putMemArrayStr(pos,  val)
end

#return string element value
function getArrStr(int pos, int index)
     return getMemArrayStr(pos, index)
end

function sleep(int milliseconds)
     sleepNative(milliseconds)
end

function setLock()
    dpdlLOCK = 1
end

function releaseLock()
    dpdlLOCK = 0
end

function getLock()
     return dpdlLOCK
end

function releaseLock()
    dpdlLOCK = 0
end


function createThread(int instance, string script_file, int priority, int milliseconds)
    return DPDLAPI_createThread(instance, script_file, priority, milliseconds)
end


function deleteThread(int id)
       return DPDLAPI_deleteThread(id)
end


#start of execution, LOCK is unused at beginning
int dpdlLOCK = 0
int dpdlthreadCount = 0
int dpdlTrue = 1
int dpdlFalse = 0
string dpdlNull = "null"
int dpdlNotFound = -2
int dpdlError = -1

#Thread variables
int dpdlMinPriority = 1
int dpdlMaxPriority = 10
int dpdlNormPriority = 5



