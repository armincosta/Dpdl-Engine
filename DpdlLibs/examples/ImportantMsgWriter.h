include("dpdlMIDP.h")
func saveMsg(string m)
    if(MSG_RS != -1)
         int idx = addRecord(MSG_RS, m)
         println("msg saved: " + m)
    endif
endfunc

func startWriter()
   string msgz = dpdlNull
   println("enter a msg to broadcast (q == quit):")
   while(running)
        msgz = readln()
        if(msgz == "q")
           running = dpdlFalse
        else
            saveMsg(msgz)
        endif
   endwhile
endfunc

#entry point
int MSG_RS = 0
int running = dpdlTrue
startWriter()



