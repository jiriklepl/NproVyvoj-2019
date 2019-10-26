package org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.data.store;

import java.util.*;

import javax.persistence.EntityManager;

import org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.PersistenceContext;
import org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.PersistenceContextImpl;
import org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.Product;
import org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.ProductOrder;
import org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.StockItem;
import org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.Store;
import org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.*;

public class StoreImpl implements StoreQueryIf
{
	// FillDB Code	
	/*
	public static final int NUMBEROF_ENTERPRISES = 10;
	public static final int NUMBEROF_STORES = 10;	// original 100
	public static final int NUMBEROF_STOCKITEMS = 100000;	// original 10000
	public static final int NUMBEROF_SUPPLIERS = 20;
	public static final int NUMBEROF_PRODUCTS = 1000;
	public static final int NUMBEROF_PRODUCTORDERS = 200;
	public static final int NUMBEROF_ORDERENTRIES = 20;
	
	List<TradingEnterprise> enterprises = new ArrayList<TradingEnterprise>();
	List<Store> stores = new ArrayList<Store>();
	List<ProductSupplier> suppliers = new ArrayList<ProductSupplier>();
	List<Product> products = new ArrayList<Product>();
	List<ProductOrder> productorders = new ArrayList<ProductOrder>();
	List<StockItem> stockitems = new ArrayList<StockItem>();
	List<OrderEntry> orderentries = new ArrayList<OrderEntry>();
	
	// -----------------------------------------------------
	// Constructor without parameters
	// -----------------------------------------------------

	public StoreImpl()
	{
		//Pseudo-random
		Random r = new Random(777);
		//fill Enterprises
		for(int i = 0; i < NUMBEROF_ENTERPRISES; i++) {
			TradingEnterprise enterprise = new TradingEnterprise();
			enterprise.setName("TradingEnterprise " + i);
			enterprises.add(enterprise);
		}
		
		//fill Stores and connect to Enterprises
		for(int i = 0; i < NUMBEROF_STORES; i++) {
			Store store = new Store();
			store.setName("Store " + i);
			store.setLocation("StoreLocation " + i);
			//select randomly TradingEnterprise to connect to Store
			TradingEnterprise enterprise = enterprises.get(
					r.nextInt(enterprises.size()));
			store.setEnterprise(enterprise);
			stores.add(store);
		}
		//fill Suppliers
		for(int i = 0; i < NUMBEROF_SUPPLIERS; i++) {
			ProductSupplier supplier = new ProductSupplier();
			supplier.setName("ProductSupplier " + i);
			suppliers.add(supplier);
		}
		//fill Products and connect to Suppliers
		for(int i = 0; i < NUMBEROF_PRODUCTS; i++) {
			Product product = new Product();
			//each barcode is different
			product.setBarcode(i + 777);
			product.setName("Product " + i);
			product.setPurchasePrice(Math.rint(100 *r.nextInt(10000) * 0.01) /100);
			//select randomly ProductSupplier to connect to Product
			ProductSupplier supplier = suppliers.get(
					r.nextInt(suppliers.size()));
			product.setSupplier(supplier);
			products.add(product);
		}
		//fill StockItems and connect to Stores and Products
		for(int i = 0; i < NUMBEROF_STOCKITEMS; i++) {
			StockItem stockitem = new StockItem();
			stockitem.setSalesPrice(Math.rint(100 *r.nextInt(10000) * 0.01) /100);
			stockitem.setAmount(r.nextInt(100));
			stockitem.setMinStock(r.nextInt(20));
			stockitem.setMaxStock(90+r.nextInt(18));
			//select randomly Store to connect to StockItem
			Store store = stores.get(
					r.nextInt(stores.size()));
			stockitem.setStore(store);
			//select randomly Product to connect to StockItem
			Product product = products.get(
					r.nextInt(products.size() - (NUMBEROF_PRODUCTS / 10)
							) );
			stockitem.setProduct(product);
			stockitems.add(stockitem);
		}
		//connect TradingEnterprise and ProductSupplier (n:m)
		for(TradingEnterprise enterprise : enterprises) {
			List<ProductSupplier> sup = new ArrayList<ProductSupplier>();
			for(double ra = r.nextDouble() * 1.0; ra < 1.; ra = r.nextDouble() * 1.2) {
				ProductSupplier supplier = suppliers.get(
						(int)Math.floor(ra * suppliers.size()));
				sup.add(supplier);
			}
			enterprise.setSuppliers(sup);
		}
		//fill ProductOrders and connect to Store
		for(int i = 0; i < NUMBEROF_PRODUCTORDERS; i++) {
			ProductOrder productorder = new ProductOrder();
			productorder.setOrderingDate(
					new Date(1166832000000L + ((long)i) * 86400000L));
			productorder.setDeliveryDate(
					new Date(1166832000000L + 2592000000L + ((long)i) * 86400000L));
			//select randomly Store to connect to ProductOrder
			Store store = stores.get(
					r.nextInt(stores.size()));
			productorder.setStore(store);
			productorders.add(productorder);
		}
		//fill OrderEntries and connect to Orders and Products
		for(int i = 0; i < NUMBEROF_ORDERENTRIES; i++) {
			OrderEntry orderentry = new OrderEntry();
			orderentry.setAmount(r.nextInt(1000) + 1);
			//select randomly ProductOrder to connect to OrderEntry
			ProductOrder productorder = productorders.get(
					r.nextInt(productorders.size()));
			orderentry.setOrder(productorder);
			//select randomly Product to connect to OrderEntry
			Product product = products.get(
					r.nextInt(products.size()));
			orderentry.setProduct(product);
			orderentries.add(orderentry);
		}
		
		System.out.println("StoreImpl: Objects initialized");
	}
	*/
	
