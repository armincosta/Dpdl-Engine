#dpdlRS.h V1.0      info@seesolutions.it
#
#Author: Armin Costa
#
#This library is implemented with Dpdl-Control-Script and comes with the standard Dpdl core Engine,
#It contains basic system abstraction functions and internal system variables.
#
#Filename: dpdlRS.h
#License: GNU GPL
#
#This library provides basic a basic interaction layer for accessing Dpdl File Storage functiontions
#NOTE: When loading this module as part of dpdlMIDP.h, we have to include it in dpdlMIDPRS.h and remove all contained declarations
#      This is useful to reuse the same dpdl script on different targets (Win32 vs. MIDP),
#      Redirecting J2ME RS functiontions to Dpdl Native File Storage mechanism, the interface is the same.
#
#return int rs_id
function createRS(string name, int auth_mode, int write, int create)
    return DPDLLIB_openRS(name, auth_mode, write, create)
end

#return int status
function closeRS(int rs_id)
    return DPDLLIB_closeRS(rs_id)
end

#return int status
function deleteRS(string rs_name)
    return DPDLLIB_deleteRS(rs_name)
end

#return int nr Records, -1 if error
function getNrRecords(int rs_id)
    return DPDLLIB_getNumRecords(rs_id)
end

#return int status
function enumRecords(int rs_id, int keepupdated)
      return DPDLLIB_enumRecords(rs_id, keepupdated)
end

#return int status
function resetEnum(int rs_id)
      return DPDLLIB_resetEnum(rs_id)
end

#return int nr Records
function getEnumNrRecords(int rs_id)
      return DPDLLIB_getEnumNumRecords(rs_id)
end

#return int next record ID
function getNextRecordID(int rs_id)
    return DPDLLIB_getNextRecordID(rs_id)
end

#return int record id added
function addRecord(int rs_id, string data)
    return DPDLLIB_addRSData(rs_id, data)
end

#return string record
function getRecord(int rs_id, int rec_id)
    return DPDLLIB_getRSData(rs_id, rec_id)
end

#return int status
function setRecord(int rs_id, int rec_id, string data)
    return DPDLLIB_setRSRecord(rs_id, rec_id, data)
end

#return int bytes
function getRecordSize(int rs_id, int rec_id)
    return DPDLLIB_getRecordSize(rs_id, rec_id)
end

#return int status
function deleteRecord(int rs_id, int rec_id)
    return DPDLLIB_deleteRSData(rs_id, rec_id)
end

#RS modes
int AUTHMODE_ANY = 1
int AUTHMODE_PRIVATE = 0
