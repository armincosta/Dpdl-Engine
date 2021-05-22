# Dpdl (Dynamic Packet Definition Language)

DPDL is a small framework and scripting engine that can be used to implement small, portable and light-weight applications on Java enabled devices and small embedded systems (in particular J2ME and Java ME). It has been developed in 2002, in early days when mobile phones where running mostly J2ME applications. Dpdl is a compact framework, small memory footprint API library and scripting engine that can be used to encode, decode, control and query data efficiently on limited memory devices. It supports Bluetooth and HTTP protocols by default.

![Dpdl](http://www.seesolutions.it/images/app/thumb/Dpdl_Dynamic_Packet_Definition_Language_components_thumb.jpg)

Dpdl can be used as integrated application module, as a library module, as a testing environment or as rapid application prototyping platform for small devices and small embedded systems.

Dpdl allows to implement small applications and scripts that make use of the built-in data container in form of a Dpdl packet, a highly compressed chunked data packet with built in database technology and scripting engine.

![Dpdl-Packet](http://www.seesolutions.it/images/app/thumb/Dpdl_Framework_FlowChart_thumb.jpg)

## Examples

### Example Dpdl script for discovering bluetooth devices and saving the devices found in a record store:

```c++
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

### Dpdl script to create an executable Dpdl Packet (dpdl_PHONEBOOK)

```c++
/*######################################################
                Dpdl(tm)
     Dynamic Packet Definition Language
             www.seesolutions.it

  this is a prototype-script written in Dpdl
  (Dynamic Packet Definition Language ) showing
  how services could be implemented on the Dpdl platform

  Author:   Armin Costa
  contact: info@seesolutions.it
  -----------------------------------------------------
  EXAMPLE:        Phone-Book Cities BZ TN
  File: dpdl_PHONEBOOK_BZ_TN.c
  Date: 23.01.2002
  #######################################################
**/
call(dpdlInterpreter)
::module dpdl_PHONEBOOK
::module_SPEC 23452
::model 836
::dpdlVersion 1.0

import extern SystemData;

OPTIONS {
    TARGET = CDC
    KVM = 1.0
    ZIP = true
    CHECKSUM = true
    SIGNATURE = true
    ENCRYPTION(RSA) = true
}

#define DpdlEncoding UTF-8

#define bolzano_db user@192.168.2.44:5432
#define trento_db user@192.168.2.44:5432

#defineSQL query SELECT name, phoneNR, e-mail FROM $Chunk end

#defineProtocol-cHtml phonebook_visual phone_book.html

catch DPDL_Script OnInit() {
    include("dpdllib.h")  nl
    println("OnInit()")  nl
}


import virtual DATA none  {
        class Bolzano volatile phonebook_visual {
              DATA::string const name;
              DATA::string using phoneNR;
              DATA::string using  e-mail;
              #defineGUI Default <Bolzano_PhoneBook>  <please_enter_name_and_surname_here:>
              catch DPDL_Script OnDecode() {
                 include("dpdllib.h")    nl
                 println("OnDecode() Bolzano")  nl
              }
        }
        class Trento volatile phonebook_visual {
              DATA::string const name;
              DATA::string using phoneNR;
              DATA::string using  e-mail;
              #defineGUI Default <Trento_PhoneBook>  <please_enter_name_and_surname_here:>
              catch DPDL_Script OnDecode() {
                 include("dpdllib.h")    nl
                 println("OnDecode() Trento")  nl
              }
        }
}

#defineD Bolzano src bolzano_db SQL query {
                CHUNK entrybz [6];
                struct BTree DENSE_INDEX hashing *name
                entrybz.content { name , phoneNR , e-mail }
                entrybz.name TAG(0xef) const (string) = 20;
                entrybz.phoneNR TAG(0xefe) (string) = 15;
                entrybz.e-mail TAG(0xefee) (string) = 30;
}

#defineD Trento src trento_db SQL query {
                CHUNK entrytn [6];
                struct BTree DENSE_INDEX hashing *name
                entrytn.content { name , phoneNR , e-mail }
                entrytn.name TAG(0xef) const (string) = 20;
                entrytn.phoneNR TAG(0xefe) (string) = 15;
                entrytn.e-mail TAG(0xefee) (string) = 30;
}

