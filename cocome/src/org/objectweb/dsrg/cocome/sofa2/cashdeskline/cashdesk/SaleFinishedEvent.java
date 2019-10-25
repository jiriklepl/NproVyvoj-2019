package org.objectweb.dsrg.cocome.sofa2.tradingsystem.cashdeskline.cashdesk;

import java.io.Serializable;

/**
 * This event is raised by the cashbox controller component after the cashier
 * signals the end of a sale process (by hitting a key).
 * 
 */
public class SaleFinishedEvent implements Serializable {

	private static final long serialVersionUID = -1198744791703155060L;

	public SaleFinishedEvent() {

	}
}
