# File: bluetoothDiscoverySave.h
# Date: 02.10.2019
# Dldl-Example: Discovery of bluetooth devices
# Author: ACosta
# e-mail: info@seesolutions.it
#
#
include("dpdllib.h")
include("dpdlBT.h")
include("dpdlRS.h")
func runDiscovery()
     int s1 = searchServerDevices()
     int status_discovery = 0
     int service_discovery = 0
     int counter = 0
     if(s1 == dpdlTrue)
	     while (status_discovery != 1) && (service_discovery != 1)
	         status_discovery = discoveryFinished(BT_SERVER_MODE)
	         service_discovery = serviceDiscoveryFinished(BT_SERVER_MODE)
	         print(".")
	         counter = counter+1
	         sleep(3000)
	     endwhile
     else
     	println("No working Bluetooth stack found")
     endif
endfunc

func showDevicesFound()
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

func saveData(string data)
     if(BT_DEV_RS != -1)
         int id = addRecord(BT_DEV_RS, data)
         println("rec ID:" + id)
         println("data saved")
     endif
endfunc

#entry
println("BT device discovery inited")
int x = DPDLAPI_createObexServer(BT_GIAC_MODE)
println("opening record store 'BluetoohDevices'...")
int BT_DEV_RS = createRS("BluetoohDevices", AUTHMODE_ANY, dpdlTrue, dpdlTrue)
enumRecords(BT_DEV_RS, dpdlTrue)
println("discovering BT devices...")
runDiscovery()
showDevicesFound()
int total_btdevices  =  getNrRecords(BT_DEV_RS)
println("Total Bluetooth devices discovered: " + total_btdevices)
println("closing record store")
closeRS(BT_DEV_RS)
println("done")
