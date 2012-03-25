package net.ponder2;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Ponder2BrokerInterface extends Remote {

	public void sendEvent(String event, String[] args) throws RemoteException;
}
