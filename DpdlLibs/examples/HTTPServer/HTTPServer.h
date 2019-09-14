include("dpdllib.h")


#main
string host = "192.168.2.85"
int port = 6666

println("starting server on port: " + port)
int status = DPDLLIB_createServer(0, port)
println("server started with status: " + status)
while(dpdlTrue)
	print(".")
	sleep(2000)
endwhile

