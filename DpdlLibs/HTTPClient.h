# File: HTTPClient.h
#
# Example: client to broadcast data to clients over HTTP protocol via HTTPServer 
#
# Author: A. Costa
# e-mail: info@seesolutions.it
#
#
include("dpdllib.h")


#main
string host = "192.168.2.128"
int port = 6666
int PTR_CLIENT = 0

println("starting client...")
int status_client = DPDLLIB_createClient(PTR_CLIENT, host, port)
println("server started with status: " + status_client)

int counter = 0
string data = "null"
int s = dpdlFalse
while(dpdlTrue)
	println("sending data...")
	s = DPDLLIB_sendClientData(PTR_CLIENT, "data" + counter)
	println("status: "+ s)
	sleep(1000)
	println("reading data...")
	data = DPDLLIB_readClientData(PTR_CLIENT)
	println("data: " + data)
	counter = counter + 1
endwhile