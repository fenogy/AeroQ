<?php

#Get the device ID from the main.js's HTTP GET request
$q=$_GET["dev"];

#Credentials for database acces 
$host = 'localhost';
$user = 'test';
$pass = 'test';
$db = 'airq1';

#This variable will used prepare the type of response
#If null no response or error will be reported
#if last the most recent data will be sent
#If full hourly data will be sent
$deviceDataStatus =null;

//print $q;
#Establish Database connection
$con=mysqli_connect($host,$user,$pass,$db);

#Report if any failure occurs
if (mysqli_connect_errno($con)){
	echo "Failed to connect to MySQL Server: " . mysqli_connect_error();
}


#Read the latest available data for the requested device ID
$last_data = mysqli_fetch_array(mysqli_query($con,"SELECT * FROM airq_data WHERE DeviceID={$q} ORDER BY DateTime DESC LIMIT 1"));
$lr = mysqli_fetch_array(mysqli_query($con,"SELECT COUNT(*) FROM airq_data WHERE DeviceID={$q}"));

//print '#';
//print $lr[0];
//print '#';
//$lr = intval($last_data["ID"]);

#Definitions for hourly data
$hourlyRowIDs = array(0,0,0,0,0,0,0,0,0,0,0,0);
$hourlyData = array($lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID);

#Fetch Hourly data
#Data base must have atleast 144 or 12 hours data to support the Graphing data
if($lr[0] >= 145){

	
	for ($i=0;$i <12;$i++){
	
		 $hourlyRowIDs[$i] = $lr[0] - (12*$i) - 1;
		 //$hourlyData[$i] = mysqli_fetch_array(mysqli_query($con,"SELECT * FROM airq_data where ID={$hourlyRowIDs[$i]}"));
		 #This special query will read the specific line number from the result table with LIMIT lineNumber,1 
		 $hourlyData[$i] = mysqli_fetch_array(mysqli_query($con,"SELECT * FROM airq_data where DeviceID={$q} LIMIT {$hourlyRowIDs[$i]},1"));
	
		//print '<P>Hourly Row IDs are'.$hourlyData[$i]["ID"].'</p>';

	
	}
	$deviceDataStatus ="full";

}else if ($lr[0] > 0 && $lr[0] < 145){

	#This means we dont have enough data for graphing function. Only single recent value will be sent
	$hourlyData[0] = mysqli_fetch_array(mysqli_query($con,"SELECT * FROM airq_data where DeviceID={$q} LIMIT {$lr[0]},1"));
	$deviceDataStatus ="last";

}else{

	#We dont have anything from the selected device. Dont have to send anything
	$deviceDataStatus =null;
}

#Close the Database session
mysqli_close($con);

if ($deviceDataStatus == null){

	print $q;
	print ',NA';

}else if ($deviceDataStatus == "last"){

	print $q;
	print ',last';
	print ',';
	print $hourlyData[0]['DateTime'];
	print ',';
	print $hourlyData[0]['ALT'];
	print ',';
	print $hourlyData[0]['PRESSURE'];
	print ',';
	print $hourlyData[0]['TEMPERATURE'];
	print ',';
	print $hourlyData[0]['HUMIDITY'];
	print ',';
	print $hourlyData[0]['CO'];
	print ',';
	print $hourlyData[0]['AIRQ'];
	print ',';
	print $hourlyData[0]['DUST'];
	print ',';
	print $hourlyData[0]['CO2'];


}else if ($deviceDataStatus == "full"){

	print $q;
	print ',full';
	
	for ($j = 0; $j<12 ; $j++){
	
		print ',';
		print ($j+1);
		print ',';
		print $hourlyData[$j]['DateTime'];
		print ',';
		print $hourlyData[$j]['ALT'];
		print ',';
		print $hourlyData[$j]['PRESSURE'];
		print ',';
		print $hourlyData[$j]['TEMPERATURE'];
		print ',';
		print $hourlyData[$j]['HUMIDITY'];
		print ',';
		print $hourlyData[$j]['CO'];
		print ',';
		print $hourlyData[$j]['AIRQ'];
		print ',';
		print $hourlyData[$j]['DUST'];
		print ',';
		print $hourlyData[$j]['CO2'];

		
	}
}


?>