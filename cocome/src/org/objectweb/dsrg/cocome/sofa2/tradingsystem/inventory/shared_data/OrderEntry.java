package org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data;

import javax.persistence.Basic;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToOne;

/**
 * The class OrderEntry represents a single productorder entry in the database
 * @author Yannick Welsch
 */
@Entity
public class OrderEntry {
	private long id;
	private long amount;
	private Product product;
	private ProductOrder productOrder;
	
	/**
	 * Gets identifier value
	 * @return The id.
	 */
	@Id
	@GeneratedValue(strategy = GenerationType.AUTO)
	public long getId() {
		return id;
	}

	/**
	 * Sets identifier.
	 * @param id Identifier value.
	 */
	public void setId(long id) {
		this.id = id;
	}
	
	
	
	/**
	 * @return The amount of ordered products
	 */
	@Basic
	public long getAmount() {
		return amount;
	}
	
	/**
	 * @param amount The amount of ordered products
	 */
	public void setAmount(long amount) {
		this.amount = amount;
	}
	
	/**
	 * @return The ProductOrder where the OrderEntry belongs to
	 */
	@ManyToOne
	public ProductOrder getOrder() {
		return productOrder;
	}
	
	/**
	 * @param productOrder The ProductOrder where the OrderEntry belongs to
	 */
	public void setOrder(ProductOrder productOrder) {
		this.productOrder = productOrder;
	}
	
	/**
	 * @return The product which is ordered
	 */
	@ManyToOne
	public Product getProduct() {
		return product;
	}
	
	/**
	 * @param product The product which is ordered
	 */
	public void setProduct(Product product) {
		this.product = product;
	}

	
}
