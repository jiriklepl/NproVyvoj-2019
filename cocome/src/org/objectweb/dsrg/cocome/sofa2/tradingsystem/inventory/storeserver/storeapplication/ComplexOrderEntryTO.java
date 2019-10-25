package org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.storeserver.storeapplication;


/**
 * <code>ComplexOrderEntryTO</code> is used as transfer object class for transferring full order entry information
 * between client and the service-oriented application layer. It contains either copies of persisted
 * data which are transferred to the client, or data which is transferred from the client to the
 * application layer for being processed and persisted.
 * @author herold
 *
 */
public class ComplexOrderEntryTO extends OrderEntryTO {

	protected ProductWithSupplierTO productTO;

	/**
	 * Gets transfer object for product information of an order entry.
	 * @return Product transfer object with supplier information.
	 */
	public ProductWithSupplierTO getProductTO() {
		return productTO;
	}

	/**
	 * Sets product transfer object with supplier information for order entry.
	 * @param productTO Product transfer object to be set.
	 */
	public void setProductTO(ProductWithSupplierTO productTO) {
		this.productTO = productTO;
	}

}
