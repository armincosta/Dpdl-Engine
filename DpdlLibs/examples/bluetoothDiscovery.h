# File: bluetoothDiscovery.h
# Date: 03.09.2009
# Dldl-Example: Discovery of bluetooth devices
# Author: ACosta
# e-mail: info@seesolutions.it
#
#
include("dpdllib.h")
include("dpdlBT.h")
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
			  dev_found = dev_found + 1
          endif
     endwhile
endfunc

#entry
println("BT device discovery inited")
int x = DPDLAPI_createObexServer(BT_GIAC_MODE)
println("discovering BT devices...")
runDiscovery()
showDevicesFound()
println("done")
