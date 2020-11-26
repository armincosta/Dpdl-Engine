/*######################################################

  this is an example script written in Dpdl
  (Dynamic Packet Definition Language ) showing
  how data services can be implemented on the Dpdl platform

  Author:   Armin Costa
  contact: info@seesolutions.it
  -----------------------------------------------------
  # Example:    Phone-Book Cities Bolzano Trento
  # Filename:   dpdl_PHONEBOOK.c
  # DpdlPacket: dpdl_PHONEBOOK
  #
  # License: GNU GPL
  #
  #######################################################
**/
call(dpdlInterpreter)
::module dpdl_PHONEBOOK
::module_SPEC 23452
::model 836
::dpdlVersion 1.0

import extern SystemData;

OPTIONS {
    TARGET = CDC 1.0
    VM = 1.0
    ZIP = true
    CHECKSUM = true
    SIGNATURE = true
    ENCRYPTION(RSA) = true
}

#define DpdlEncoding UTF-8

#define bolzano_db Bolzano.csv
#define trento_db Trento.csv

#defineSQL query SELECT name, phoneNR, e-mail FROM $Chunk

#defineProtocol-cHtml phonebook_visual phone_book.html

catch DPDL_Script OnInit() {
    include("dpdllib.h")
    println("OnInit()")
}


import virtual DATA SystemData {
        class Bolzano volatile phonebook_visual {
              DATA::string const name;
              DATA::string using phoneNR;
              DATA::string using  e-mail;
              #defineGUI Default <Bolzano_PhoneBook>  <please_enter_name_and_surname_here:>
              catch DPDL_Script OnDecode() {
                 include("dpdllib.h")
                 println("OnDecode() Bolzano")
              }
        }
        class Trento volatile phonebook_visual {
              DATA::string const name;
              DATA::string using phoneNR;
              DATA::string using  e-mail;
              #defineGUI Default <Trento_PhoneBook>  <please_enter_name_and_surname_here:>
              catch DPDL_Script OnDecode() {
                 include("dpdllib.h")
                 println("OnDecode() Trento")
              }
        }
}

#defineD Bolzano src bolzano_db SQL query {
                CHUNK entrybz [6];
                struct BTree DENSE_INDEX hashing *name
                entrybz.content { name , phoneNR , e-mail }
                entrybz.name TAG(0xef) const (string) = 20;
                entrybz.phoneNR TAG(0xefe) (string) = 15;
                entrybz.e-mail TAG(0xefee) (string) = 30;
}

#defineD Trento src trento_db SQL query {
                CHUNK entrytn [6];
                struct BTree DENSE_INDEX hashing *name
                entrytn.content { name , phoneNR , e-mail }
                entrytn.name TAG(0xef) const (string) = 20;
                entrytn.phoneNR TAG(0xefe) (string) = 15;
                entrytn.e-mail TAG(0xefee) (string) = 30;
}
