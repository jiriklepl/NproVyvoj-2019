package org.objectweb.dsrg.cocome.sofa2.tradingsystem;

public class AccountSaleEvent {

	private SaleTO sale;

	public AccountSaleEvent(SaleTO sale) {
		this.sale = sale;
	}

	public SaleTO getSale() {
		return sale;
	}
}
