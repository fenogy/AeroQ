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

$result = mysqli_query($con,"SELECT * FROM airq_data");
$last_data = mysqli_query($con,"SELECT * FROM airq_data ORDER BY DateTime DESC LIMIT 1");

print '<TABLE border="1">';
print '<TH>Record Number</TH> <TH>DeviceID</TH> <TH>DateTime</TH> <TH>LON</TH> <TH>LAT</TH> <TH>ALT</TH> <TH>PRESSURE</TH> <TH>TEMP</TH><TH>HUMIDITY</TH> <TH>CO</TH>
<TH>AIRQ</TH><TH>DUST</TH><TH>O2</TH>';
while($row = mysqli_fetch_array($result)){
	print '<TR>';
		print '<TD style="border:solid 1px #060">'.$row['ID'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row['DeviceID'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row['DateTime'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row['LON'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row['LAT'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row['ALT'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row['PRESSURE'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row['TEMPERATURE'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row['HUMIDITY'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row['CO'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row['AIRQ'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row['DUST'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row['CO2'].'</TH>';
	print '</TR>';
}
print '</TABLE>';

print '<TABLE border="1">';
$row2 ="";
while($row2 = mysqli_fetch_array($last_data)){
	$lastRowID = $row2;
	print '<TR>';
		print '<TD style="border:solid 1px #060">'.$row2['ID'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row2['DeviceID'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row2['DateTime'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row2['LON'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row2['LAT'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row2['ALT'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row2['PRESSURE'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row2['TEMPERATURE'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row2['HUMIDITY'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row2['CO'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row2['AIRQ'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row2['DUST'].'</TH>';
		print '<TD style="border:solid 1px #060">'.$row2['CO2'].'</TH>';
	print '</TR>';
}
print '</TABLE>';

/*$lastRowID = $last_data['ID'];
print '<P>Last Row is</P>';

print '</P>';*/
$lr = intval($lastRowID["ID"]);

$hourlyRowIDs = array(0,0,0,0,0,0,0,0,0,0,0,0);
$hourlyData = array($lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID,$lastRowID);

if($lr > 144){

	for ($i=0;$i <12;$i++){
	
		 $hourlyRowIDs[$i] = $lr - (12*$i);
		 $hourlyData[$i] = mysqli_fetch_array(mysqli_query($con,"SELECT * FROM airq_data where ID={$hourlyRowIDs[$i]}"));
	
		print '<P>Hourly Row IDs are'.$hourlyData[$i]["DateTime"].'</p>';

	
	}


}
mysqli_close($con);



//$lastRowID = 56;
print '<P>Last Row is';
print $lastRowID["ID"];
print $lr;
print '</P>';

print '<br/><a href="index.php">Go to Form</a>';

