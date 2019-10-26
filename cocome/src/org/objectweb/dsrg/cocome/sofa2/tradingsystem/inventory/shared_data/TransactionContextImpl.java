package org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data;

import javax.persistence.EntityTransaction;

import org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.TransactionContext;

/**
 * 
 * @author Yannick Welsch
 */
public class TransactionContextImpl implements TransactionContext {
	
	private EntityTransaction t;
	
	public TransactionContextImpl(EntityTransaction t) {
		this.t = t;
	}

	public void beginTransaction() {
		t.begin();
	}

	public void commit() {
		t.commit();
	}

	public void rollback() {
		t.rollback();
	}

	public Boolean isActive() {
		return t.isActive();
	}
}
