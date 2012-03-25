package net.ponder2.managedobject;

import java.rmi.RemoteException;



import java.rmi.NotBoundException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

//import eu.resumenet.mechanisms.core.AbstractDetectionInterface;

import net.ponder2.apt.*;
import net.ponder2.ManagedObject;
import net.ponder2.objects.*;
import net.ponder2.exception.Ponder2OperationException;
import net.ponder2.exception.Ponder2ArgumentException;


/**
 * Implements an adaptor object for Ponder2 to communicate with external detection mechanisms. 
 * External detection mechanisms must implement the interface eu.resumenet.mechanisms.DetectionInterface.
 * An instance of DetectionAdaptor then locates the external mechanisms and provides a wrapper for
 * accessing it from a Ponder2 application (for example, to deactivate a particular kind of detection).
 * 
 * @author alberto
 */
public class DetectionAdaptor implements ManagedObject {

	private static String serverName = null;
	private static String objName = null;
	//private AbstractDetectionInterface detection;
	
	/**
	 * Creates an instance of the adaptor by locating the RMI remote object that this 
	 * adaptor will refer to, based on the server and object name used by the mechanism.
	 * 
	 */
	@Ponder2op("create:host:")
	public DetectionAdaptor(P2Object objName, P2Object serverName) {
		
		try {
			//extract the arguments
			this.serverName = serverName.asString();
			this.objName = objName.asString();
			
		} catch (Ponder2ArgumentException p2ae) {
			p2ae.printStackTrace();
		} catch (Ponder2OperationException p2oe) {
			p2oe.printStackTrace();
		}
		
		try {
			//locate the remote object that this adaptor refers to
			Registry registry = LocateRegistry.getRegistry(this.serverName);
			//this.detection = (AbstractDetectionInterface) registry.lookup(this.objName);
			
		} catch (RemoteException re) {
			re.printStackTrace();
		}
	}
	
	/**
	 * TODO To implement methods that Ponder2 should be able to perform on detection mechanisms, 
	 * for example, activating or deactivating a particular kind of detection. 
	 * 
	 */
}