```

### Dpdl script to allocate and query a Dpdl-Packet with some benchmarking (dpdl_PHONEBOOK)

```c++
# File: testDpdlDB2.h
#
# Example: Script implementation that shows how to access and query data stored in a Dpdl Packet (dpdl_PHONEBOOK.dpdl)
#		   that has been encoded with dpdl_PHONEBOOK.c source
#
# 		   This implementation assumes that the provided Dpdl service dpdl_PHONEBOOK has already been installed
#		   If the selected chunks are not yet allocated, allocation will be done at the first run
#
# Author: A. Costa
# e-mail: info@seesolutions.it
#
#
include("dpdlMIDP.h")

func init()
   println("init() testDpdlDB.h")
endfunc

func addToCSV(string name, string phoneNR, string email)
	string entry = "" + name + ";" + phoneNR + ";" + email + ""
	if(hfile != dpdlError)
		write(hfile, entry)
		println("entry added..")
	else
		println("Error in opening file for writing")
	endif
endfunc

func showResults()
     string name_
     string phoneNR
     string email
     int nr_res = DPDLAPI_getNrResults()
     int c = 0
     println("Results: " + nr_res + " ---->");
     if(nr_res > 0)
         # we just show one result-set in this example
         while(c < nr_res)
              name_ = DPDLAPI_getResultSet(c, "name")
              phoneNR = DPDLAPI_getResultSet(c, "phoneNR")
              email = DPDLAPI_getResultSet(c, "e-mail")
              println("                       name: " + name_)
              println("                       phone nr.: " + phoneNR)
              println("                       e-mail: " + email)
              println("-----------------------------------------")
              if(name_ != dpdlNull)
              	# addToCSV(name_, phoneNR, email)
              endif
              c=c+1
         endwhile
         println("#######################")
     else
         println("no results found")
     endif
endfunc

# script entry point
string DPDL_PACKET_NAME = "dpdl_PHONEBOOK"
string DPDL_CHUNK_NAME = "BolzanoPhone"
# for stats
int total_ms = 0
int end_ms = 0
println("starting...")
init()

println("allocating Dpdl Service...")
int status = dpdlError
println("swapping chunks..")
status = DPDLAPI_swapDpdlChunk(DPDL_PACKET_NAME, DPDL_CHUNK_NAME)
println("status: " + status)
println("finished swapping..")

string constraint_ = dpdlNull

int hfile = open("./BolzanoPhone.csv", "w")
status = dpdlTrue
if(status == dpdlTrue)
         int c = 0
         int i = 1
         string search_key = ""
         int search_rand_int = 0
         println("running queries...")
         println("press 'q' to query from the console, else ENTER to run 50000 queries automatically")
         int console_input = dpdlFalse
         string read_console = readln()
         if(read_console == "q")
              console_input = dpdlTrue
         else
         	  println("enter a constraint base name: $basename $counter")
              constraint_ = readln()
              constraint_ = constraint_ + " "
         endif
         int count = 0
         while(c < 50000)
              if(console_input)
                  println("enter a key to search:")
                  search_key = readln()
              else
              	  search_rand_int = randInt(16, 50000)
              	  search_rand_int = abs(search_rand_int) # i
                  println("-->   searching: "+(constraint_+search_rand_int))
                  search_key = (constraint_+search_rand_int)
              endif
              setStartTime()
              status = DPDLAPI_selectDpdlService(DPDL_PACKET_NAME, DPDL_CHUNK_NAME, search_key)
              end_ms = getEndTime()
              total_ms = total_ms + end_ms
              if(status == dpdlTrue)
              	showResults()
              else
              	println("Error in select")
              endif
              c = c+1
              i = i+1
         endwhile
         int time_exec = total_ms / 50000
         println("average execution time in : " + time_exec + " ms")
endif
close(hfile)
```

### Various other examples for Dpdl scripting

```c++
# File: dpdlLibExamples.h
# Date: 03.09.2009
# Dldl-Example: Examples using Dpdl scripting
# Author: ACosta
# e-mail: info@seesolutions.it
#
#
include("dpdllib.h")
include("dpdlBT.h")

