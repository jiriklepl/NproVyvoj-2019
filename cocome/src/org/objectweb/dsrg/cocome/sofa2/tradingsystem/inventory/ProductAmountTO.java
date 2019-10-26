package org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory;

/**
 * Simple struct for product / amount.
 * <p>
 * Required for UC 8
 * @author kelsaka
 *
 */
public class ProductAmountTO {

	private ProductTO product;
	private long amount;
	
	/**
	 * Initializes the amount to "0".
	 *
	 */
	public ProductAmountTO() {
		this.amount = 0;
	}
	
	/**
	 * Amount of product.
	 * @return Current amount.
	 */
	public long getAmount() {
		return amount;
	}
	
	/**
	 * Amount of product.
	 * @param amount New amount.
	 */
	public void setAmount(long amount) {
		this.amount = amount;
	}
	
	/**
	 * Product
	 * @return a product
	 */
	public ProductTO getProduct() {
		return product;
	}
	
	/**
	 * Product
	 * @param product a product to set
	 */
	public void setProduct(ProductTO product) {
		this.product = product;
	}
	
	
	
}
