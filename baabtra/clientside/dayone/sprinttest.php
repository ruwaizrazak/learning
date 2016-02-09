<?php

$name=$_POST['username'];
$password=$_POST['password'];
$gender=$_POST['gender'];
$branch=$_POST['branch'];
$language="";
for($i=0;$i<count($_POST['languages']);$i++)
{
    $language.=$_POST['language'][$i].",";
}
mysql_connect("localhost","root","root") or die("abracadabra");
mysql_select_db("Baabtra1") or die ("oculus reparo db");
mysql_query("insert into sampletable (username,password,gender,branch,language) values('$name',$password,'$gender','$branch','$language')");


 
?>