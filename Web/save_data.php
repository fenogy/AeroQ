<?php
$host = 'localhost';
$user = 'test';
$pass = 'test';
$db = 'airq1';

$con=mysqli_connect($host,$user,$pass,$db);
//$con=mysqli_connect($host,$user,$db);

if (mysqli_connect_errno($con)){
	echo "Failed to connect to MySQL Server: " . mysqli_connect_error();
}
/*
echo $_POST['devID'];
echo $_POST['lon'];
echo $_POST['lat'];
echo $_POST['alt'];
echo $_POST['pres'];
echo $_POST['tmp'];
echo $_POST['hum'];
echo $_POST['airq'];
echo $_POST['co'];
echo $_POST['dust'];
echo $_POST['co2'];
*/
$datetime = date("Y-m-d H:i:s"); 
//$datetime = ($datetime + 19800);
mysqli_query($con,"INSERT INTO airq_data (DeviceID, 
										DateTime, 
										LON, 
										LAT, 
										ALT, 
										PRESSURE, 
										TEMPERATURE, 
										HUMIDITY, 
										CO, 
										AIRQ, 
										DUST, 
										CO2
										) VALUES ('{$_POST['devID']}',
										'{$datetime}', 
										'{$_POST['lon']}', 
										'{$_POST['lat']}', 
										'{$_POST['alt']}',
										'{$_POST['pres']}', 
										'{$_POST['tmp']}', 
										'{$_POST['hum']}', 
										'{$_POST['airq']}',
										'{$_POST['co']}',
										'{$_POST['dust']}',
										'{$_POST['co2']}' )");

mysqli_close($con);

header("Location: view_data.php");
//print 'Data Saved';
