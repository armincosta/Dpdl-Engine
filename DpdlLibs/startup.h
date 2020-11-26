#
# File: startup.h
#
# Example startup script that starts a dedicated Thread running BTObexServer.h
#
# Author: A.Costa
# e-mail: armincosta(_a_t_)seesolutions.it
#
# License: GNU GPL
#
#
include("dpdllib.h")
function printlnScreen(string m)
     println(m+"\n")
end

function printScreen(string m)
     print(m)
end

#begin of execution
string dpdl_script = "examples/DpdlScripting/BTObexServer.h"

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
    printlnScreen("ERROR in creating BTObexServer Thread is script " + dpdl_script)
endif
printlnScreen("--------------------------")



