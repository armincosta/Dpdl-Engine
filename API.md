# Dpdl-Engine API documentation


## Core API

The methods listed below are part of the Dpdl core API and can be accessed via dpdl scripting

**[Native]**
```
systemExec(string cmd, int wait_for, int verbose_output) return int status
hash(string s)
println(string s)
print(string s)
mod(int val, int mod) return int res
randInt(int bits, int modulo) return int res
nextInt(int modulo) return int res
abs(int val) return int res
substring(string str, int off_start, int off_end) return string res
replace(string str, string find, string replace) return string res
strlen(string str) return int len
endsWith(string str) return int bool
parseInt(string str) return int value
getDateStamp() return string date
getDateField(int field) return int date
getTime() return string time
setStartTime()
getEndTime() return int time
readln() return string line
sleep(int time_ms) return int status
putMemArrayInt(int array_id, int val) return int status
getMemArrayInt(int array_id, int index) return int entry
putMemArrayStr(int array_id, string val) return int status
getMemArrayStr(int array_id, int index) return string entry
allocMemArray(int id, int minsize) return int status
getMemArraySize(int id) return int size
isInArr(int array_id, object obj)
close(int handle)
open(string file, string mode) return int handle
write(int handle, string str)
writeStream(int handle, string obj, ..)
read(int handle) return string str
eof() return int status
listFiles()
api()
getApi() return string api
exit(int status)
```

**[DPDLAPI]**
```
include(string lib_path)     return int
DPDLAPI_getVersion()  return string
DPDLAPI_getEngineVersion() return string
DPDLAPI_getResultSet(int pos, string variableName)  return string 
DPDLAPI_getNrResults() return int
DPDLAPI_mallocDpdlService(string serviceName) return int
DPDLAPI_selectDpdlService(string serviceName, string chunk, string contraint)  return status
DPDLAPI_swapDpdlChunk(string serviceName, string chunkName)  return int 
DPDLAPI_processXPath(string filepath, string query)  return string result
DPDLAPI_getXPathNrResults()  return int size
DPDLAPI_getXPathResult(int index)  return string result
DPDLAPI_printDpdlScript(string package_name, int mode, string file)  return int  desc-> STDOUT: mode = 0   FILE: mode = 1 
DPDLAPI_callExtension(string extension_function)  return int
DPDLAPI_clearCache(string class_name)    return int
DPDLAPI_processXPathVar(string var_name, string query, string mode, string outputFile)    return int
DPDLAPI_createThread(int instance, string script, int priority, int milliseconds)    return int status
DPDLAPI_execScript(string script) return int status
DPDLAPI_execCode(string file) return int status
```

**[DPDLAPI Bluetooth]**
```
DPDLAPI_createDevice(string type, string name, string param, string cmd) return int status
DPDLAPI_discoverBTDevices()   return devices
DPDLAPI_discoverBTDevicesA()   return int status
DPDLAPI_discoverBTFinished() return int status
DPDLAPI_createBTServer(int DISCOVERY_MODE, int authentication, int authorization, int encryption)  return int status
DPDLAPI_createBTClient(int instance, int DISCOVERY_MODE, int authentication, int authorization, int encryption)   return int device
DPDLAPI_sendClientData(int device, string data) return int status
DPDLAPI_readClientData()  return string data
DPDLAPI_clearClientTX(int device)   void
DPDLAPI_clearClientRX(int device)   void
DPDLAPI_discoveryClientFinished()  return int discoveryFinished
DPDLAPI_serviceDiscoveryClientFinished(int client_instance)  return int status
DPDLAPI_getClientBTAddr(int client_instance)  return string remoteDevice
DPDLAPI_getServerBTAddr()  return string remoteDevice
DPDLAPI_getServerVisibleBTAddr()   return string remoteDevice
DPDLAPI_getServerVisibleBTAddrA()   return string remoteDevice
DPDLAPI_searchClientsOnServer() return int status
DPDLAPI_discoveryServerFinished() return int status
DPDLAPI_serviceDiscoveryServerFinished() return int status
DPDLAPI_connectServerToClients() return int status
DPDLAPI_sendServerData(string data) return int status
DPDLAPI_readServerData() return string data
DPDLAPI_disconnectServerToClients() return int status
DPDLAPI_createObexServer(int DISCOVERY_MODE) return int status
DPDLAPI_sendObex(string device, int useAuth, string data) return int status
DPDLAPI_sendObexFile(string device, int useAuth, string file_name) return int status
DPDLAPI_sendObexA(string dev, string data) return int status
DPDLAPI_sendObexFileA(string dev, string data_file) return int status
DPDLAPI_sendObexImage(string img_name) return int status
DPDLAPI_pairBTDeviceA(string dev) return int status
DPDLAPI_pairBTDeviceAWait(string dev) return int status
DPDLAPI_pairBTDeviceAPassive(int init) return int status
```

