package org.objectweb.dsrg.cocome.sofa2.tradingsystem.cashdeskline.cashdesk;

import java.io.Serializable;

import org.objectweb.dsrg.cocome.sofa2.tradingsystem.cashdeskline.PaymentMode;

public class PaymentModeEvent implements Serializable {

    private static final long serialVersionUID = -7394495671841623726L;

	private PaymentMode mode;

	public PaymentModeEvent(PaymentMode mode) {
		this.mode = mode;
	}

	public PaymentMode getMode() {
		return mode;
	}

}
