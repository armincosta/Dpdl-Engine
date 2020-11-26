#DpdlLib V1.0      info@seesolutions.it
#
#Author: Armin Costa
#
#This library is implemented with Dpdl-Control-Script and comes with the standard Dpdl core Engine,
#It contains basic system abstraction functions and internal system variables.
#
#Filename: dpdllib.h
#License: GNU GPL
#
include("dpdltypes.h")
function chunkAlloc(string pkgname, string chunk)
         int status = DPDLAPI_mallocDpdlService(pkgname)
         println("done malloc()")
         if status == dpdlTrue
              DPDLAPI_swapDpdlChunk(pkgname, chunk)
              println("chunkAlloc OK")
              return dpdlTrue
         else
              println("no need for chunk allocation, OK")
              return dpdlFalse
         endif
end

function searchData(string pkgName, string chunk, string constraint)
    int status = DPDLAPI_selectDpdlService(pkgName, chunk, constraint)
    if status == dpdlTrue
         DPDLAPI_projectData(chunk, constraint)
         if DPDLAPI_getDataState() == dpdlTrue
             println("Results ready")
             return dpdlTrue
         endif
         return dpdlFalse
    else
         println("error in quering Data")
         return dpdlFalse
    endif
end

function openLogFile(string file)
   dpdlHFILE = open(file, "w")
   return dpdlHFILE
end

function logToFile(string data)
    if dpdlHFILE == -1
       dpdlHFILE = open(file, "w")
       write(dpdlHFILE, data)
       println("data written")
    else
       write(dpdlHFILE, data)
    endif
end


#system variable definition
string DpdlLibVersion = "1.0"
int engineID = 0

#start Library execution
int dpdlHFILE = -1






