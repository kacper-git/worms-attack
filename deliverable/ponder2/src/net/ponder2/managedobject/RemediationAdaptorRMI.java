package net.ponder2.managedobject;

import java.lang.reflect.Method;

import java.rmi.RemoteException;
import java.rmi.NotBoundException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.Remote;
import java.util.HashMap;
import java.lang.reflect.InvocationTargetException;

import net.ponder2.RemediationAdaptorInterface;
import net.ponder2.objects.P2Object;
import net.ponder2.exception.Ponder2OperationException;
import net.ponder2.exception.Ponder2ArgumentException;
import net.ponder2.exception.Ponder2Exception;


/**
 * Implements an adaptor object for Ponder2 to communicate with external remediation mechanisms. 
 * External remediation mechanisms must implement the interface eu.resumenet.mechanisms.RemediationInterface.
 * An instance of RemediationAdaptor then locates the external mechanisms and provides a wrapper for
 * accessing it from a Ponder2 application (so policies can execute actions on it).
 * 
 * @author alberto
 */
public class RemediationAdaptorRMI implements RemediationAdaptorInterface {
	
	protected HashMap<String, String> operations;
	protected String address = null;
	protected String type = null;
	
	private Remote adaptorRMI = null;
	
	/**
	 * Creates an instance of the adaptor by locating the RMI remote object that this 
	 * adaptor will refer to, based on the server and object name used by the mechanism.
	 * 
	 */
	protected RemediationAdaptorRMI(P2Object address, P2Object type) {

		try {
			//extract the arguments
			this.address = address.asString();
			this.type = type.asString();
			
		} catch (Ponder2ArgumentException p2ae) {
			p2ae.printStackTrace();
		} catch (Ponder2OperationException p2oe) {
			p2oe.printStackTrace();
		}
		
		this.operations = new HashMap<String, String>();
		
		try {
			//Extracts the server name and the object name from the address string
			String serverNameTmp = address.asString().substring(address.asString().indexOf("://") + 3,address.asString().lastIndexOf("/"));
			String objectNameTmp = address.asString().substring(address.asString().lastIndexOf("/") + 1);
			
			//locate the remote object that this adaptor refers to
			Registry registry = LocateRegistry.getRegistry(serverNameTmp);
			this.adaptorRMI = (Remote) registry.lookup(objectNameTmp);
			
		} catch (Ponder2ArgumentException p2ae) {
			p2ae.printStackTrace();
		} catch (Ponder2OperationException p2oe) {
			p2oe.printStackTrace();
		} catch (NotBoundException nbe) {
			nbe.printStackTrace();
		} catch (RemoteException re) {
			re.printStackTrace();
		}
	}
	
	/**
	 * 
	 */
    public void addOperation(P2Object localOp, P2Object remoteOp) throws Ponder2Exception {
    	
    	this.operations.put(localOp.asString(), remoteOp.asString());
    }
	
	/**
	 * 
	 */
    public P2Object invoke(P2Object source, String localOp, P2Object... args) throws Ponder2ArgumentException, Ponder2OperationException, Ponder2Exception {
    	
    	System.out.println("Invoking operation: " + localOp);
    	
    	String remoteOp = this.operations.get(localOp);    	
    	Object argsTmp[] = RemediationAdaptor.convertArgumentTypes(args);
    	
    	Class[] argTypes = new Class[argsTmp.length];
    	for (int i = 0; i < argsTmp.length; i++) {
    		argTypes[i] = argsTmp[i].getClass();
    	}
    	
    	Object result = null;
    	
    	try {
    		Class c = Class.forName(this.type);
    		Object obj = c.cast(this.adaptorRMI);
    		Method method = obj.getClass().getMethod(remoteOp, argTypes);
    		
    		result = method.invoke(obj, argsTmp);
    		
    	} catch (ClassNotFoundException cnfe) {
    		cnfe.printStackTrace();
    	} catch (NoSuchMethodException nsme) {
    		nsme.printStackTrace();
    	} catch (IllegalAccessException iae) {
    		iae.printStackTrace();
    	} catch (InvocationTargetException ite) {
    		ite.printStackTrace();
    	}
    	
    	System.out.println("Done");
    	return null;
    }
}