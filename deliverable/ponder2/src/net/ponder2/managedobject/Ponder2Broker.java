package net.ponder2.managedobject;

import java.util.HashMap;
import java.util.StringTokenizer;
import java.util.ArrayList;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

import java.net.*;
import java.io.*;

import net.ponder2.Ponder2BrokerInterface;

import net.ponder2.apt.*;
import net.ponder2.ManagedObject;
import net.ponder2.objects.*;
import net.ponder2.Util;
import net.ponder2.exception.Ponder2ArgumentException;
import net.ponder2.exception.Ponder2OperationException;
import net.ponder2.exception.Ponder2Exception;

/**
 * Provides an access interface to Ponder2 so external objects can publish events into the policy 
 * system. By default, Ponder2Broker is initialised as an RMI object, so external applications can 
 * locate it and inject events into Ponder2. Most likely to be used by external detection objects  
 * to signal the detection of a challenge.
 * 
 * @author alberto
 */
public class Ponder2Broker implements ManagedObject, Ponder2BrokerInterface {

	private static String objName = Ponder2Broker.class.getSimpleName();
	private P2Object myP2Object;
	private HashMap eventMap;
	private ServerSocket serverSocket = null;
	private static int SOCKET_PORT = 4444;
	
	/**
	 * Creates an instance of Ponder2Broker. Exports and binds this object,  
     * so Ponder2 can be accessed via RMI by the detection objects. The 
     * default RMI name is the class name ("Ponder2Broker"), but this can 
     * be overridden.
	 * 
	 */
	@Ponder2op("create")
	public Ponder2Broker(P2Object myP2Object) {
		
		this.eventMap = new HashMap();
		/*
		try {
			if (System.getSecurityManager() == null)
				System.setSecurityManager(new SecurityManager());
							
    		// exports and register this object
			Ponder2BrokerInterface stub = (Ponder2BrokerInterface) UnicastRemoteObject.exportObject(this, 0);
			Registry registry = LocateRegistry.getRegistry();
    		registry.rebind(objName, stub);
    		
    	} catch (RemoteException re) {
    		re.printStackTrace();
    	}
    	*/
    	
    	try {
    		// creates the server socket
    		serverSocket = new ServerSocket(this.SOCKET_PORT);
    		System.out.println("Socket is ready... " + SOCKET_PORT);
    	} catch (IOException ioe) {
    		ioe.printStackTrace();
    	}
    	
    	// creates a thread that will keep the socket open and will spawn new threads for 
    	// addressing each new connection
    	(new Thread() { public void run() { 
    		while (true) {
    			try {
    				Socket eventSource = serverSocket.accept();
    				new Ponder2BrokerThread(eventSource).start();
    			} catch (IOException ioe) {
    				ioe.printStackTrace();
    			}
    		}
    	}}).start();

    	this.myP2Object = myP2Object;
    	System.out.println("Server is ready... " + objName);		
	}
	
	private class Ponder2BrokerThread extends Thread {
		
		Socket eventSource = null;
		
		public Ponder2BrokerThread(Socket s) {
			eventSource = s;
		}
		
		public void run() {
			
			try {
				// read the event via the socket	
				BufferedReader in = new BufferedReader(new InputStreamReader(eventSource.getInputStream()));
				String inputLine = in.readLine();
				
				System.out.println("Read from socket = " + inputLine);
				
				// assumes the convention "eventName;param1;param2;" is followed
				StringTokenizer st = new StringTokenizer(inputLine, ";");
				ArrayList params = new ArrayList();
				
				// event name is the first token
				String eventName = st.nextToken();
				
				// remainder tokens are the parameters
				while (st.hasMoreTokens()) {
				
					String token = st.nextToken();
					params.add(token);
				}
				
				// raise the event locally
				sendEvent(eventName, (String[]) params.toArray(new String[] {}));
				
				// close stuff
				in.close();
				eventSource.close();
				
			} catch (IOException ioe) {
				ioe.printStackTrace();
			}
		}
	};
	
	/**
	 * Receives an alarm from an external detection application and injects an internal event 
	 * into the Ponder2 system (so it can trigger Ponder2 policies running locally).
	 * 
	 */
	@Ponder2op("sendEvent:args:")
	public void sendEvent(P2Object event, P2Object args) {
 		
		try {
			P2Object[] argsP2ObjectArray = args.asArray();
			String[] argsStringArray = new String[argsP2ObjectArray.length];
		
			for (int i = 0; i < argsP2ObjectArray.length; i++) {
				argsStringArray[i] = argsP2ObjectArray[i].asString();
			}
			this.sendEvent(event.asString(), argsStringArray);
			
		} catch (Ponder2ArgumentException p2ae) {
			p2ae.printStackTrace();
		} catch (Ponder2OperationException p2oe) {
			p2oe.printStackTrace();
		} catch (RemoteException re) {
			re.printStackTrace();
		}
	}
	
	/**
	 * Receives an alarm from an external detection application and injects an internal event 
	 * into the Ponder2 system (so it can trigger Ponder2 policies running locally).
	 * 
	 */
	public void sendEvent(String event, String[] args) throws RemoteException {
		
		System.out.println("Sending event...");
		try {
			P2Object eventObj = Util.resolve((String)this.eventMap.get(event));
			eventObj.operation(myP2Object, "create:", P2Object.create(args));
			
		} catch (Ponder2Exception p2e) {
			p2e.printStackTrace();
		}
	}
	
	/**
	 * Adds a mapping to the event map, which associates the name of an external event with
	 * an internal Ponder2 event used for triggering policies.
	 * 
	 */
	@Ponder2op("setEventMap:event:")
	public void p2_setEventMap(P2Object key, P2Object eventPath) {
		
		try {
			this.eventMap.put(key.asString(), eventPath.asString());
			
		} catch (Ponder2ArgumentException p2ae) {
			p2ae.printStackTrace();
		} catch (Ponder2OperationException p2oe) {
			p2oe.printStackTrace();
		}
	}
}