package org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data;

import java.util.Collection;

import javax.persistence.Basic;
import javax.persistence.CascadeType;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToMany;
import javax.persistence.OneToMany;

/**
 * This class represents a TradingEnterprise in the database
 * @author Yannick Welsch
 */
@Entity
public class TradingEnterprise {

	private long id;
	private String name;
	private Collection<ProductSupplier> suppliers;
	private Collection<Store> stores;

	/**
	 * @return id A unique identifier for TradingEnterprise objects
	 */
	@Id
	@GeneratedValue(strategy = GenerationType.AUTO)
	public long getId() {
		return id;
	}

	/**
	 * @param id A unique identifier for TradingEnterprise objects
	 */
	public void setId(long id) {
		this.id = id;
	}

	/**
	 * @return Name of TradingEnterprise
	 */
	@Basic
	public String getName() {
		return name;
	}

	/**
	 * @param name Name of TradingEnterprise
	 */
	public void setName(String name) {
		this.name = name;
	}

	/**
	 * @return List of Stores related to the TradingEnterprise
	 */
	@OneToMany(mappedBy="enterprise", fetch=FetchType.LAZY, cascade=CascadeType.ALL)
	public Collection<Store> getStores() {
		return stores;
	}

	/**
	 * @param stores List of Stores related to the TradingEnterprise
	 */
	public void setStores(Collection<Store> stores) {
		this.stores = stores;
	}

	/**
	 * @return List of Suppliers related to the TradingEnterprise
	 */
	@ManyToMany(fetch=FetchType.LAZY, cascade=CascadeType.ALL)	
	public Collection<ProductSupplier> getSuppliers() {
		return suppliers;
	}

	/**
	 * @param suppliers List of Suppliers related to the TradingEnterprise
	 */
	public void setSuppliers(Collection<ProductSupplier> suppliers) {
		this.suppliers = suppliers;
	}
}
