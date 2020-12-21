package dpdl.dpdlRun;

/**
 Dpdl(tm) -- Dynamic Packet Definition Language
 copyright(c) 2007-2012 Armin Costa

 www.seesolutions.it


 Author:  Armin Costa
 e-mail:  armincosta@hotmail.com

 */

import java.io.*;
import java.util.*;

import dpdl.dpdlDpdlEngine.DpdlEngine;
import dpdl.dpdlDpdlEngine.Type;
import dpdl.dpdlDpdlEngine.mslsDpdlParams;
import dpdl.dpdlVisualizer.mslsVisualizer;
import dpdl.dpdlInstall.DpdlInstaller;

public class DpdlClient extends DpdlEngine {

	private InputStreamReader system_in = null;
	private Vector execCodeBuffer = new Vector();

	mslsVisualizer visualResult__ = null;
	
	DpdlEngine enc_engine = null;

	public DpdlClient() {
		super(true, new dpdl.dpdlUI.Display());
		initClient();

	}

	public DpdlClient(String config_file) {
		super(config_file, true, new dpdl.dpdlUI.Display());
		initClient();

	}
	public DpdlClient(boolean dummy) {
		super(true, new dpdl.dpdlUI.Display());

	}

	void initClient() {
		if (mslsDpdlParams.EXEC_STARTUP_CODE) {
			DPDLAPI_execStartupCode();
		} else {
			initDpdlConsole();
		}
	}

	void printHelp() {
		System.out.println("Usage: ");
		System.out.println(" -l  List Dpdl Packets installed");
		System.out.println(" -i  Install Dpdl Packet");
		System.out.println(" -d  Deinstall Dpdl Packet");
		System.out.println(" -la List Dpdl Packets allocated");
		System.out.println(" -a  Allocate Dpdl Packet");
		System.out.println(" -da Deallocate Dpdl Packet");
		System.out.println(" -qp Query Dpdl Packet");
		System.out.println(" -c Create Dpdl Packet");
		System.out.println(" -libs  List Dpdl Libraries");
		System.out.println(" -slib  Show Library");
		System.out.println(" -api   List Dpdl API functions");
		System.out.println(" -exec  Type && Execute a Dpdl script inbetween <script>   </script>");
		System.out.println(" -load  Load && Execute a Dpdl script (relative path in DPDL_LIBRARY_PATH eg. examples/dslsConsole.h");
		System.out.println(" -h  Help");
		System.out.println(" -q  Quit");
		System.out
				.println("###################################################################");

	}

	void listDpdlLibraries() {
		System.out.println("Dpdl Libraries->");
		String[] libs_h = DPDLAPI_listLibraries();
		if (libs_h != null) {
			for (int s = 0; s < libs_h.length; s++) {
				if(!libs_h[s].startsWith(".")){
					System.out.println(s + " : " + libs_h[s]);
				}
			}
		} else {
			System.out.println("No Dpdl library found!!");
		}

	}

	void showLibrary(int lib_i) {
		String[] libs_h = DPDLAPI_listLibraries();
		if (libs_h != null) {
			if (lib_i >= 0 && lib_i < libs_h.length) {
				dpdl.dpdlUtil.File f__ = new dpdl.dpdlUtil.File(
						mslsDpdlParams.DPDL_LIBRARY_PATH + libs_h[lib_i]);
				f__.print();
			} else {
				System.out.println("ERROR: invalid index");
			}
		} else {
			System.out.println("No Dpdl library found!!");
		}
	}

	void showDpdlAPI() {
		DPDLAPI_printAPI();
	}

