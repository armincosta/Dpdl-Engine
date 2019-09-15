# Dpdl-Scripting

Dpdl (Dynamic Packet Definition Language) Scripting allows the controlling of DpdlEngine features.

Dpdl provides and extensible API to implement small application on J2ME and JavaME platforms. 

Some examples of Dpdl-Scripting can be found under ./DpdlLibs/examples/

Example script:
```
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
