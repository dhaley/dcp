/* Copyright 01/28/05 Sun Microsystems, Inc. All Rights Reserved
** @(#)Sub_Routine.java 1.3 05/01/28 SMI
** This is subclass of Routine , overrides one method
*/

public class Sub_Routine extends Routine {
    private static native double cTimer();

   /*
    ** Calls another method c() many times, overridden methos
    */
   public int add_int(int scale) {
	int w = 0;
	int kmax = 10000 * scale;
	double tEnd = jsynprog.Timer() + jsynprog.testtime;
	do { w = 0;
	for (int k=0 ; k<kmax; k++) {
	    w = addcall(w) + 1;
	}
	} while (jsynprog.Timer() < tEnd);
	return w;
   }

   private static int addcall(int x) {
	int jmax = 2000;
	for (int j=0; j<jmax;j++) {
	    x = x + 1;
	}
	return x;
   }

   public int naptime(int k, int scale)
   {
	int i;
	int imax = k * scale;

	try {
	    for (i = 0; i < imax; i++) {
		System.out.println(i + " sleeping");
		Thread.currentThread().sleep(1000);
		i=i+1;  
	    }
	} catch (InterruptedException e) {e.printStackTrace();}
	System.out.println("In naptime");
	return 0;
   }

}
