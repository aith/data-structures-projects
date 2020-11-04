// Ari Iramanesh, 1628897, 12M, a file to be compiled by Makefile functions
//-----------------------------------------------------------------------------
// HelloUser.java
// This is a really simple program to get you started.
// Prints greeting to stdout, then prints out some environment information.
//-----------------------------------------------------------------------------
class HelloUser2{
public static void main( String[] args ){
String userName = System.getProperty("user.name"); /* this should be you! */
String os = System.getProperty("os.name");
String osVer = System.getProperty("os.version");
String jre = System.getProperty("java.runtime.name");
String jreVer = System.getProperty("java.runtime.version");
String jvm = System.getProperty("java.vm.name");
String jvmVer = System.getProperty("java.vm.version");
String javaHome = System.getProperty("java.home");
long freemem = Runtime.getRuntime().freeMemory();/* scary if 0! */
long time = System.currentTimeMillis();
System.out.println("I love chicken pot pie");
System.out.println("Operating system: "+os+" "+osVer);
System.out.println("Runtime environment: "+jre+" "+jreVer);
System.out.println("Virtual machine: "+jvm+" "+jvmVer);
System.out.println("Java home directory: "+javaHome);
System.out.println("Free memory: "+freemem+" bytes");
System.out.printf("Time: %tc.%n", time);
}
}
