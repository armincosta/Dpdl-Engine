include("dpdllib.h")


#main
string host = "192.168.2.128"
int port = 6666

println("starting client...")
int status_client = DPDLLIB_createClient(0, host, port)
println("server started with status: " + status_client)

int counter = 0
string data = "null"
int s = dpdlFalse
while(dpdlTrue)
	println("sending data...")
	s = DPDLLIB_sendClientData(0, "data" + counter)
	println("status: "+ s)
	sleep(1000)
	println("reading data...")
	data = DPDLLIB_readClientData(0)
	println("data: " + data)
	counter = counter + 1
endwhile