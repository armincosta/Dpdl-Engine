#dpdlRS.h V1.0      info@seesolutions.it
#
#Author: Armin Costa
#
#This library is implemented with Dpdl-Control-Script and comes with the standard Dpdl core Engine,
#It contains basic system abstraction functions and internal system variables.
#
#Filename: dpdlRS.h
#This library provides basic a basic interaction layer for accessing Dpdl File Storage functions
#NOTE: When loading this module as part of dpdlMIDP.h, we have to include it in dpdlMIDPRS.h and remove all contained declarations
#      This is useful to reuse the same dpdl script on different targets (Win32 vs. MIDP),
#      Redirecting J2ME RS functions to Dpdl Native File Storage mechanism, the interface is the same.
#
#return int rs_id
func createRS(string name, int auth_mode, int write, int create)
    return DPDLLIB_openRS(name, auth_mode, write, create)
endfunc

#return int status
func closeRS(int rs_id)
    return DPDLLIB_closeRS(rs_id)
endfunc

#return int status
func deleteRS(string rs_name)
    return DPDLLIB_deleteRS(rs_name)
endfunc

#return int nr Records, -1 if error
func getNrRecords(int rs_id)
    return DPDLLIB_getNumRecords(rs_id)
endfunc

#return int status
func enumRecords(int rs_id, int keepupdated)
      return DPDLLIB_enumRecords(rs_id, keepupdated)
endfunc

#return int status
func resetEnum(int rs_id)
      return DPDLLIB_resetEnum(rs_id)
endfunc

#return int nr Records
func getEnumNrRecords(int rs_id)
      return DPDLLIB_getEnumNumRecords(rs_id)
endfunc

#return int next record ID
func getNextRecordID(int rs_id)
    return DPDLLIB_getNextRecordID(rs_id)
endfunc

#return int record id added
func addRecord(int rs_id, string data)
    return DPDLLIB_addRSData(rs_id, data)
endfunc

#return string record
func getRecord(int rs_id, int rec_id)
    return DPDLLIB_getRSData(rs_id, rec_id)
endfunc

#return int status
func setRecord(int rs_id, int rec_id, string data)
    return DPDLLIB_setRSRecord(rs_id, rec_id, data)
endfunc

#return int bytes
func getRecordSize(int rs_id, int rec_id)
    return DPDLLIB_getRecordSize(rs_id, rec_id)
endfunc

#return int status
func deleteRecord(int rs_id, int rec_id)
    return DPDLLIB_deleteRSData(rs_id, rec_id)
endfunc

#RS modes
int AUTHMODE_ANY = 1
int AUTHMODE_PRIVATE = 0