	void initDpdlConsole() {
		system_in = new InputStreamReader(System.in);
		int read = 0;
		if (!mslsDpdlParams.EXEC_STARTUP_CODE) {
			System.out
					.println("---------------------------------------------\n");
			System.out.println("Dpdl Command console->\n");
			System.out.println("type -h for Help");
			//printHelp();

			char[] buf = new char[256];

			String pkgname; // Dpdl packet
			String chkname = "null";

			String[] chk_arr = null;
			
			String[] s; // for temp runtime info

			try {

			BufferedReader in = new BufferedReader(new InputStreamReader(
						System.in), 2);
				String read_str = "null";
				while (true) {
					read_str = in.readLine();
					//System.out.println("stdin>" + read_str);
					//switch (read_str) {
					if(read_str.equals("-l")){
						String[] n = getDpdlServiceNames();
						if (n != null) {
							
							if(n.length == 0){
								System.out.println("No packets installed");
							}else{
								System.out.println("Installed Dpdl Packets: ->");
								for (int z = 0; z < n.length; z++) {
									System.out.println("Dpdl->   " + n[z]);
								}
							}
						} else {
							System.out.println("Error in getting DpdlServiceNames");	
						}
						System.out
								.println("###################################################################");

					}else if(read_str.equals("-i")){
						System.out.print("enter the Dpdl packet to install:\n");
						pkgname = (in.readLine()).trim(); // "armin 3000";

						System.out.println("installing Dpdl Packet " + pkgname);
						if (DPDLAPI_installPacket(pkgname) == Type.dpdlTrue) {
							System.out.println("installed...");
						} else {
							System.out.println("Error: Packet not installed");
						}
						System.out
								.println("###################################################################");

					}else if(read_str.equals("-d")){
						System.out.print("enter the Dpdl packet to deinstall:\n");
						pkgname = (in.readLine()).trim();

						System.out.println("deinstalling Dpdl Packet " + pkgname);
						if (DPDLAPI_deinstallPacket(pkgname) == Type.dpdlTrue) {
							System.out.println("deinstalled...");
						} else {
							System.out.println("Error: Packet not deinstalled");
						}
						System.out
								.println("###################################################################");
						
					}else if(read_str.equals("-la")){
						Vector chunks = DPDLAPI_getAllocatedChunks(null);
						if(chunks.size() == 0){
							System.out.println("No allocated packets");
						}else{
							System.out.println("List allocated Packets:");
							for(int p = 0; p < chunks.size(); p++){
								String item = (String)chunks.elementAt(p);
								System.out.println("-> " + item);
							}
						}

					}else if(read_str.equals("-a")){

						System.out
								.print("enter the Dpdl-Packet to allocate ($package_name:$Chunk_name:)\n");
						chkname = (in.readLine()).trim();

						s = chkname.split(":");

						if(s.length > 1){
							pkgname = s[0];
							chkname = s[1];
							System.out.println("Packet name " + pkgname);
							System.out.println("Chunk " + chkname);
							chk_arr = new String[]{chkname};

							if(allocService(pkgname, chk_arr)){
								System.out.println("Dpdl service allocated successfully!...\n");
							}else{
								System.out.println("Error: Dpdl service Not allocated...\n");
							}

						}else{
							System.out.println("Syntax Not correct");
						}

						System.out
								.println("###################################################################");

					}else if(read_str.equals("-da")){
						System.out
						.print("enter the Chunk name to deallocate (with syntax $package_name:$Chunk_name):\n");
						chkname = (in.readLine()).trim();
				
						s = chkname.split(":");
     					if(s.length > 1){
							pkgname = s[0];
							chkname = s[1];
							
							System.out.println("Packet name " + pkgname);
							System.out.println("Chunk " + chkname);
							chk_arr = new String[]{chkname};
							
							DPDLAPI_clearDpdlChunks(pkgname, chk_arr);
						
						}else{
							System.out.println("Syntax Not correct");
						}
						System.out
								.println("###################################################################");

					}else if(read_str.equals("-qp")){
						System.out
						.print("enter the Chunk name to search ($package_name:$Chunk_name:\n");
						chkname = (in.readLine()).trim();
						
						s = chkname.split(":");
						if(s.length > 1){
								pkgname = s[0];
								chkname = s[1];
								
								System.out.println("Packet name " + pkgname);
								System.out.println("Chunk " + chkname);
								chk_arr = new String[]{chkname};
								
								System.out.print("enter the keyword:\n");
								String mK = (in.readLine()).trim();
								displayResult(mK, pkgname, new String[] { chkname });
	
							
							
							System.out.print("\n");
						}else{
							System.out.println("Syntax Not correct");
						}
						System.out
								.println("###################################################################");

					}else if(read_str.equals("-c")){
						enc_engine = new DpdlEngine(false);
						System.out.println("enter the Dpdl Script:");
						String dpdl_script = (in.readLine()).trim();

						System.out
								.println("enter name of Dpdl Packet to be created");
						String dpdl_packet = (in.readLine()).trim();
						
						try{
							if(enc_engine.DPDLAPI_compileDpdlScript(dpdl_script, dpdl_packet)){
								System.out.println("successfully compiled Dpdl Packet");
							}else{
								System.out.println("Error in compiling Dpdl Packet");
							}
						}catch(Exception e){
							System.out.println("Error in creating dpdl Packet. Please make sure the file exists and is valid");
						}
						enc_engine.deallocate();

					}else if(read_str.equals("-libs")){
						listDpdlLibraries();
						System.out
								.println("###################################################################");
					}else if(read_str.equals("-slib")){
						System.out.println("enter the library number:");
						String lib = (in.readLine());
						int index = Integer.parseInt(lib);
						showLibrary(index);
						System.out
								.println("###################################################################");
					}else if(read_str.equals("-api")){
						showDpdlAPI();

					}else if(read_str.equals("-exec")){
						execCodeBuffer = new Vector();
						String stripe = " ";
						String tmp_ = "";
						String incFile = "";
						if (DPDLAPI_initDpdlScripting() == 1) {
							System.out.print("<script>\n");
							while (!stripe.equals("</script>")) {
								stripe = (in.readLine()).trim();
								incFile = stripe;
								tmp_ = stripe;

								if (tmp_.length() >= 7) {
									tmp_ = tmp_.substring(0, 7);
								}
								if (tmp_.equals("include")) {
									incFile = incFile.substring(9,
											stripe.length() - 2);
									System.out.println("including file: "
											+ incFile);
									DPDLAPI_includeDpdlCode(incFile);
									System.out.println("code included...");
								} else {

									if (!stripe.equals("</script>")) {
										execCodeBuffer.addElement(stripe);

									}
								}

							}
							if (DPDLAPI_execDpdlCode(execCodeBuffer) == 1) {
								System.out.println("finished exec");
							} else {
								System.out.println("error in exec");
							}
						} else {
							System.out.println("scripting not available");
						}
						System.out
								.println("###################################################################");
					}else if(read_str.equals("-load")){
						System.out
								.println("enter the Dpdl script name to execute:");
						String code = (in.readLine());
						DPDLAPI_execCode(code);
						System.out.println("finished executing");
						System.out
								.println("###################################################################");

					}else if(read_str.equals("-h")){
						printHelp();
						System.out
								.println("###################################################################");
						
					}else if(read_str.equals("-q")){
						System.out.println("exiting ...Bye Bye:)");
						System.exit(0);
					}else{
						System.out.println("Invalid command");

					}
					System.out.println("\n");
				}

			} catch (Exception e) {

			}
		}
	}

