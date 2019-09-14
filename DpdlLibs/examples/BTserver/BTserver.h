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

func initFileStore()
    string fn = "./Test/BTdevices.csv"
    println("opening file stream>>"+fn)
    int file_h = open(fn, "w")
    println("File Store .csv opened")
    return file_h
endfunc

func saveData(string data)
     if(COPY_DATA != -1)
         printlnScreen("saving data...")
         int id = addRecord(COPY_DATA, data)
         if(FILE_STORE != -1)
              string str_csv = "" + id + ";" + data + "\n"
              write(FILE_STORE, str_csv)
         endif
         printlnScreen("rec ID:" + id)
     endif
endfunc

func saveDevicesFound()
	 string dev = "n"
	 int dev_found = 0
     while(dev != "null")
          dev = DPDLAPI_getServerVisibleBTAddr()
          if(dev != "null")
              println("dev visible: " + dev)
              saveData(dev)
			  dev_found = dev_found + 1
          endif
     endwhile
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
         if (rx == "ping")
             s3 = sendServerData("pong")
             printlnScreen("bt communication status: " + s3)
             sleep(5000)
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
           printlnScreen("processing BT-Clients...")
           sleep(15000)
           saveDevicesFound()
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
int FILE_STORE = initFileStore()
#status vars
int s1, s2, s3, s4, s5, s6 = 0
#we set the polling and timeout values to 10*100ms, internally readClientData(..)
#runs every 100 ms for 10 times, until a data unit is buffered, usually at 1st time
setRxTimeout(10, 100)
int x = run()