	// -----------------------------------------------------
	// Implementation of the StoreQueryIf interface 'StoreQueryIf'
	// -----------------------------------------------------
	
	@SuppressWarnings("unchecked")
	public Collection<StockItem> queryLowStockItems(long storeId,
			PersistenceContext pctx) {
		EntityManager em = ((PersistenceContextImpl)pctx).getEntityManager();
		Collection<StockItem> result = Collections.emptySet();
		Store store = em.getReference(Store.class, storeId);

		result = em
				.createQuery(
						"select stockitem from StockItem as stockitem where stockitem.store = ?1 and stockitem.amount < stockitem.minStock")
				.setParameter(1, store).getResultList();

		return result;
	}
	
	@SuppressWarnings("unchecked")
	public Collection<StockItem> queryAllStockItems(long storeId,
			PersistenceContext pctx) {
		EntityManager em = ((PersistenceContextImpl)pctx).getEntityManager();
		Collection<StockItem> result = Collections.emptySet();
		Store store = em.getReference(Store.class, storeId);

		result = em
				.createQuery(
						"select stockitem from StockItem as stockitem where stockitem.store = ?1")
				.setParameter(1, store).getResultList();

		return result;
	}

	public ProductOrder queryOrderById(long orderId, PersistenceContext pctx) {
		EntityManager em = ((PersistenceContextImpl)pctx).getEntityManager();
		ProductOrder result = null;

		result = em.find(ProductOrder.class, orderId);

		return result;
	}

	public Store queryStoreById(long storeId, PersistenceContext pctx) {
		EntityManager em = ((PersistenceContextImpl)pctx).getEntityManager();
		Store result = null;

		result = em.find(Store.class, storeId);

		return result;
	}

	@SuppressWarnings("unchecked")
	public Collection<Product> queryProducts(long storeId, PersistenceContext pctx) {
		EntityManager em = ((PersistenceContextImpl)pctx).getEntityManager();
		Collection<Product> result = Collections.emptySet();

		Store store = em.getReference(Store.class, storeId);
		result = em
				.createQuery(
						"select product from Product as product where exists (select stockitem from StockItem as stockitem where stockitem.store = ?1 and stockitem.product = product)")
				.setParameter(1, store).getResultList();

		return result;
	}
	
