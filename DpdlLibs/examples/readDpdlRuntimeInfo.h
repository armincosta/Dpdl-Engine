# File: readRS.h
# Date: 03.09.2009
# Dpdl-example: read by enumeration the records stored in the DpdlRuntimeInfo record store
# Author: ACosta
# e-mail: info@seesolutions.it
#
# example dpdl script implementation that shows how to access data stored in a Dpdl Packet
#
include("dpdlMIDP.h")
func readDevStore()
    int dev_idx = 0
    string cur_rec = dpdlNull
    if(DEV_STORE != -1)
        println("reading RS STORE...")
        enumRecords(DEV_STORE, dpdlTrue)
        int nr_ = getEnumNrRecords(DEV_STORE)
        println("# of records found: " + nr_)
            int cnt_ = 0
            while dev_idx != -1
                dev_idx = getNextRecordID(DEV_STORE)
                if dev_idx != -1
                  cur_rec = getRecord(DEV_STORE, dev_idx)
                  cnt_ = cnt_+1
                  println("record: " + cnt_ + "   ->" + cur_rec)
                endif
            endwhile
    endif
endfunc

#main
println("reading DpdlRuntimeInfo")
string rs_dev_name = "DpdlFragments1977596108"
int DEV_STORE = createRS(rs_dev_name, AUTHMODE_ANY, dpdlTrue, dpdlTrue)
println("RS STORE: " + DEV_STORE)
readDevStore()