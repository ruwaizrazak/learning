class parentclass
{
parentclass()
{
System.out.println("Hello world");
}
}
class childclass extends parentclass
{
childclass()
{
super();
}
}
class demosuper{
public static void main (String args[])
{
childclass cl=new childclass();
}
}

