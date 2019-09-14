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
              	addToCSV(name_, phoneNR, email)
              endif
              c=c+1
         endwhile
         println("#######################")
     else
         println("no results found")
     endif
endfunc

# script entry point
println("starting...")
init()

println("allocating Dpdl Service...")
int status = dpdlError
println("swapping chunks..")
status = DPDLAPI_swapDpdlChunk("dpdl_PHONEBOOK", "BolzanoPhone")
println("status: " + status)
println("finished swapping..")

string constraint_ = dpdlNull

int hfile = open("./BolzanoPhone.csv", "w")
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
         while(c < 48001)
              if(console_input)
                  println("enter a key to search:")
                  search_key = readln()
              else
                  println("-->   searching: "+(constraint_+i))
                  search_key = (constraint_+i)
              endif
              status = DPDLAPI_selectDpdlService("dpdl_PHONEBOOK", "BolzanoPhone", search_key)
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
close(hfile)

