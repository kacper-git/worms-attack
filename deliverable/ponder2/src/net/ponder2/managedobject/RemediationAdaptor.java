package net.ponder2.managedobject;

import net.ponder2.apt.*;
import net.ponder2.ManagedObject;
import net.ponder2.RemediationAdaptorInterface;
import net.ponder2.objects.P2Object;
import net.ponder2.objects.P2Number;
import net.ponder2.objects.P2String;
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
public class RemediationAdaptor implements ManagedObject {
	

	protected RemediationAdaptorInterface adaptor = null;
	
	/**
	 * Creates an instance of the adaptor by locating the RMI remote object that this 
	 * adaptor will refer to, based on the server and object name used by the mechanism.
	 * 
	 */
	@Ponder2op("create:type:")
	public RemediationAdaptor(P2Object address, P2Object type) {
		
		String addressStr = null;
		
		try {
			addressStr = address.asString();
			
		} catch (Ponder2ArgumentException p2ae) {
			p2ae.printStackTrace();
		} catch (Ponder2OperationException p2oe) {
			p2oe.printStackTrace();
		}
		
		if (addressStr.startsWith("rmi")) {
			// instantiates an RMI adaptor
			System.out.println("Creating RMI adaptor = " + addressStr);
			adaptor = (RemediationAdaptorInterface) new RemediationAdaptorRMI(address, type);
			
		} else if (addressStr.startsWith("http")) {
			//instantiates an RPC adaptor
			System.out.println("Creating RPC adaptor = " + addressStr);
			adaptor = (RemediationAdaptorInterface) new RemediationAdaptorRPC(address, type);
		}
	}
	
	/**
	 * 
	 */
	@Ponder2op("addOperation:remoteName:")
    public void addOperation(P2Object localOp, P2Object remoteOp) throws Ponder2Exception {
    	
    	this.adaptor.addOperation(localOp, remoteOp);
    }
    
	/**
	 * 
	 */
	 @Ponder2op(Ponder2op.WILDCARD)
	 public P2Object invoke(P2Object source, String localOp, P2Object... args) throws Ponder2ArgumentException, Ponder2OperationException, Ponder2Exception {
		 
		 return this.adaptor.invoke(source, localOp, args);
	 }
	
    /**
     * Convert Ponder2 argument types to one of the following: String, Float, Long.
     * 
     */
    protected static Object[] convertArgumentTypes(P2Object... args) throws Ponder2ArgumentException, Ponder2OperationException, Ponder2Exception {
    	
    	Object argsTmp[] = new Object[args.length];
    	
    	for (int i = 0; i < args.length; i++) {
    		
    		if (args[i].getClass().equals(P2String.class)) {
    			
    			argsTmp[i] = args[i].asString();
    		} 
    		else if (args[i].getClass().equals(P2Number.class)) {
    			
    			boolean hasDecimalPoint = ((args[i]).asNumber().toPlainString().indexOf(".") >= 0) ? true : false;
    			if (hasDecimalPoint) {
    				argsTmp[i] = new Double(args[i].asDouble());
    			} else {
    				argsTmp[i] = new Integer(args[i].asInteger());
    			}
    		} 
    		else {
    			throw new Ponder2ArgumentException("Type not supported: " + args[i].getClass());
    		}
    	}
    	return argsTmp;
    }
}