**[DPDLRS]**
```
DPDLLIB_openRS(string name, int auth_mode, int writable, int create)  return int rs_id
DPDLLIB_closeRS(int rs_id)   return int status
DPDLLIB_deleteRS(string rs_name)   return int status
DPDLLIB_openRSId(int idx, string name, int auth_mode, int writable, int create)  return int rs_id
DPDLLIB_getNumRecords(int rs_id)   return int nr_records
DPDLLIB_enumRecords(int rs_id, int keepUpdated) return int status
DPDLLIB_resetEnum(int rs_id) return int status
DPDLLIB_rebuildEnum(int rs_id) return int status
DPDLLIB_getEnumNumRecords(int rs_id) return status
DPDLLIB_getNextRecordID(int rs_id)   return int next_rec_id
DPDLLIB_getRecordSize(int rs_id)  return int size_bytes
DPDLLIB_addRSData(int rs_id, string data)  return int status
DPDLLIB_setRSData(int rs_id, int rec_id, string data)   return int status
DPDLLIB_getRSData(int rs_id, int rec_id)   return string data
DPDLLIB_deleteRSData(int rs_id, int rec_id) return int status
```

**[DPDLNET]**
```
DPDLLIB_createServer(int server_id, int port) return int status
DPDLLIB_createClient(int client_id, string host, int port) return int status
DPDLLIB_sendClientData(string data) return int status
DPDLLIB_readClientData() return string data
```

**[MIDP]**
```
MIDPLIB_Alert(string title, string msg, int type)   return int commandPressed
MIDPLIB_Form(int instance, string title)   return int component_index
MIDPLIB_FormAppend(int component, string msg)   return int status
MIDPLIB_FormClear(int component)  return int status
MIDPLIB_Canvas(int instance) return int component
MIDPLIB_graphicsSetCurrent(int component)
MIDPLIB_graphicsSetColor(int component, int r, int g, int b)
MIDPLIB_graphicsRepaint(int component)
MIDPLIB_graphicsClear(int component)
MIDPLIB_graphicsDrawString(int component, int x, int y, int anchor)
MIDPLIB_graphicsDrawLine(int component, int x1, int y1, int x2, int y2)
MIDPLIB_graphicsDrawRect(int component, int x, int y, int w, int h)
MIDPLIB_graphicsFillRect(int component, int x, int y, int w, int h)
MIDPLIB_openRS(string name, int auth_mode, int writable, int create)  return int rs_id
MIDPLIB_closeRS(int rs_id)   return int status
MIDPLIB_getNumRecords(int rs_id)   return int nr_records
MIDPLIB_enumRecords(int rs_id, int keepUpdated) return int status
MIDPLIB_resetEnum(int rs_id) return int status
MIDPLIB_getEnumNumRecords(int rs_id) return status
MIDPLIB_getNextRecordID(int rs_id)   return int next_rec_id
MIDPLIB_getRecordSize(int rs_id)  return int size_bytes
MIDPLIB_addRSData(int rs_id, string data)  return int status
MIDPLIB_setRSData(int rs_id, int rec_id, string data)   return int status
MIDPLIB_getRSData(int rs_id, int rec_id)   return string data
MIDPLIB_deleteRSData(int rs_id, int rec_id) return int status
MIDPLIB_getCalendarField(int field_name)   return int value
```
