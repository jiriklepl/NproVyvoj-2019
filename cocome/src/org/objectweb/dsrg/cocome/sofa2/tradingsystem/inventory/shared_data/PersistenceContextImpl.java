package org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data;

import javax.persistence.EntityManager;

import org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.PersistenceContext;
import org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.TransactionContext;
/**
 * 
 * @author Yannick Welsch
 */
public class PersistenceContextImpl implements PersistenceContext {
	
	private EntityManager em;
	
	public EntityManager getEntityManager() {
		return em;
	}
	
	public PersistenceContextImpl(EntityManager em) {
		this.em = em;
	}

	public TransactionContext getTransactionContext() {
		return new TransactionContextImpl(em.getTransaction());
	}

	public void makePersistent(Object o) {
		em.persist(o);
	}

	public void close() {
		em.close();
	}
}
