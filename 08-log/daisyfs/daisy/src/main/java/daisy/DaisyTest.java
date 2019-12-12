package daisy;

public class DaisyTest {
	
	private static class Tester implements Runnable {
		
		private int id;
		
		private FileHandle root;
		private FileHandle topdir;
		private FileHandle topfile;
		
		public Tester(int id, FileHandle root, FileHandle tdir, FileHandle tfile) {
			this.id = id;
			
			this.root = root;
			this.topdir = tdir;
			this.topfile = tfile;
		}

		@Override
		public void run() {
			
			System.out.println("Writing the string 'test' into file");
			DaisyDir.write(topfile, 0+4*id, 4, stringToBytes("test"));

			System.out.println("Reading the string 'test' from file");
			DaisyDir.read(topfile, 2*id, 4, new byte[4]);

			FileHandle file1 = new FileHandle();

			System.out.println("Creating new file in the directory");
			DaisyDir.creat(topdir, stringToBytes("file"+id), file1);

			System.out.println("Reading the string 'test' from file");
			DaisyDir.read(file1, 0, 4, new byte[4]);
				
			System.out.println("Writing the string 'test' into file");
			DaisyDir.write(file1, 2, 4, stringToBytes("test"));

			System.out.println("Reading the string 'test' from file");
			DaisyDir.read(topfile, 0, 4, new byte[4]);

			System.out.println("Writing the string 'test' into file");
			DaisyDir.write(topfile, 8+4*id, 4, stringToBytes("test"));
			
			System.out.println("Deleting file from the top level directory");
			DaisyDir.unlink(topdir, stringToBytes("file"+id));
			
			/*
			System.out.println("Disk contents:");
			Daisy.dumpDisk();
			*/
		}		
	}
	
	public static void main(String[] args) throws InterruptedException {
        FileHandle root = new FileHandle();
        
        root.inodenum = 0;
        Petal.init(false);
        
        System.out.println("Disk contents:");
        Daisy.dumpDisk();

		System.out.println("Creating top level directory in the root directory");
		FileHandle topdir = new FileHandle();
		DaisyDir.creat(root, stringToBytes("dir"), topdir);
        
		System.out.println("Creating file in the top level directory");
		FileHandle topfile = new FileHandle();
		DaisyDir.creat(topdir, stringToBytes("file"), topfile);

        final int count = 2;
        Thread[] threads = new Thread[count];
        
        for (int i = 0; i < count; i++) {
        	threads[i] = new Thread(new Tester(i, root, topdir, topfile));
        	threads[i].start();
        }
        
        for (int i = 0; i < count; i++) {
        	threads[i].join();
        }
	}
	
	static byte[] stringToBytes(String s) {
        byte[] b = new byte[s.length()];
        for (int i = 0; i < s.length(); i++) {
            b[i] = (byte)s.charAt(i);
        }
        return b;
    }

}
