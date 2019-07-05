<?php

$host = 'localhost';
$user = 'test';
$pass = 'test';
$db = 'airq1';

#Establish Database connection
$con=mysqli_connect($host,$user,$pass,$db);

#Report if any failure occurs
if (mysqli_connect_errno($con)){
	echo "Failed to connect to MySQL Server: " . mysqli_connect_error();
}
#Find how many devices are available
$noOfDevicesR = mysqli_query($con,"SELECT DISTINCT DeviceID FROM airq_data ORDER BY DeviceID DESC");
$noOfDevices = mysqli_num_rows($noOfDevicesR);
$noOfDevices = $noOfDevices;

#Query device information of each device respectively
$deviceLocationsQ = mysqli_query($con,"SELECT DeviceID,LON,LAT FROM airq_data GROUP BY DeviceID");

#We now read the distinct device info from database and send to Page Load
print $noOfDevices;

while($row = mysqli_fetch_array($deviceLocationsQ)){
		
		print ',';
		print $row['DeviceID'];
		print ',';
		print convertLonLat($row['LON']);
		print ',';
		print convertLonLat($row['LAT']);

}

#Close the Database session
mysqli_close($con);

#This fuction converts GPGGA values to be compatible with Google API
function convertLonLat($rawVal){
	
	$val = floatval($rawVal);
	$val = $val/100;
	$intVal = (int)$val;
	
	$rem60 = $val - $intVal;
	$rem100 = $rem60 * 10/6;

	return (string)round(($intVal+$rem100),6);
}

#Print Xml file upon get request
// print $noOfDevices;
// print ',';
// print '1';
// print ',';
// print convertLonLat('7954.43');
// print ',';
// print convertLonLat('655.66');
// print ',';
// print '2';
// print ',';
// print convertLonLat('7957.43');
// print ',';
// print convertLonLat('658.66');
//print ',35.64';
//print ',1009,28.70,81.20%,39.00,5.00,NA,NA,NA';


?>