	void displayResult(String key, String pkgname, String[] chkname) {
		String[] const_;
		String name, phoneNR, e_mail, target, trains, busses = null;
		visualResult__.setMaxResultSet(chkname[0], 2); // for Chunk Bolzano
		// visualResult__.setMaxResultSet(chkname[1], 2); // for Chunk AltaBadia
		// visualResult__.setMaxResultSet(chkname[2], 2); // for Chunk
		// AltaBadia_IMP

		const_ = new String[] { "armin 2000" };

		/*
		 * for(int x = 600; x < 610; x++){ const_[0] = "armin " + x;
		 * selectDpdlServices(DPDL_SERVICE_NAME, DPDL_SERVICEDATA, const_,
		 * visualResult__); }
		 */

		const_[0] = key;

		DPDLAPI_selectDpdlServices(pkgname, chkname, const_, visualResult__);

		System.out.println("querying service...");

		System.out.println("##############################################\n");
		System.out.println("Result:\n");
		visualResult__.projectData(chkname[0], key); // fix
		if (visualResult__.getDataState()) {
			int len = visualResult__.getDataLength();
			System.out.println("Nr. Entries:" + len + "\n");
			for (int i = 0; i < len; i++) {
				// get the variables --- in final implementation already casted
				if (pkgname.equals("dpdl_PHONEBOOK")
						|| pkgname.equals("ALTA_BADIA_PHONE")) {
					name = (String) visualResult__.d_b.DATA__[i].get("name");
					phoneNR = (String) visualResult__.d_b.DATA__[i]
							.get("phoneNR");
					e_mail = (String) visualResult__.d_b.DATA__[i]
							.get("e-mail");
					System.out
							.println("##"
									+ i
									+ "#####################################################");
					System.out.println("name: " + name);
					System.out.println("phone: " + phoneNR);
					System.out.println("e-mail: " + e_mail);
					System.out
							.println("----------------------------------------------------------------");
				} else if (pkgname.equals("TRAIN_BUS")) {
					target = (String) visualResult__.d_b.DATA__[i]
							.get("target");
					trains = (String) visualResult__.d_b.DATA__[i]
							.get("trains");
					System.out
							.println("##"
									+ i
									+ "#####################################################");
					System.out.println("TARGET: " + target);
					System.out.println("Trains " + trains);
					System.out
							.println("----------------------------------------------------------------");
				}

			}
			visualResult__.flushDataState(); // data_ready = false,
		}

	}

	boolean allocService(String pkgname, String[] chkname) {
		boolean status = false;
		int[] error = null;
		visualResult__ = new mslsVisualizer();
		try {

			status = DPDLAPI_mallocDpdlService(pkgname, visualResult__);
		} catch (Exception e) {
			// display.setCurrent(new Alert("Status", "malloc() ERROR", null,
			// AlertType.ERROR));
			status = false;
			System.out.println("error mallocDpdlService(string name)\n");
			
		}

		
		try {
			error = DPDLAPI_swapDpdlChunks(pkgname, chkname);
			if(error != null){
				status = true;
			}else{
				status = false;
			}
		} catch (Exception e) {
			status = false;
		}
		return status;
		
	}

	public static void main(String[] args) {
		/*
		if (args.length > 0 && args[0] != null && args[1] != null) {
			if (args[1].equals("638165")) {
				new DpdlClient(args[0]);
			} else {
				System.out
						.println("Error: unable to start DpdlEngine, contact support@seesolutions.it");
			}
			*/
		if(args.length > 0 && args[0].equals("-load") && args[1] != null){
			String code = args[1];
			new DpdlClient(true).DPDLAPI_execCode(code);
			System.out.println("finished executing");
			System.out
					.println("###################################################################");
		} else {
			new DpdlClient();
		}
	}

}
