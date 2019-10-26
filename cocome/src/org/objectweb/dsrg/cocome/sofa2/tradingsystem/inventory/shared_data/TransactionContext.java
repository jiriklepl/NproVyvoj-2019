package org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data;

/**
 * 
 * @author Yannick Welsch
 */
public interface TransactionContext {
	/**
	 * starts a new transaction
	 */
	void beginTransaction();
	
	/**
	 * commits the current transaction
	 */
	void commit();
	
	/**
	 * does a rollback on the current transaction
	 */
	void rollback();
	
	/**
	 * checks whether this transaction is still active
	 * @return 
	 * 	true, if this transaction is active
	 * 	false, else
	 */
	Boolean isActive();
}
