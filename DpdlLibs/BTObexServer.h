#
# File: BTObexServer.h
#
# Obex server application that reads messages from a store and sends them via bluetooth
#
# Author: A.Costa
# e-mail: armincosta(_a_t_)seesolutions.it
#
# License: GNU GPL
#
#
include("dpdlMIDP.h")
function printlnScreen(string m)
     if TEXT_LOG != -1
         int x =  FormAppend(TEXT_LOG, m+"\n")
     else
         println(m)
     endif
end

function printScreen(string m)
     if TEXT_LOG != -1
        int x = FormAppend(TEXT_LOG, m)
     else
         print(m)
     endif
end

function sendImportantMsg(string dev)
     int status_send = dpdlFalse
     int id = -1
     string d = dpdlNull
     string msg_to = dpdlNull
     int cnt_ = 0
     if(MSG_QUEUE_HIGH != -1)
        printlnScreen("Important Msgs -------------")
        DPDLLIB_rebuildEnum(MSG_QUEUE_HIGH)
        int nr_ = getEnumNrRecords(MSG_QUEUE_HIGH)
        printlnScreen("# Msgs in Queue HIGH: " + nr_)
            cnt_ = nr_-1
            while cnt_ < nr_
                id = getNextRecordID(MSG_QUEUE_HIGH)
                printlnScreen("next recID: " + id)
                if id != -1
                  d = getRecord(MSG_QUEUE_HIGH, id)
                  msg_to = "Notification Message: \n  "+d+"\n\n  <time sent:  " + getTime() + "  >"
                  printlnScreen("msg: " + msg_to)
                  status_send = DPDLAPI_sendObex(dev, dpdlTrue, msg_to)
                endif
                cnt_ = cnt_+1
                sleep(1000)
            endwhile
            printlnScreen("Status sending: " + status_send)
     endif
end


function run()
     #first we clear the previous log
     FormClear(TEXT_LOG)
     s1 = searchServerDevices()
     int status_discovery = 0
     int service_discovery = 0
     int counter_ = 0
     string dev = "n"
     while (status_discovery != 1) && (service_discovery != 1)
         status_discovery = discoveryFinished(BT_SERVER_MODE)
         service_discovery = serviceDiscoveryFinished(BT_SERVER_MODE)
         printScreen(".")
         sleep(2000)
         counter_ = counter_+1
     endwhile
     println("")
	 int dev_found = 0
     while(dev != "null")
          dev = DPDLAPI_getServerVisibleBTAddr()
          if(dev != "null")
              println("dev visible: " + dev)
			  dev_found = dev_found + 1
			  println("sending data...")
			  sendImportantMsg(dev)
          endif
     endwhile
	 if(dev_found == 0)
		println("No device found")
	 endif
     return dpdlTrue
end

#start of execution
#this will be replaced by getStaticContext("TEXT_LOG")
int TEXT_LOG = 1
int MSG_QUEUE_HIGH = 0
int s1, s2, s3, s4, s5, s6 = 0
#we set the polling and timeout values to 10*100ms, internally readClientData(..)
#runs every 100 ms for 10 times, until a data unit is buffered, usually at 1st time
setRxTimeout(10, 100)
int x = run()
