# File: HTTPServer.h
#
# Example: server to accept and forward data from HTTPClient.h over HTTP protocol
#
# Author: A. Costa
# e-mail: info@seesolutions.it
#
#
include("dpdllib.h")


#main
string host = "192.168.2.85"
int port = 6666
int PTR_SERVER = 0

println("starting server on port: " + port)
int status = DPDLLIB_createServer(PTR_SERVER, port)
println("server started with status: " + status)
while(dpdlTrue)
	print(".")
	sleep(2000)
endwhile

