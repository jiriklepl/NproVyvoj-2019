package org.objectweb.dsrg.cocome.sofa2.tradingsystem.cashdeskline.cashdesk;

import java.io.Serializable;

/**
 * This event is raised by the cashdesk application component after having
 * calculated the change amount during cash payment.
 * 
 */
public class ChangeAmountCalculatedEvent implements Serializable {

	private static final long serialVersionUID = 3529515546013136702L;

	private double changeAmount;

	public ChangeAmountCalculatedEvent(double changeAmount) {
		this.changeAmount = changeAmount;
	}

	public double getChangeAmount() {
		return changeAmount;
	}
}
