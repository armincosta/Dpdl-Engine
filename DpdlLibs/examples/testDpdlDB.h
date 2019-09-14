# File: testDpdlDB.h
#
# Example: Example Script that shows how to access and query data stored in a Dpdl Packet
#		   that has been encoded with dpdl_$PACKET_NAME.c definition source
#
#		   The script implements a small console application to allocate and make bulk queries on a provided Dpdl Packet 
#
# 		   This implementation assumes that the provided dpdl_$PACKET_NAME has already been installed on the device.
#		   If the selected chunks are not yet allocated, allocation will be done at the first run.
#
# Author: A.Costa
# e-mail: armincosta(_a_t_)seesolutions.it
#
# License: GNU GPL
#
#
include("dpdlMIDP.h")

function init()
   println("init() testDpdlDB.h")
end

function showResults()
     string name_
     string phoneNR
     string email
     int nr_res = DPDLAPI_getNrResults()
     int c = 0
     println("Results: " + nr_res + " ---->")
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
              c=c+1
         endwhile
         println("#######################")
     else
         println("no results found")
     endif
end

string dpdl_packet_name = dpdlNull
string dpdl_chunk_name = dpdlNull

# script entry point
println("starting...")
init()
println("enter the packet name:")
dpdl_packet_name = readln()
println("enter the chunk name:")
dpdl_chunk_name = readln()

println("allocating Dpdl Service...")
int status = dpdlError
println("swapping chunks..")
status = DPDLAPI_swapDpdlChunk(dpdl_packet_name, dpdl_chunk_name)
println("status: " + status)
println("finished swapping..")

string constraint_ = dpdlNull
if(status == dpdlTrue)
         int c = 0
         int i = 1
         string search_key = ""
         println("running queries...")
         println("press 'q' to query from the console, else ENTER to run 5000 queries automatically")
         int console_input = dpdlFalse
         string read_console = readln()
         if(read_console == "q")
              console_input = dpdlTrue
         else
         	  println("enter a constraint base name: $basename $counter")
              constraint_ = readln()
              constraint_ = constraint_ + " "
         endif
         setStartTime()
         while(c < 43000)
              if(console_input)
                  println("enter a key to search:")
                  search_key = readln()
              else
                  println("-->   searching: "+(constraint_+i))
                  search_key = (constraint_+i)
              endif
              status = DPDLAPI_selectDpdlService(dpdl_packet_name, dpdl_chunk_name, search_key)
              if(status == dpdlTrue)
              	showResults()
              else
              	println("Error in select")
              endif
              c = c+1
              i = i+1
         endwhile
         int time_exec = getEndTime()
         println("time exec in : " + time_exec + " ms")
endif

