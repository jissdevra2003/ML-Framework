import java.io.*;
import java.util.*;
public class JavaExecution
{
public static void main(String args[])
{
try
{
if(args.length!=1)
{
System.out.println("Pass the value of temperature");
return;
}
String line;
String err;
String lines[]=new String[2];
lines[0]="IceCreamSalesProfitPredictorApp.exe";
lines[1]=args[0];  //temperature
//we will pass the lines[] array as command line arguments for the predictor app
//IceCreamSalesPredictorApp.exe temperature_value

Process p=Runtime.getRuntime().exec(lines);
BufferedReader inputBufferReader;
BufferedReader errBufferReader;

//now the predictor app wil give either the output which will be treated as input here
//or the app will give error 

//the following line will read the input stream
inputBufferReader=new BufferedReader(new InputStreamReader(p.getInputStream()));
line=inputBufferReader.readLine();  //the output of the predictor app received as input for java execution 

//the following line will read the error stream from standard error buffer(if any error comes).
errBufferReader=new BufferedReader(new InputStreamReader(p.getErrorStream()));
err=errBufferReader.readLine();  // error received from the standard error buffer 
inputBufferReader.close();
errBufferReader.close();
if(line!=null)  // if input is received then print the prediction
{
double prediction=Double.parseDouble(line);
System.out.println("Predicted profit in USD($) :"+prediction);
}
else if(err!=null) // if error is received 
{
System.out.println("Oops some problem occured "+err);
}
else 
{
System.out.println("Unable to predict profit");
}
}catch(Exception exception)
{
System.out.println(exception);
}
}
}