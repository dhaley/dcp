// Copyright 12/04/06 Sun Microsystems, Inc. All Rights Reserved
// @(#)jsynprog.java 1.15 06/12/04 SMI

import java.util.*;
import java.io.*;
import java.text.*;

class jsynprog 
{
    private static String	dir_home;
    private static PrintWriter	log;
    private static double 	pstart, cstart;

    /* JNI calls */
    public  static native double Timer();
    private static native double cTimer();
    private static native double computeSet();
    private static native int JavaJavaC(int np, int scale);
    private static native void JavaCC(int scale);
    private static native void JavaCJava(int scale);
    private static native int isJVMPI();

    public static double testtime = 3.0 * 1e9;

    public static void main (String [] args)
    {
	jsynprog jsyn_obj = new jsynprog();
	Integer ni;
	int scale = 10;

	createAcct();
	LoadJNILibrary(args);
        testtime = computeSet();

	/* check for invocation parameter */
	if (args.length != 0) {
	    if (args[0].equals("fast")) {
		scale = 100;
	    } else if (args[0].equals("slow")) {
		scale = 1;
	    } else {
		System.err.println("fatal: unexpected argument: " + args[0] );
		System.exit(1);
	    }
	}

	/* large memory allocations, trigger gc */
	Routine rtn = new Routine();
	Sub_Routine sbrt = new Sub_Routine();
	recTime(); 
	rtn.memalloc(10000, scale);
	printValue("Routine.memalloc",null);

	/* add integers */
	recTime(); 
	ni = new Integer (rtn.add_int(scale));
	printValue("Routine.add_int",ni);

	/* add double */
	recTime(); 
	Double nd = new Double(rtn.add_double(scale)); 
	printValue("Routine.add_double",nd);

	/* call method in derived class */ 
	recTime(); 
	ni = new Integer (sbrt.add_int(scale));
	printValue("Sub_Routine.add_int",ni);

	/* call method that defines an inner class */ 
	recTime(); 
	Integer[] na = rtn.has_inner_class(scale);
	printValue("Routine.has_inner_class",na[1]);

	/* recursion */ 
	recTime(); 
	rtn.recurse(0,80, scale);
	printValue("Routine.recurse",null);

	/* deep recursion */ 
	recTime(); 
	rtn.recursedeep(0,500, scale);
	printValue("<Truncated-stack>",null);

	/* indirect recursion */ 
	recTime(); 
	rtn.bounce(0,20, scale);
	printValue("Routine.bounce",null);

	/* array operations */ 
	recTime(); 
	rtn.array_op(scale);
	printValue("Routine.array_op",null);

	/* Vector operations */ 
	recTime(); 
	rtn.vector_op(scale);
	printValue("Routine.vector_op",null);

	/* spend time in system calls */ 
	recTime(); 
	rtn.sys_op(scale);
	printValue("Routine.sys_op",null);

	/* java->java->c */
	recTime(); 
	int np = 0;
	jni_JavaJavaC(np, scale);
	printValue("jsynprog.jni_JavaJavaC",null);

	/* java->c->c */
	recTime(); 
	JavaCC(scale);
	printValue("jsynprog.JavaCC",null);

	/* java->c->java */
	recTime(); 
	JavaCJava(scale);
	printValue("jsynprog.JavaCJava",null);
     
     
	/* dynamically loaded classes */
	/* java version must be 1.5.0 or higher and */
	/* agent library must be based on JVMPI */
	String java_ver = System.getProperty("java.version");
	if (isJVMPI() != 0) {
	    Launcher lnch = new Launcher();
	    String[] params = new String[]{"DynLoadedClass"};
	    recTime();
	    lnch.main(params);
	    printValue("Launcher.main",null);
	}

	System.gc();
   }

   /* 
    ** Create accounting file 
    */
   private static void createAcct() {
	System.out.println ("Directing output to acct file...");
	try {
	   log = new PrintWriter (new FileWriter("jsynprog.acct"),true);
	} catch (IOException ioe) {
	   ioe.printStackTrace();
	   System.err.println("fatal: Cannot create accounting file ");
	   System.exit(1);
	}

	log.println("Function\t\t\tValue\t\tLWPTime\t\tCPUTime");
	log.print("============================================");
	log.println("============================================");
   }

   /* 
    ** Print output in acct file 
    */
   private static void printValue (String fname, Object obj) {
	double	p_end = Timer();	 // Global.Timer();
	double	c_end = cTimer();	// Global.cTimer();
	int	nspace = 30 - fname.length();
	double	prog_elapsed = p_end - pstart;
	double	cpu_elapsed = c_end - cstart;
	DecimalFormat     format_decimal = new DecimalFormat("0.000");

	log.print(fname);
	System.out.println("Running " + fname + "; T = " + format_decimal.format(prog_elapsed * 0.000000001)
		+" UCPU = " + format_decimal.format(cpu_elapsed * 0.000000001));
	for (int i =0; i<nspace;i++) {
	    log.print(" ");
	}
	log.print(obj + "\t\t" + format_decimal.format(prog_elapsed * 0.000000001));
	log.println("\t\t" + format_decimal.format(cpu_elapsed * 0.000000001));
   }

   /*
    ** Record intial times
    */
   private static void recTime() {
	pstart = Timer();	 // Global.Timer();
	cstart = cTimer();	// Global.cTimer();
   }

   /*
    ** Load dynamic shared library for JNI
    */
   private static void LoadJNILibrary(String[] args) {

	try {
	   dir_home = (new File(".")).getCanonicalPath();
	} catch (IOException e) {
	   dir_home = "..";
	}
	System.out.println("libpath:"+dir_home);

	// Find which JVM was invoked
	String jvm_format = System.getProperty("java.vm.name"); 
	System.out.println("jvm "+ jvm_format);
	int ver_idx = jvm_format.indexOf("64-Bit");
	System.out.println("version "+ ver_idx);
 
	try {
	    if (ver_idx > 0 ) {
		System.out.println("Loading 64-bit library....");
		System.load(dir_home + "/libcloop64.so");
	    }
	    else {
		System.out.println("Loading 32-bit library....");
		System.load(dir_home + "/libcloop.so");
	    }
	} catch (UnsatisfiedLinkError e) {
	   System.err.println("fatal: Cannot load shared library" + e);
	   System.exit(1);
	}
   }

   /*
    ** Makes a lot of JNI calls
    */ 
   private static void jni_JavaJavaC(int np, int scale) {
	int ret = 0;
	int jmax = 10000;
	System.out.println("Entering jni_JavaJavaC, scale = " + scale);
	double tEnd = Timer() + testtime;
	do {
	for (int j =0 ; j<jmax; j++) {
	    ret = JavaJavaC(np, scale);
	}
	} while (Timer() < tEnd);
   }

   public static int javafunc (int scale) {
	int jmax = 20*scale;
	int imax = 40000;
	int np = 0;
	// System.out.println("Entering javafunc, scale = " + scale);
	double tEnd = Timer() + testtime;
	do { np = 0;
	for (int j =0 ; j<jmax; j++) {
	    for (int i =0 ; i<imax; i++) {
		np = np + 1;
	    }
	}
	} while (Timer() < tEnd);
	return np;
   }
}
