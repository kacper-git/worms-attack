package net.ponder2.managedobject;

import java.net.MalformedURLException;
import java.net.URL;
import java.util.HashMap;

import org.apache.xmlrpc.XmlRpcException;
import org.apache.xmlrpc.client.XmlRpcClient;
import org.apache.xmlrpc.client.XmlRpcClientConfigImpl;

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
public class RemediationAdaptorRPC implements RemediationAdaptorInterface {
	
	protected HashMap<String, String> operations;
	protected String address = null;
	protected String type = null;
	
	private XmlRpcClient adaptorRPC = null;
	
	/**
	 * Creates an instance of the adaptor by locating the RPC remote object that this 
	 * adaptor will refer to, based on address of the mechanism.
	 * 
	 */	
	protected RemediationAdaptorRPC(P2Object address, P2Object type) {
		
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
		
		XmlRpcClientConfigImpl config = new XmlRpcClientConfigImpl();
	    
		try {
			config.setServerURL(new URL(address.asString()));
		} catch (Ponder2ArgumentException p2ae) {
			p2ae.printStackTrace();
		} catch (Ponder2OperationException p2oe) {
			p2oe.printStackTrace();
		} catch (MalformedURLException mue) {
	    	mue.printStackTrace();
	    }
	    
		this.adaptorRPC = new XmlRpcClient();
		this.adaptorRPC.setConfig(config);
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
    	
    	Object result = null;
    	
    	try {
	    	result = this.adaptorRPC.execute(this.type + "." + remoteOp, argsTmp);
	    } catch (XmlRpcException xre) {
	    	xre.printStackTrace();
	    }

    	System.out.println("Done");
    	return null;
    }
}