func readFile(string fname)
	string str = ""
	int fh = open(fname, "r")
	while(str != dpdlNull)
		str = read(fh)
		if(str != dpdlNull)
			println("str: " + str)
		endif
	endwhile
	close(fh)
endfunc

func writeFile(string fname)
	int fh = open(fname, "w")
	write(fh, "This is a Test")
	close(fh)
endfunc

func arrayAlloc()
	allocMemArray(0, 10)
	allocMemArray(1, 10)
	int c = 0
	while(c < 15)
		putMemArrayInt(0, c)
		putMemArrayStr(1, "test " + c)
		c = c + 1
	endwhile
	c = 0
	int val = -1
	string val_str = dpdlNull
	while(c < getMemArraySize(0))
		val = getMemArrayInt(0, c)
		val_str = getMemArrayStr(1, c)
		println("value: " + val + " str: " + val_str)
		c = c + 1
	endwhile
endfunc


# Examples using Dpdl scripting

# Main
println("TEST 1 #######################################")
# reading file
println("reading from a file ...")
readFile("./Test/TestRead.txt")
sleep(2000)
println("")

println("TEST 2 #######################################")
# writing file
println("writing to a file ...")
writeFile("./Test/TestWrite.txt")
sleep(2000)
println("")

println("TEST 3 #######################################")
# array allocation
println("allocating and adding elements to dynamic array ...")
arrayAlloc()
sleep(2000)
println("")

println("TEST 4 #######################################")
# Time
println("get time ...")
println(getTime())
setStartTime()
sleep(1000)
int ms = getEndTime()
println("time elapsed in ms: " + ms)
sleep(2000)
println("")

println("TEST 5 #######################################")
# String operations
string str = "Hello World from Dpdl"
println("performing string operations on string: " + str)
int len = strlen(str)
println("len: " + len)
string substr = substring(str, 0, 5)
println("substring: " + substr)
println("hash: " + hash(str))
if(endsWith(str, "Dpdl") == dpdlTrue)
	println("string ends with Dpdl")
endif
println("replacing 'World' with 'Space' in string...");
string str_replaced =  replace(str, "World", "Space")
println("New string is: " + str_replaced)
sleep(2000)
println("")

println("TEST 6 #######################################")
# Random Number generation
println("generating random numbers ...")
int c = 0
int rand = -1
while(c < 10)
	rand = randInt(32, 100)
	println("random nr: " + abs(rand))
	c = c + 1
endwhile
sleep(2000)
println("")

println("TEST 7 #######################################")
# Inline script execution
println("Executing inline dpdl script...")
int status_execscript = DPDLAPI_execScript("println(\"Hello\")")  
sleep(2000)
println("")

println("TEST 8 #######################################")
# System exec operations
println("executing system function 'echo test' ...")
int status = systemExec("echo test", dpdlTrue, dpdlTrue)
println("status: " + status)
sleep(2000)
println("")

println("TEST 9 #######################################")
# XML xpath query
println("query xml document via xpath...")
string result = DPDLAPI_processXPath("./Test/xpath_test.xml", "/Users/User/Name")
int nr_results = DPDLAPI_getXPathNrResults()
println("nr results: " + nr_results)
println("getting last entry ...")
string entry = DPDLAPI_getXPathResult(nr_results - 1)
println("entry: " + entry)
sleep(2000)
println("")

println("TEST 10 #######################################")
# Bluetooth device discovery
println("BT device discovery inited")
int x = DPDLAPI_createObexServer(BT_GIAC_MODE)
println("discovering BT devices...")
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
	         sleep(1000)
	     endwhile
     else
     	println("No working Bluetooth stack found")
     endif
	 string dev = "n"
	 int dev_found = 0
     while(dev != "null")
          dev = DPDLAPI_getServerVisibleBTAddr()
          if(dev != "null")
              println("dev visible: " + dev)
			  dev_found = dev_found + 1
          endif
     endwhile
sleep(2000)
println("")

```

For more info visit the SEE Solutions website: [www.dpdl.biz](http://www.dpdl.biz)


