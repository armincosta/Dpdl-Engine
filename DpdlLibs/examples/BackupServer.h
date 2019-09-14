# File: BackupServer.h
# Date: 03.09.2009
# Dldl-Example: Backup server
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
     s2 = connectServerDevices()
     printlnScreen("ready to read()" + s2)
     sleep(4000)
     if s1 && s2
         rx = readServerData()
         printlnScreen("rx: " + rx)
         if (rx == "backup_cmd")
             s3 = sendServerData("ok_cmd")
             printlnScreen("bt communication status: " + s3)
             rx = readServerData()
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
                 rx = readServerData()
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
     #first we clear the previous log
     FormClear(TEXT_LOG)
     s1 = searchServerDevices()
     int status_discovery = 0
     int service_discovery = 0
     int counter_ = 0
     while (status_discovery != 1) && (service_discovery != 1)
         status_discovery = discoveryFinished(BT_SERVER_MODE)
         service_discovery = serviceDiscoveryFinished(BT_SERVER_MODE)
         printScreen(".")
         counter_ = counter_+1
         sleep(500)
     endwhile
     if(counter_ > 3)
           printlnScreen("processing Backup-Clients...")
           sleep(15000)
           processClients()
     endif
     return dpdlTrue
endfunc

#start of execution
#TEXT_LOG ->loaded statically at index 1, see BackupServer.h_static
#this will be replaced by getStaticContext("TEXT_LOG")
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
