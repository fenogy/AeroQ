<?php



$infoID=$_GET["dev"];
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
//print '<P>No of devices'.$noOfDevices.'</p>';

#Read the latest available data
$last_data = mysqli_fetch_array(mysqli_query($con,"SELECT * FROM airq_data ORDER BY DateTime DESC LIMIT 1"));


$lr = intval($last_data["ID"]);

#Definitions for hourly data
$hourlyRowIDs = array(0,0,0,0,0,0,0,0,0,0,0,0);
$hourlyData = array($lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID);

#Fetch Hourly data
#Data base must have atleast 144 or 12 hours data to support the Graphing data
// if($lr > 144){

	// for ($i=0;$i <12;$i++){
	
		 // $hourlyRowIDs[$i] = $lr - (12*$i);
		 // $hourlyData[$i] = mysqli_fetch_array(mysqli_query($con,"SELECT * FROM airq_data where ID={$hourlyRowIDs[$i]}"));
	
		 //print '<P>Hourly Row IDs are'.$hourlyData[$i]["DateTime"].'</p>';

	
	// }


// }

#Close the Database session
mysqli_close($con);


#Print Xml file upon get request
print $noOfDevices;
print ',';
print convertLonLat('7954.43');
print ',';
print convertLonLat('655.66');
print ',35.44,7957.43,658.66,35.44,1009,28.70,81.20%,39.00,5.00,NA,NA,NA';

#This fuction converts GPGGA values to be compatible with Google API
function convertLonLat($rawVal){
	
	$val = floatval($rawVal);
	$val = $val/100;
	$intVal = (int)$val;
	
	$rem60 = $val - $intVal;
	$rem100 = $rem60 * 10/6;

	return (string)round(($intVal+$rem100),6);
}
?>