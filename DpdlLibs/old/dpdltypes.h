#DpdlLib V1.0      info@seesolutions.it
#
#Author: Armin Costa
#
#This library comes with the standard Dpdl core Engine, written in Dpdl-Control-Scripting.
#It contains basic system abstraction functions and internal system variables.
#
#Filename: dpdltypes.h
#
#return int array pos
func allocArr(int pos, int minSize)
     return allocMemArray(pos, minSize)
endfunc

func sizeArr(int pos)
     return getMemArraySize(pos)
endfunc

#return int element index
func putArrInt(int pos, int val)
     return putMemArrayInt(pos,  val)
endfunc

#return int element value
func getArrInt(int pos, int index)
     return getMemArrayInt(pos, index)
endfunc

#return int element index
func putArrStr(int pos,  string val)
     return putMemArrayStr(pos,  val)
endfunc

#return string element value
func getArrStr(int pos, int index)
     return getMemArrayStr(pos, index)
endfunc

func setLock()
    dpdlLOCK = 1
endfunc

func releaseLock()
    dpdlLOCK = 0
endfunc

func getLock()
     return dpdlLOCK
endfunc

func releaseLock()
    dpdlLOCK = 0
endfunc


func createThread(int instance, string script_file, int priority, int milliseconds)
    return DPDLAPI_createThread(instance, script_file, priority, milliseconds)
endfunc


func deleteThread(int id)
       return DPDLAPI_deleteThread(id)
endfunc


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



