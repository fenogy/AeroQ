<?php ?>
<form name="htmlform" method="post" action="save_data.php">
	<label for="url">DeviceID : </label>
	<input  type="text" name="devID" size="40"><br/>
	<label for="url">LON : </label>
	<input  type="text" name="lon" size="40"><br/>
	<label for="url">LAT : </label>
	<input  type="text" name="lat" size="40"><br/>
	<label for="url">ALT : </label>
	<input  type="text" name="alt" size="40"><br/>
	<label for="url">PRESSURE : </label>
	<input  type="text" name="pres" size="40"><br/>
	<label for="url">TEMP : </label>
	<input  type="text" name="tmp" size="40"><br/>
	<label for="url">HUMIDITY : </label>
	<input  type="text" name="hum" size="40"><br/>
	<label for="url">CO : </label>
	<input  type="text" name="co" size="40"><br/>
	<label for="url">AIRQ : </label>
	<input  type="text" name="airq" size="40"><br/>
	<label for="url">DUST : </label>
	<input  type="text" name="dust" size="40"><br/>
	<label for="url">CO2 : </label>
	<input  type="text" name="co2" size="40"><br/>
	<input type="submit" value="Save Data"> 
</form>

<a href='view_data.php'>View Data</a>
