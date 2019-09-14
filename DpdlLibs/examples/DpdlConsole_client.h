#Example: DpdlConsole Client Software
#
#
#www.dpdl.com
#Author: Armin Costa
#
#
include("dpdlMIDP.h")
include("DPDLProt.h")
func printlnScreen(string m)
     if TEXT_LOG != -1
         int x =  FormAppend(TEXT_LOG, m+"\n")
     else
         println(m)
     endif
endfunc

func printScreen(string m)
     if TEXT_LOG != -1
        int x = FormAppend(TEXT_LOG, m)
     else
         print(m)
     endif
endfunc


func startConsoleSession()
         string cmd = "null"
         while(cmd != dpdl_end_cmd)
             printScreen(".")
             cmd = readClientData(client)
             #we poll continuously for input commands from the server
             if(cmd == BT_TIMEOUT)
                 cmd = "null"
             else
                 if(cmd == dpdl_exec_cmd)
                      string script = readClientData(client)
                      if(script != "null" && script != BT_TIMEOUT)
                           printlnScreen(dpdl_exec_cmd)
                           printlnScreen("Script: ")
                           printlnScreen(script)
                           return DPDLAPI_execScript(script)
                      else
                           printlnScreen("no script received: BT_TIMEOUT")
                      endif
                 else if(cmd == dpdl_save_cmd)
                      printlnScreen(dpdl_save_cmd)
                 else
                      printlnScreen("no valid cmd")
                 endif
             endif
             sleep(100)
         endwhile
         return false
endfunc


func run()
     #first we clear the previous log
     FormClear(TEXT_LOG)
     string rx = "null"
     string tx = "null"
     printlnScreen("Sending Session request...")
     tx = dpdl_console_cmd
     int x = sendClientData(client, tx)
     if(x == dpdlTrue)
         rx = readClientData(client)
         while(rx == "null")
             rx = readClientData(client)
             #we force data transfer as this script runs 1 time, no threading
             if(rx == BT_TIMEOUT)
                 rx = "null"
             endif
             sleep(100)
         endwhile
         printlnScreen("tx: " + tx)
         printlnScreen("rx: " + rx)
     else
         printlnScreen("no connection available")
         clearClientTXBuffer(client)
     endif
     if (rx != "null") && (rx != BT_TIMEOUT)
          if(rx == dpdl_ok_cmd)
                setStartTime()
                int s_runtime = startConsoleSession()
                int t_ms = getEndTime()
                printlnScreen("total processing time: " + t_ms + " ms")
                printlnScreen("clearing TX && RX Buffers")
                clearClientTXBuffer(client)
                clearClientRXBuffer(client)
                if(s_runtime == dpdlTrue)
                         printlnScreen("Session terminated successfully OK")
                else
                         printlnScreen("Runtime Error")
                         return dpdlFalse
                endif
                return dpdlTrue
          endif
     else
          printlnScreen("no answer")
     endif
     return dpdlTrue
endfunc


#module entry point
     #client ->loaded statically at index 0, see DSLSClientScript2.h_static
     #this will be replaced by getStaticContext("client")
     int client = 4
     #TEXT_LOG ->loaded statically at index 0, see DSLSClientScript2.h_static
     #this will be replaced by getStaticContext("TEXT_LOG")
     int TEXT_LOG = 4
     #we set the polling and timeout values to 10*100ms, internally readClientData(..)
     #runs every 100 ms for 10 times, until a data unit is buffered, usually at 1st time
     setRxTimeout(10, 100)
     int x__ = run()


