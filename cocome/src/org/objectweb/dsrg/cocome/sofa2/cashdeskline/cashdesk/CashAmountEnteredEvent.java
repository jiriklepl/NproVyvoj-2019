package org.objectweb.dsrg.cocome.sofa2.tradingsystem.cashdeskline.cashdesk;

import java.io.Serializable;

/**
 * This event signals the entering of a cash amount at the cash box keyboard
 * after taking cash from the customer. It is raised by the cash box controller
 * component after EVERY key stroke, <code>isFinalInput()
 * </code> is true if
 * the final input is entered.
 * 
 */
public class CashAmountEnteredEvent implements Serializable {

	private static final long serialVersionUID = -5441935251526952790L;

	private KeyStroke keystroke;

	public CashAmountEnteredEvent(KeyStroke keystroke) {
		this.keystroke = keystroke;
	}

	public KeyStroke getKeyStroke() {
		return keystroke;
	}
}
