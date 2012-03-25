package net.ponder2;

import net.ponder2.exception.Ponder2ArgumentException;
import net.ponder2.exception.Ponder2Exception;
import net.ponder2.exception.Ponder2OperationException;
import net.ponder2.objects.P2Object;

public interface RemediationAdaptorInterface {

	public P2Object invoke(P2Object source, String localOp, P2Object... args) throws Ponder2ArgumentException, Ponder2OperationException, Ponder2Exception;
	
	public void addOperation(P2Object localOp, P2Object remoteOp) throws Ponder2Exception;
}
