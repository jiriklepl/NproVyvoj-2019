package org.objectweb.dsrg.cocome.sofa2.tradingsystem.cashdeskline;

import org.objectweb.dsrg.cocome.sofa2.tradingsystem.AccountSaleEvent;

/**
 * This interface defines an event handler for events related to the cash box.
 */
public interface CashDeskEventDispatcherIf {
	void sendSaleRegisteredEvent(SaleRegisteredEvent saleRegisteredEvent);

	void sendAccountSaleEvent(AccountSaleEvent accountSaleEvent);
}