	@SuppressWarnings("unchecked")
	public StockItem queryStockItem(long storeId, long productbarcode,
			PersistenceContext pctx) {
		EntityManager em = ((PersistenceContextImpl)pctx).getEntityManager();
		StockItem result = null;

		Collection<Product> prodref = em
				.createQuery(
						"select product from Product as product where product.barcode = ?1")
				.setParameter(1, productbarcode)
				.getResultList();
		if (prodref.size() == 0) {
			return null;
		}
		
		Store store = em.getReference(Store.class, storeId);
		Collection<StockItem> results = em
				.createQuery(
						"select stockitem from StockItem as stockitem where stockitem.store = ?1 and stockitem.product = ?2")
				.setParameter(1, store)
				.setParameter(2, prodref.iterator().next())
				.getResultList();
		//TODO: print Error if result.size() > 1
		if (results.size() > 0)
			result = results.iterator().next();

		return result;
	}

	public StockItem queryStockItemById(long stockId, PersistenceContext pctx) {
		EntityManager em = ((PersistenceContextImpl)pctx).getEntityManager();
		return em.getReference(StockItem.class, stockId);
	}

	public Product queryProductById(long productId, PersistenceContext pctx) {
		EntityManager em = ((PersistenceContextImpl)pctx).getEntityManager();
		return em.getReference(Product.class, productId);
	}
	
	/*
	 * (non-Javadoc)
	 * @see org.cocome.tradingsystem.inventory.data.store.StoreQueryIf#getStockItems(long[])
	 */
	@SuppressWarnings("unchecked")
	public Collection<StockItem> getStockItems(long storeId, long[] productIds, PersistenceContext pctx) {
		EntityManager em = ((PersistenceContextImpl)pctx).getEntityManager();	

		//TODO: implement SDQ
		StringBuilder sb = new StringBuilder();
		for(int x = 0; x < productIds.length; x++) {
			sb.append("stockitem.product.id = " + productIds[0]);
			if(x < productIds.length - 1) { //not last
				sb.append(" OR "); 
			}
		}
		
		Store store = em.getReference(Store.class, storeId);
		Collection<StockItem> results = em
				.createQuery(
						"SELECT stockitem FROM StockItem AS stockitem WHERE stockitem.store = ?1 AND (" + sb.toString() + ")")
				.setParameter(1, store)
				.getResultList();

		return results;
	}
	// Old implementation of StoreQueryIf
	/*
	public Store queryStoreById(long arg0, PersistenceContext arg1)  {
		// TODO Generated method
		return null;
	}
	
	public Collection<Product> queryProducts(long arg0, PersistenceContext arg1)  {
		// TODO Generated method
		return null;
	}
	
	public Collection<StockItem> queryLowStockItems(long arg0, PersistenceContext arg1)  {
		// TODO Generated method
		return null;
	}
	
	public Collection<StockItem> queryAllStockItems(long arg0, PersistenceContext arg1)  {
		// TODO Generated method
		return null;
	}
	
	public ProductOrder queryOrderById(long arg0, PersistenceContext arg1)  {
		// TODO Generated method
		return null;
	}
	
	public StockItem queryStockItem(long storeId, long productbarcode, PersistenceContext pctx)  {
		Product foundProduct = null;
		
		synchronized(products) {
			for (Product product : products) {
				if (product.getBarcode() == productbarcode) {
					foundProduct = product;
					break;
				}
			}
			if (foundProduct == null) return null;
		}
		
		synchronized(stockitems) {
			for (StockItem item : stockitems) {
				if (item.getProduct().equals(foundProduct) && item.getStore().getId() == storeId) {
					return item;
				}
			}
		}
		
		return null;
	}
	
	public StockItem queryStockItemById(long arg0, PersistenceContext arg1)  {
		// TODO Generated method
		return null;
	}
	
	public Product queryProductById(long arg0, PersistenceContext arg1)  {
		// TODO Generated method
		return null;
	}
	
	public Collection<StockItem> getStockItems(long arg0, long[] arg1, PersistenceContext arg2)  {
		// TODO Generated method
		return null;
	}
	*/
}

