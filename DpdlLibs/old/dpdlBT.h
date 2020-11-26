#DpdlLib V1.0      info@seesolutions.it
#
#Author: Armin Costa
#
#This library is implemented with Dpdl-Control-Script and comes with the standard Dpdl core Engine,
#It contains basic system abstraction functions and internal system variables.
#
#Filename: dpdlBT.h
func discoverDevices()
    return DPDLAPI_discoverBTDevices()
endfunc

func discoverFinished()
    return DPDLAPI_discoverBTFinished()
endfunc

func discoverDevice()
     string dev_ = "dev"
     return dev_
endfunc

func connectDevice(string name)
     println("connect..")
     return 1
endfunc

func createServer(int DISCOVERY_MODE, int authentication, int authorization, int encryption)
        return DPDLAPI_createBTServer(DISCOVERY_MODE, authentication, authorization, encryption)
endfunc

func createClient(int instance, int DISCOVERY_MODE, int authentication, int authorization, int encryption)
      return DPDLAPI_createBTClient(instance, DISCOVERY_MODE, authentication, authorization, encryption)
endfunc

func setDeviceConnectionURL(string url)
      DPDLAPI_setBTDeviceConnectionURL(url)
endfunc

func setDeviceUUID(string uuid)
      DPDLAPI_setBTDeviceUUID(uuid)
endfunc

func discoveryFinished(int client_instance)
     #by providing BT_SERVER_MODE as param, we can switch to server-side operation
     if client_instance == BT_SERVER_MODE
         return DPDLAPI_discoveryServerFinished()
     else
         return  DPDLAPI_discoveryClientFinished(client_instance)
     endif
endfunc

func serviceDiscoveryFinished(int client_instance)
     #by providing BT_SERVER_MODE as param, we can switch to server-side operation
     if client_instance == BT_SERVER_MODE
           return DPDLAPI_serviceDiscoveryServerFinished()
     else
           return DPDLAPI_serviceDiscoveryClientFinished(client_instance)
     endif
endfunc

func getDeviceAddr(int client_instance)
     if client_instance == BT_SERVER_MODE
        return DPDLAPI_getServerBTAddr()
     else
        return DPDLAPI_getClientBTAddr(client_instance)
     endif
endfunc

#the funcion allows customization of read- and write-out operations, speed vs. accurancy
func setRxTimeout(int timeout_read, int time_slice)
     TIMEOUT_READ = timeout_read
     TIMESLICE = time_slice
endfunc

func sendClientData(int device, string data)
      return DPDLAPI_sendClientData(device, data)
endfunc

func readClientData(int device)
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
endfunc

func clearClientTXBuffer(int device)
     DPDLAPI_clearClientTX(device)
endfunc

func clearClientRXBuffer(int device)
       DPDLAPI_clearClientRX(device)
endfunc

func searchServerDevices()
      return DPDLAPI_searchClientsOnServer()
endfunc

func connectServerDevices()
      return DPDLAPI_connectServerToClients()
endfunc

func sendServerData(string data)
      return DPDLAPI_sendServerData(data)
endfunc

func readServerData()
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
endfunc

func clearServerTXBuffer()
    return DPDLAPI_clearServerTX()
endfunc

func disconnectServerDevices()
     return DPDLAPI_disconnectServerToClients()
endfunc


func createImageServer()
    return DPDLAPI_createBTImageServer()
endfunc

func createImageClient()
    return  DPDLAPI_createBTImageClient()
endfunc

func initProt()
    println("init() Bluetooth")
endfunc

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