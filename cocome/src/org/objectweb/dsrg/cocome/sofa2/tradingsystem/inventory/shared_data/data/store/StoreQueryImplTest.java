package org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.data.store;

import org.objectweb.dsrg.sofa.SOFAClient;
import org.objectweb.dsrg.sofa.SOFALifecycle;
import org.objectweb.dsrg.sofa.SOFAThreadHelper;

import static org.junit.Assert.assertTrue;

import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;
import java.util.Enumeration;
import java.net.URL;
import java.io.IOException;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.lang.Runtime;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

import javax.persistence.spi.PersistenceProvider;

import org.hibernate.ejb.Ejb3Configuration;

import org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.*;

//import org.junit.After;
//import org.junit.Before;
//import org.junit.BeforeClass;
//import org.junit.Test;

class UsedMemoryThread extends Thread {
	
	Runtime runtime = Runtime.getRuntime();
	PrintWriter out = null;
	
	public UsedMemoryThread(String file)
	{   	
		try {
			out = new PrintWriter(new FileOutputStream(file));
		} catch (Exception e) {
			System.out.println("Exception raised");
		}
	}
	
	public void run()
	{
		while(!StoreQueryImplTest.testEnd)
		{
			System.out.println("Used Memory: " + (runtime.totalMemory() - runtime.freeMemory()));
			
			out.println(runtime.totalMemory() - runtime.freeMemory());
		
			try {
				Thread.sleep(1000);
			} catch (Exception e) {
				System.out.println("Exception raised");
			}
		}
		out.close();
	}
}

class QueryThread extends Thread {
	
	EntityManager em = null; 
	
	public QueryThread()
	{
		em = StoreQueryImplTest.emf.createEntityManager();
	}
	
	public void run() {
		while (!StoreQueryImplTest.testEnd) {
			
			em.getTransaction().begin();
			Collection<Product> result = StoreQueryImplTest.store.queryProducts(65536, new PersistenceContextImpl(em));
//			
//			for (Product product : result)
//			{
//				System.out.println("Product name: " + product.getName() + "location: " + product.getBarcode());
//			}
			
			em.getTransaction().commit();
		}
		em.close();
	}
}

/**
 * tests the StoreQueryIf interface
 * @author Yannick Welsch
 */
@SuppressWarnings("unchecked")
public class StoreQueryImplTest implements SOFALifecycle, Runnable, SOFAClient {
	
	private static Ejb3Configuration cfg = new Ejb3Configuration();
	
	public static EntityManagerFactory emf;
	EntityManager em = null;
	public static StoreQueryIf store = null;
	
	public static boolean end = false;
	public static boolean testEnd = false;
	
	Store s1;
	StockItem si1, si2;
	ProductOrder o1;
	Product p1;
	
	//@BeforeClass
	public static void setUpClass() {
		cfg.configure ("inventory-manager", null);
	/*	
		cfg.addAnnotatedClass(org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.Store.class);
		cfg.addAnnotatedClass(org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.ProductSupplier.class);
		cfg.addAnnotatedClass(org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.Product.class);
		cfg.addAnnotatedClass(org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.TradingEnterprise.class);
		cfg.addAnnotatedClass(org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.ProductOrder.class);
		cfg.addAnnotatedClass(org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.OrderEntry.class);
		cfg.addAnnotatedClass(org.objectweb.dsrg.cocome.sofa2.tradingsystem.inventory.shared_data.StockItem.class);
	*/

		emf = cfg.buildEntityManagerFactory();		
	}
	
	//@Before
	public void setUp() throws Exception {
		em = emf.createEntityManager();
		em.getTransaction().begin();
		
		s1 = new Store();
		em.persist(s1);
		
		si1 = new StockItem();
		si1.setAmount(100);
		si1.setMinStock(50);
		si1.setStore(s1);
		si2 = new StockItem();
		si2.setAmount(100);
		si2.setMinStock(200);
		si2.setStore(s1);
		
		o1 = new ProductOrder();
		o1.setStore(s1);
		p1 = new Product();
		//
		p1.setBarcode(777);
		//
		si2.setProduct(p1);
		
		em.persist(s1);
		em.persist(si1);
		em.persist(si2);
		em.persist(o1);
		em.persist(p1);

		em.getTransaction().commit();

	}

	//@After
	public void tearDown() throws Exception {
		em.close();
	}
	
	//@Test
	public void queryLowStockItems() {
		em.getTransaction().begin();
		em.refresh(s1);
		em.refresh(si2);
		Collection<StockItem> result = store.queryLowStockItems(s1.getId(), new PersistenceContextImpl(em));
		assertTrue(result.size() == 1 && result.iterator().next().getId() == si2.getId());
		em.getTransaction().commit();
	}
	
	//@Test
	public void queryProducts() {
		em.getTransaction().begin();
		em.refresh(s1);
		em.refresh(p1);
		Collection<Product> result = store.queryProducts(s1.getId(), new PersistenceContextImpl(em));
		assertTrue(result.size() == 1 && result.iterator().next().getId() == p1.getId());
		em.getTransaction().commit();
	}
	
	//@Test
	public void queryOrderById() {
		em.getTransaction().begin();
		em.refresh(o1);
		ProductOrder result = store.queryOrderById(o1.getId(), new PersistenceContextImpl(em));
		//TODO: Compare real equality
		assertTrue(result.getId() == o1.getId());
		em.getTransaction().commit();
	}

	//@Test
	public void queryStoreById() {
		em.getTransaction().begin();
		em.refresh(s1);
		Store result = store.queryStoreById(s1.getId(), new PersistenceContextImpl(em));
		//TODO: Compare real equality
		assertTrue(result.getId() == s1.getId());
		em.getTransaction().commit();
	}

	public void startTest (int threads) {
		
		UsedMemoryThread usedMemoryThread = new UsedMemoryThread(Integer.toString(threads) + ".txt");
		QueryThread[] queryThread = new QueryThread[threads];
		
		Runtime.getRuntime().gc();
		
		usedMemoryThread.start();
		
		for (int i = 0; i < threads; ++i)
		{
			System.out.println("Starting thread number: " + i);
			queryThread[i] = new QueryThread();
			queryThread[i].start();
		}
		
		System.out.println("Threads started");
		
		try {
			Thread.sleep(1000*60);
		} catch (Exception e) {
			System.out.println("Exception raised");
		}
		
		testEnd = true;
		
		for (int i = 0; i < threads; ++i)
		{
			try {
				queryThread[i].join();
			} catch (Exception e) {
				System.out.println("Exception raised");
			}
		}
		System.out.println("Finished");
	}
	
	public void run() {
		for (int i = 1; i <= 10; ++i)
		{
			System.out.println("Number of threads: " + i*10);
			testEnd = false;
			startTest(50*i);
		}
		end = true;
	}
	
	public void setRequired(String name, Object iface) {
		if (name.equals("StoreQueryIf")) {
			if (iface instanceof StoreQueryIf) {
				store = (StoreQueryIf) iface;
			}
		}
	}

	public void start() {		
		setUpClass();
		
		Thread t = new Thread(this);
		t.start();
	}

	public void stop() {
		end = true;
		try {
			tearDown();
		} catch (Exception e) {
			e.printStackTrace();
		}		
	}

	public void stopping() {
		// TODO Auto-generated method stub
	}
}
