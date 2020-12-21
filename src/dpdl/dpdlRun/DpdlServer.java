package dpdl.dpdlRun;

/**
 Dpdl(tm) -- Dynamic Packet Definition Language
 copyright(c) 2003-2006 Armin Costa

 www.seesolutions.it


 Author:  Armin Costa
 e-mail:  armincosta@hotmail.com

 */

import java.io.*;
import java.util.Vector;

import dpdl.dpdlDpdlEngine.DpdlEngine;
import dpdl.dpdlDpdlEngine.Type;
import dpdl.dpdlDpdlEngine.mslsDpdlParams;

public class DpdlServer extends DpdlEngine {
	private InputStreamReader system_in = null;

	static String dpdl_file = "null";

	public DpdlServer() {
		super(false);
	}

	void printHelp() {
		System.out.println("Usage: ");
		System.out.println(" -c -> Create Dpdl Packet");
		System.out.println(" -h  -> Help");
		System.out.println(" -q  -> Quit");
		System.out
				.println("###################################################################");

	}

	void initDpdlConsole() {
		system_in = new InputStreamReader(System.in);
		if (!mslsDpdlParams.EXEC_STARTUP_CODE) {
			System.out
					.println("---------------------------------------------\n");
			System.out.println("Dpdl Command console->\n");
			System.out.println("type h for Help");
			printHelp();

			char[] buf = new char[256];

			String dpdl_script = "null";
			String dpdl_packet = "null";

			String[] chk_arr = null;

			try {
				BufferedReader in = new BufferedReader(new InputStreamReader(
						System.in));
				String read_str = "null";
				while (!read_str.equals("-q")) {
					read_str = in.readLine();
					//switch (read_str) {
					if(read_str.equals("-c")){
						System.out.println("enter the Dpdl Script:");
						dpdl_script = (in.readLine()).trim();

						System.out
								.println("enter name of Dpdl Packet to be created");
						dpdl_packet = (in.readLine()).trim();
						
						DPDLAPI_compileDpdlScript(dpdl_script, dpdl_packet);
						
						System.out
								.println("###################################################################");

					}else if(read_str.equals( "-h")){
						printHelp();
						System.out
								.println("###################################################################");

					}else{
						System.out.println("Invalid command");

					}
					System.out.println("\n");
				}

			} catch (Exception e) {
				System.out.println("Error: " + e.getMessage());
				e.printStackTrace();
			}
		}
	}

	public static void main(String[] args) {
		new DpdlServer().initDpdlConsole(); 
	}

}
