# File: recordStoreExample.h
#
# Example: create, populate and iterate a recordstore using the DPDAPI_ function
# Note: a shortcut of the function is available in dpdlRS.h
#
# Author: A. Costa
# e-mail: info@seesolutions.it
#
#
include("dpdllib.h")
include("dpdlBT.h")
include("dpdlRS.h")

# main
string my_record_store_name = "dsls_altabadia_lifts"
int nr_records = 10
int c = 0

println("opening RecordStore: " + my_record_store_name)
int PTR_RS = DPDLLIB_openRS(my_record_store_name, AUTHMODE_ANY, dpdlTrue, dpdlTrue)
DPDLLIB_enumRecords(PTR_RS, dpdlTrue)
DPDLLIB_rebuildEnum(PTR_RS)
println("showing data in recordstore...")
int rec_id = 1
string record_data = ""
while(rec_id != -1)
	rec_id = DPDLLIB_getNextRecordID(PTR_RS)
	println("fetching next record id: " + rec_id)
	record_data = DPDLLIB_getRSData(PTR_RS, rec_id)
	println("rec_id: " + rec_id + " record_data: " + record_data)
endwhile
closeRS(PTR_RS)
println("--------------------------------")
println("done")