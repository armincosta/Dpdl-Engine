# Dpdl-Engine

Dpdl (Dynamic Packet Definition Language) Engine is a compact Java(tm) micro component that may facilitate the development and prototyping of small java applications on embedded systems and mobile devices (J2ME, JavaME, pure Java).

Dpdl provides and extensible API, a custom database implementation and an integrated scripting language to handle control- and data-flows in low memory devices.

The Dpdl-Engine is highly portable and provides also a small virtual machine (< 180 KB) to run the component on  basically almost every platform.

**Features**:
- API interfaces
- Scripting engine
- Database implementation (in form of Dpdl packets)
- Bluetooth (JSR-82 implementation)

**Platform compatibility**:
- Java >= 1.0 <= 1.8
- J2ME
- JavaME
- DpdlVM

**Extensions**:
- CoAP (Constrained Application Protocol)

 

**Example bluetooth discovery**:
```
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
```

Other Examples of Dpdl-Scripting can be found under ./DpdlLibs/examples/
