# Dpdl-Engine

Dpdl (Dynamic Packet Definition Language) Engine is a compact Java(tm) micro component that may facilitate the development and prototyping of small java applications on embedded systems and mobile devices (J2ME, JavaME, pure Java).

Dpdl provides and extensible API, a custom database implementation and an integrated scripting language to handle control- and data-flows in low memory devices.

The Dpdl-Engine is highly portable and provides also a small virtual machine (< 180 KB) to run the component on  basically almost every platform. The engine has been implemented back in year 2003 where low memory mobile devices and applications were spreading. It has been successfully used to develop applications on J2ME MIDP 2.0 CLDC devices to communicate via Bluetooth(tm) with Linux and Windows workstations.

**Features**:
- API interfaces
- Dpdl scripting
- Database implementation (in form of Dpdl packets)
- Bluetooth (JSR-82 implementation)

**Platform compatibility**:
- Java >= 1.0 <= 1.8
- J2ME
- JavaME
- DpdlVM

**Extensions**:
- CoAP (Constrained Application Protocol)

For more info about Dpdl visit the SEE Solutions website:

[SEE Solutions DPDL](http://www.seesolutions.it/lang_en/index_technology.html) 

**Example bluetooth discovery and save devices found**:
```
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

```

Other Examples of Dpdl-Scripting can be found under ./DpdlLibs/examples/
