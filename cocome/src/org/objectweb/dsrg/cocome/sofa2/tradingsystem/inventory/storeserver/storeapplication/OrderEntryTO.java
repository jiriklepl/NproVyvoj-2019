package org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.storeserver.storeapplication;

/**
 * <code>OrderEntryTO</code> is used as transfer object class for transferring basic order entry information
 * between client and the service-oriented application layer. It contains either copies of persisted
 * data which are transferred to the client, or data which is transferred from the client to the
 * application layer for being processed and persisted.
 * @author herold
 *
 */

public class OrderEntryTO {

	protected long amount;

	/**
	 * Gets value of amount attribute of an order entry.
	 * @return Amount.
	 */
	public long getAmount() {
		return amount;
	}

	/**
	 * Sets value of amount attribute of an order entry.
	 * @param amount
	 */
	public void setAmount(long amount) {
		this.amount = amount;
	}
}
