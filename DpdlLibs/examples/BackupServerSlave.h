# File: BackupServerSlave.h
# Date: 03.09.2009
# Dldl-Example: Backup server slave
# Author: ACosta
# e-mail: info@seesolutions.it
#
#
include("dpdlMIDP.h")
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

func saveData(string data)
     if(COPY_DATA != -1)
         int id = addRecord(COPY_DATA, data)
         if(FILE_STORE != -1)
              string str_csv = "" + id + "%" + data + "\n"
              write(FILE_STORE, str_csv)
         endif
         #printlnScreen("rec ID:" + id)
         #printlnScreen("data saved")
     endif
endfunc

func processClients()
     string tx, rx
     printlnScreen("Connecting reachable devices...")
     #s2 = connectServerDevices()
     #printlnScreen("ready to read()" + s2)
     #sleep(3000)
     #we face the old server functions (see BackupServer.h)
     s1 = dpdlTrue
     s2 = dpdlTrue
     if s1 && s2 && (client != -1)
         rx = readClientData(client)
         printlnScreen("rx: " + rx)
         if (rx == "backup_cmd")
             s3 = sendClientData(client, "ok_cmd")
             printlnScreen("bt communication status: " + s3)
             rx = readClientData(client)
             int c_clear = 0
             int max = 10
             int c_ = 0
             #because backup may be interrupted, we define a start off for rest backup
             int start_off = 0
             while(rx != "done_cmd")
                 if((rx != "null") && (rx != BT_TIMEOUT))
                    if(rx != "backup_cmd")
                        if(c_ >= start_off)
                              saveData(rx)
                        endif
                        printScreen(".")
                        c_clear = c_clear + 1
                        c_ = c_ + 1
                        if(c_clear == max)
                            c_clear = 0
                            FormClear(TEXT_LOG)
                            printlnScreen("Cnt:"+c_)
                        endif
                    else
                        printScreen("*")
                    endif
                 endif
                 rx = readClientData(client)
             endwhile
             printlnScreen("DATA Backup completed")
             if(FILE_STORE != -1)
                  close(FILE_STORE)
             endif
             sleep(50000)
         else
             printlnScreen("no proper cmd")
         endif
     else
          printlnScreen("No Client-Device Discovered")
     endif
endfunc

func run()
     printlnScreen("processing Backup-Clients...")
     processClients()
     sleep(2000)
     FormClear(TEXT_LOG)
     return dpdlTrue
endfunc

#start of execution
#TEXT_LOG ->loaded statically at index 1, see BackupServer.h_static
#this will be replaced by getStaticContext("TEXT_LOG")
int client = 0
int TEXT_LOG = 1
int COPY_DATA = 0
#in addition we store it also in .csv format
int FILE_STORE = -1
#status vars
int s1, s2, s3, s4, s5, s6 = 0
#we set the polling and timeout values to 10*100ms, internally readClientData(..)
#runs every 100 ms for 10 times, until a data unit is buffered, usually at 1st time
setRxTimeout(10, 100)
int x = run()
