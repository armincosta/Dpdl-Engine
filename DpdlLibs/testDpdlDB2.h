# File: testDpdlDB.h
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
         while(c < 50000)
              if(console_input)
                  println("enter a key to search:")
                  search_key = readln()
              else
              	  search_rand_int = randInt(16, 50000) # i
              	  search_rand_int = abs(search_rand_int)
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

