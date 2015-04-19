
public class Driver {
	public static void main(String[] args) {
		String filename = "FordZTW.txt";
		System.out.println("Hello");
		// Build Automotive Object from the file <filename>
		Util.AutoIO builder = new Util.AutoIO();
		Model.Automotive FordZTW = builder.buildAutoObject(filename);
		System.out.println("Automotive built. Displaying toString():");
		System.out.println(FordZTW.toString());
	}
}
