# File: startup.h
# Date: 03.09.2009
#
# Function: Startup code for the DpdlEngine if EXEC_STARTUP_CODE is true
#
# In this example we create a console for allocating and querying a phone-book example (dpdl_PHONEBOOK.c)
# NOTE: The Dpdl service dpdl_PHONEBOOK part of the example must be installed manually via DpdlClient console
#
# Author: ACosta
# e-mail: info@seesolutions.it
#
#
include("dpdllib.h")
func printlnScreen(string m)
     println(m+"\n")
endfunc

func printScreen(string m)
     print(m)
endfunc

#begin of execution
string dpdl_script = "examples/BTObexServer.h"

int commThread = 0
printlnScreen("--------------------------")
printlnScreen("init() startup.h")
printlnScreen("please wait while initializing " + dpdl_script)
int DELAY_PAUSE = 1000
int SERVER_REFRESH = 5000
int server = -1

server = createThread(commThread, dpdl_script, dpdlNormPriority, SERVER_REFRESH)
if server == dpdlTrue
    printlnScreen(dpdl_script + " inited: " + server + " Thread interval: " + SERVER_REFRESH + " ms")
else
    printlnScreen("ERROR in starting " + dpdl_script)
endif
printlnScreen("--------------------------")



