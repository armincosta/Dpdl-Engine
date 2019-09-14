#
# File: bluetoothDeviceDetectionExample.h
#
# Bluetooth device detection example written in Dpdl
#
# Author: A.Costa
# e-mail: armincosta(_a_t_)seesolutions.it
#
# License: GNU GPL
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

func detect()
     string tx, rx
     printlnScreen("Connecting reachable devices...")
     s2 = connectServerDevices()
     printlnScreen("ready to read(): " + s2)
     sleep(1500)
     if s1 && s2
         tx = dpdl_echo
         s3 = sendServerData(tx)
         if(s3 == dpdlTrue)
               setStartTime()
               rx = readServerData()
               if(rx == dpdl_echo)
                      int ms_ = getEndTime()
                      printlnScreen("Freq. Time(ms): " + ms_)
                      int counter_ = 0
                      int max_polls = 10
                      while(counter_ < max_polls)
                            s4 = sendServerData(tx)
                            setStartTime()
                            rx = readClientData(bt_client)
                            if(rx == dpdl_echo)
                                 int ms_ = getEndTime()
                                 printlnScreen("Polling(ms): " + ms_)
                            endif
                            counter_ = counter_+1
                      endwhile
                      sleep(500)
               else
                     printlnScreen("Status: Timeout")
               endif
         else
              printlnScreen("No Device Detected")
         endif
     else
         printlnScreen("No Connection")
     endif
endfunc

func run()
     #first we clear the previous log
     FormClear(TEXT_LOG)
     s1 = searchServerDevices()
     int status_discovery = 0
     int service_discovery = 0
     while (status_discovery != 1) && (service_discovery != 1)
         status_discovery = discoveryFinished(BT_SERVER_MODE)
         service_discovery = serviceDiscoveryFinished(BT_SERVER_MODE)
         printScreen(".")
         sleep(500)
     endwhile
     printlnScreen("processing detected Devices")
     detect()
     return dpdlTrue
endfunc


#module entry point
int TEXT_LOG = 1
int s1, s2, s3, s4, s5, s6 = 0
#2 seconds
setRxTimeout(10, 200)
int x_ = run()
