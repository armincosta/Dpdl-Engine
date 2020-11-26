#DpdlLib V1.0      info@seesolutions.it
#
#Author: Armin Costa
#
#This library is implemented with Dpdl-Control-Script and comes with the standard Dpdl core Engine,
#It contains basic system abstraction functions and internal system variables.
#
#Filename: dpdlBT.h
#License: GNU GPL
#
function discoverDevices()
    return DPDLAPI_discoverBTDevices()
end

function discoverFinished()
    return DPDLAPI_discoverBTFinished()
end

function discoverDevice()
     string dev_ = "dev"
     return dev_
end

function connectDevice(string name)
     println("connect..")
     return 1
end

function createServer(int DISCOVERY_MODE, int authentication, int authorization, int encryption)
        return DPDLAPI_createBTServer(DISCOVERY_MODE, authentication, authorization, encryption)
end

function createClient(int instance, int DISCOVERY_MODE, int authentication, int authorization, int encryption)
      return DPDLAPI_createBTClient(instance, DISCOVERY_MODE, authentication, authorization, encryption)
end

function setDeviceConnectionURL(string url)
      DPDLAPI_setBTDeviceConnectionURL(url)
end

function setDeviceUUID(string uuid)
      DPDLAPI_setBTDeviceUUID(uuid)
end

function discoveryFinished(int client_instance)
     #by providing BT_SERVER_MODE as param, we can switch to server-side operation
     if client_instance == BT_SERVER_MODE
         return DPDLAPI_discoveryServerFinished()
     else
         return  DPDLAPI_discoveryClientFinished(client_instance)
     endif
end

function serviceDiscoveryFinished(int client_instance)
     #by providing BT_SERVER_MODE as param, we can switch to server-side operation
     if client_instance == BT_SERVER_MODE
           return DPDLAPI_serviceDiscoveryServerFinished()
     else
           return DPDLAPI_serviceDiscoveryClientFinished(client_instance)
     endif
end

function getDeviceAddr(int client_instance)
     if client_instance == BT_SERVER_MODE
        return DPDLAPI_getServerBTAddr()
     else
        return DPDLAPI_getClientBTAddr(client_instance)
     endif
end

#the functionion allows customization of read- and write-out operations, speed vs. accurancy
function setRxTimeout(int timeout_read, int time_slice)
     TIMEOUT_READ = timeout_read
     TIMESLICE = time_slice
end

function sendClientData(int device, string data)
      return DPDLAPI_sendClientData(device, data)
end

function readClientData(int device)
      string data = "null"
      int cnt = 1
      while data == "null"
         data = DPDLAPI_readClientData(device)
         sleep(TIMESLICE)
         cnt = cnt + 1
         if (cnt == TIMEOUT_READ)
             data = BT_TIMEOUT
         endif
      endwhile
      return data
end

function clearClientTXBuffer(int device)
     DPDLAPI_clearClientTX(device)
end

function clearClientRXBuffer(int device)
       DPDLAPI_clearClientRX(device)
end

function searchServerDevices()
      return DPDLAPI_searchClientsOnServer()
end

function connectServerDevices()
      return DPDLAPI_connectServerToClients()
end

function sendServerData(string data)
      return DPDLAPI_sendServerData(data)
end

function readServerData()
      string data = "null"
      int cnt = 1
      while data == "null"
         data = DPDLAPI_readServerData()
         sleep(TIMESLICE)
         cnt = cnt + 1
         if (cnt == TIMEOUT_READ)
             data = BT_TIMEOUT
         endif
      endwhile
      return data
end

function clearServerTXBuffer()
    return DPDLAPI_clearServerTX()
end

function disconnectServerDevices()
     return DPDLAPI_disconnectServerToClients()
end


function createImageServer()
    return DPDLAPI_createBTImageServer()
end

function createImageClient()
    return  DPDLAPI_createBTImageClient()
end

function initProt()
    println("init() Bluetooth")
end

#BT API defines
int BT_LIAC_MODE = 10390272
int BT_GIAC_MODE = 10390323

#vars
int BT_SERVER_MODE = 9999

#config
#we set the time out of read() requests to 1000 milliseconds
string BT_TIMEOUT = "BT_TIMEOUT"
int TIMEOUT_READ = 50
#TIMESLICE in ms
int TIMESLICE = 20

# start
initProt()