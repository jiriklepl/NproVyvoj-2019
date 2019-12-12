/* 
 * This file is part of the Daisy distribution.  This software is
 * distributed 'as is' without any guarantees whatsoever. It may be
 * used freely for research but may not be used in any commercial
 * products.  The contents of this distribution should not be posted
 * on the web or distributed without the consent of the authors.
 *
 * Authors: Cormac Flanagan, Stephen N. Freund, Shaz Qadeer 
 * Contact: Shaz Qadeer (qadeer@microsoft.com)
 */

package daisy;

import java.io.*;

public class Petal {

    static public String petalDir = ".";
    static private RandomAccessFile disk = null;

    public static void init(boolean keepOld) {
	    try {
	        File f = new File(petalDir + File.separator + "PETAL");
	        boolean b = f.exists();
	        if (!keepOld && b) {
	            f.delete();
	            b = false;
	        }
	        disk = new RandomAccessFile(f, "rw");
	        if (!b) {
		    Daisy.init();
	        }
	    } catch (Exception e) {
	    	e.printStackTrace();
	        assert false : "can't make disk";
	    }
    }

    public static synchronized void write(long n, byte b) {
	try {
	    disk.seek(n);
	    disk.writeByte(b);
	    //Log.log("petal", "write " + n + " " + b);
	} catch (IOException e) {
		e.printStackTrace();
	}
    }

    public static synchronized void write(long loc, byte b[], int n) {
	try {
	    disk.seek(loc);
	    disk.write(b, 0, n);
	} catch (IOException e) {
	    e.printStackTrace();
	}
    }


    public static synchronized void read(long loc, byte b[], int n) {
	try {
	    int i;
	    if (loc + n >= disk.length()) {
		disk.setLength(loc + n);
	    }
	    disk.seek(n);
	    disk.read(b, 0, n);
	} catch (IOException e) {
		e.printStackTrace();
	}
    }

    public static synchronized byte read(long n) {
	try {
	    if (n >= disk.length()) {
		return 0;
	    }
	    disk.seek(n);
	    byte b = disk.readByte();
	    //Log.log("petal", "read " + n + " " + b);	
	    return b;
	} catch (IOException e) {
	    e.printStackTrace();
	    return 0;
	}
    }

    public static synchronized void writeLong(long n, long num) {
	for (int i = 0; i < 8; i++) {
	    write(n + i, (byte)(num & 0xff));
	    num = num >> 8;
	}
    }

    static public synchronized long readLong(long n) {
	long num = 0;
	for (int i = 7; i >= 0; i--) {
	    byte x = read (n + i);
	    num = (num << 8) + (x & 0xff);
	}
	return num;
    }

}
