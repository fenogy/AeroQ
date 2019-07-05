/*This is the Main Javascript for the web page where it handles all the behaviour in one place.
  additionally this script requires googles Map apis and eternal simple chart library
*/

/*Global variables defined here which are required to availble aat any place of the script*/
var selectedDevID = 1;
var noOfDevices = 1;
var deviceMarkers = new Array(25);  
var deviceMarkerPositions = new Array(25);
var chartStatus = false;

/*Map properties required to define a center of the map, here additional one is also created*/
var mapCenter=new google.maps.LatLng(6.920667,79.905352);
var marker2pos = new google.maps.LatLng(6.910667,79.872352);

/*data table 2D array stores all the graphing data for a single device*/
var dataTable = new Array();
dataTable[0] = new Array();
dataTable[1] = new Array();
dataTable[2] = new Array();
dataTable[3] = new Array();
dataTable[4] = new Array();
dataTable[5] = new Array();
dataTable[6] = new Array();

/*Some initializing code for the array*/
deviceMarkers[0]=null;
deviceMarkers[1]=null;

/*Creating Dummy markers for testing*/
var marker1=new google.maps.Marker({
  position:mapCenter,
  icon:'img/pins.png'
  });
var marker2=new google.maps.Marker({
  position:marker2pos,
  icon:'img/pins.png'
  });
 
/*This is the main entry point to the script*/  
function initialize() {
	
	//Define map properties
	var mapProp = {
		center:mapCenter,
		zoom:14,
		mapTypeId:google.maps.MapTypeId.ROADMAP,
		controls: false,
		scrollwheel: false,
		draggable: true,
		mapTypeControl:false,
		streetViewControl:false,
		zoomControl:false,
	};
  
	/*Initialize the map*/ 
	var map=new google.maps.Map(document.getElementById("googleMap"), mapProp);
	marker1.setMap(map);
	marker2.setMap(map);
	
	/*Once for each page refresh this function call will search for the available 
	  devices and place them on the map*/ 
	updateDevices(map);

	var infowindow = new google.maps.InfoWindow({content:"Dummy marker"});
	
	/*Place dummy markers on the map*/ 
	google.maps.event.addListener(marker1, 'click', function() {
		infowindow.open(map,marker1);
	});
	google.maps.event.addListener(marker2, 'click', function() {
		infowindow.open(map,marker2);
    });
  
	/*For each dash board element an event is defined for display the behaviour of the past 12 hrs*/
	document.getElementById("2").addEventListener("click", displayTmpGraph); 
	document.getElementById("4").addEventListener("click", displayPressureGraph);
	document.getElementById("6").addEventListener("click", displayHumidityGraph); 
	document.getElementById("8").addEventListener("click", displayCoGraph); 
	document.getElementById("10").addEventListener("click", displayAirqGraph);
	document.getElementById("12").addEventListener("click", displayDate);
	document.getElementById("14").addEventListener("click", displayDate); 


}

/*True entry point of the script*/  
google.maps.event.addDomListener(window, 'load', initialize);

/*True entry point of the script*/ 
var randomScalingFactor = function(){ return Math.round(Math.random()*100)};

/*Test data for the graphing functions*/ 
// var barChartData = {
		// labels : ["0h","1h","2h","3h","4h","5h","6h","7h","8h","9h","10h","11h","12h"],
		// datasets : [
			// {
				// fillColor : "rgba(220,0,220,0.7)",
				// strokeColor : "rgba(200,0,220,0.8)",
				// highlightFill: "rgba(240,0,220,0.75)",
				// highlightStroke: "rgba(255,220,210,1)",
				// data : [randomScalingFactor(),randomScalingFactor(),randomScalingFactor(),randomScalingFactor(),randomScalingFactor(),randomScalingFactor(),randomScalingFactor(),
				        // randomScalingFactor(),randomScalingFactor(),randomScalingFactor(),randomScalingFactor(),randomScalingFactor(),randomScalingFactor(),randomScalingFactor()]
			// },

		// ]

	// }
/*Set some tet over graph area*/
window.onload = function(){
	// var ctx = document.getElementById("canvas").getContext("2d");
	// window.myBar = new Chart(ctx).Line(barChartData, {
	// responsive : true
	// });
	document.getElementById("debug2").innerHTML="Graph Area";
}

/*This will update the selected device's information once in a minute*/	
window.setInterval(deviceInfoUpdate, 60000);

/*Funtion definition for AJAX call for device info update*/	
function deviceInfoUpdate(){

  if (window.XMLHttpRequest) {
    /*for IE7+, Firefox, Chrome, Opera, Safari*/
    xmlhttp=new XMLHttpRequest();
  } else { 
	/*for IE6, IE5*/
    xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
  }
  
  xmlhttp.onreadystatechange=function() {
	/*when response is received we check for the availability*/
    if (xmlhttp.readyState==4 && xmlhttp.status==200) {
      
	  /*This function implements the required data processing*/
	  updateDashBoard(xmlhttp.responseText);

    }
  }
  
  /*Sending GET request to update.php on server*/
  xmlhttp.open("GET","update.php?dev=" + selectedDevID,true);
  xmlhttp.send();


}	

/*This function will process the comma separated values received from update.php*/	
function updateDashBoard(response) {

	var i;
	var resultArray = response.split(",");
	var length = resultArray.length;

	document.getElementById("debug1").innerHTML=response;
	
	/*Check the type of response and process accordingly*/
	if(resultArray[1] =="full"){
		
		/*enable charting only if at least 12 hour data is available*/
		chartStatus = true;
		
		document.getElementById("2").innerHTML = resultArray[6]; //Temp
		document.getElementById("4").innerHTML = resultArray[5]; //Pressure
		document.getElementById("6").innerHTML = resultArray[7]; //Humidity
		document.getElementById("8").innerHTML = getCoStatus(resultArray[8]); //CO
		document.getElementById("10").innerHTML = getAirqStatus(resultArray[9]); //Airq
		document.getElementById("12").innerHTML = resultArray[10]; //Dust
		document.getElementById("14").innerHTML = resultArray[11]; //CO2
		document.getElementById("16").innerHTML = "N/A"; //O2
	
		for (i = 0; i < 12 ; i++){
			
			/*dataTable{type][hour]*/
			dataTable[0][i] = resultArray[(i*10 + 6)];
			dataTable[1][i] = resultArray[(i*10 + 5)];
			dataTable[2][i] = resultArray[(i*10 + 7)];
			dataTable[3][i] = resultArray[(i*10 + 8)];
			dataTable[4][i] = resultArray[(i*10 + 9)];
			dataTable[5][i] = resultArray[(i*10 + 10)];
			dataTable[6][i] = resultArray[(i*10 + 11)];
			
		}
	
	}else if(resultArray[1] =="last"){ 
	
		chartStatus = false;
		
		document.getElementById("2").innerHTML = resultArray[6]; //Temp
		document.getElementById("4").innerHTML = resultArray[5]; //Pressure
		document.getElementById("6").innerHTML = resultArray[7]; //Humidity
		document.getElementById("8").innerHTML = getCoStatus(resultArray[8]); //CO
		document.getElementById("10").innerHTML = getAirqStatus(resultArray[9]); //Airq
		document.getElementById("12").innerHTML = resultArray[10]; //Dust
		document.getElementById("14").innerHTML = resultArray[11]; //CO2
		document.getElementById("16").innerHTML = "N/A"; //O2
	
	}else{
	
		chartStatus = false;
	
	}

	displayTmpGraph();
}


/*Auillary function to understand the raw values of the sensors*/	
function getCoStatus(strValue){

	var value = parseInt(strValue);
	
	if(value > 5 && value < 100){
		return "V.Low";
	}else if(value > 100 && value < 200){
		return "Modest";
	}else if(value > 200 && value < 300){
		return "High";
	}else if(value > 300 && value < 500){
		return "V.High";
	}else {
		return "Fatal";
	}

}

/*Auillary function to understand the raw values of the sensors*/
function getAirqStatus(strValue){

	var value = parseInt(strValue);
	
	if(value > 0 && value < 50){
		return "Fresh";
	}else if(value > 50 && value < 100){
		return "Good";
	}else if(value > 100 && value < 200){
		return "Avg";
	}else if(value > 300 && value < 500){
		return "Bad";
	}else {
		return "V.Bad";
	}

}

/*This function called at the page load where it sends the request to the devices.php
  to fetch the eisting device information with its IDs*/
function updateDevices(map) {

  if (window.XMLHttpRequest) {
    /*for IE7+, Firefox, Chrome, Opera, Safari*/
    xmlhttp=new XMLHttpRequest();
  } else {  
    /*for IE6, IE5*/
    xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
  }
  
  xmlhttp.onreadystatechange=function() {
    if (xmlhttp.readyState==4 && xmlhttp.status==200) {
      
		Test(xmlhttp.responseText,map);

    }
  }
  
  xmlhttp.open("GET","devices.php",true);
  xmlhttp.send();
}

/*Process the response from devices.php*/
function Test(txt,map) {

	var i;
	var resultArray = txt.split(",");
	var length = resultArray.length;
	/*8 for each data set, 96 data for 12hr, 3 for each device, 1 for no of devices*/
	var marker,tip;

	var noOfMarkers = parseInt(resultArray[0]);
	
	for (i = 0; i < noOfMarkers; i++) {  
	
		deviceMarkerPositions[i] = new google.maps.LatLng(resultArray[(3*i)+3],resultArray[(3*i)+2]);

		marker = new google.maps.Marker({position:deviceMarkerPositions[i],map: map,icon:'img/pins.png'});

		tip = new google.maps.InfoWindow({content:"Temperature"});
		
		google.maps.event.addListener(marker, 'click', (function(marker, i) {
		
         return function() {
			var content = "Device" + resultArray[(3*i)+1].toString();
             tip.setContent(content);
             tip.open(map, marker);
			 selectedDevID = parseInt(resultArray[(3*i)+1]);
			 // if (marker.getAnimation() !== null) {
				// marker.setAnimation(null);
			// } else {
				// marker.setAnimation(google.maps.Animation.BOUNCE);
			// }
			 deviceInfoUpdate();
			 displayTmpGraph();

         }
		})(marker, i));
	
	}
	document.getElementById("debug1").innerHTML=txt;
	/*We know the devices available, update the information for defult device 1*/
	deviceInfoUpdate();

} 

function displayTmpGraph(){

	if(chartStatus){
	
		
		document.getElementById("debug2").innerHTML="Temperature C";
		var temperatureChartData = {
				labels : ["1h","2h","3h","4h","5h","6h","7h","8h","9h","10h","11h","12h"],
				datasets : [
				{
					fillColor : "rgba(40,0,220,0.7)",
					strokeColor : "rgba(20,60,220,0.8)",
					highlightFill: "rgba(60,0,220,0.75)",
					highlightStroke: "rgba(255,220,210,1)",
					data : [parseInt(dataTable[0][0]),parseInt(dataTable[0][1]),parseInt(dataTable[0][2]),parseInt(dataTable[0][3]),
							parseInt(dataTable[0][4]),parseInt(dataTable[0][5]),parseInt(dataTable[0][6]),parseInt(dataTable[0][7]),
							parseInt(dataTable[0][8]),parseInt(dataTable[0][9]),parseInt(dataTable[0][10]),parseInt(dataTable[0][11])]
				},

			]
		}

		var canvs = document.getElementById("canvas").getContext("2d");

			window.myBar = new Chart(canvs).Line(temperatureChartData, {
				responsive : true
		});
	
	}
	
}

function displayPressureGraph(){

	if(chartStatus){
	
		
		document.getElementById("debug2").innerHTML="Pressure kPa";
		var temperatureChartData = {
				labels : ["1h","2h","3h","4h","5h","6h","7h","8h","9h","10h","11h","12h"],
				datasets : [
				{
					fillColor : "rgba(40,245,32,0.7)",
					strokeColor : "rgba(200,245,32,0.8)",
					highlightFill: "rgba(60,0,220,0.75)",
					highlightStroke: "rgba(255,220,210,1)",
					data : [parseInt(dataTable[1][0]),parseInt(dataTable[1][1]),parseInt(dataTable[1][2]),parseInt(dataTable[1][3]),
							parseInt(dataTable[1][4]),parseInt(dataTable[1][5]),parseInt(dataTable[1][6]),parseInt(dataTable[1][7]),
							parseInt(dataTable[1][8]),parseInt(dataTable[1][9]),parseInt(dataTable[1][10]),parseInt(dataTable[1][11])]
				},

			]
		}

		var canvs = document.getElementById("canvas").getContext("2d");

			window.myBar = new Chart(canvs).Line(temperatureChartData, {
				responsive : true
		});
	
	}
	
}

function displayHumidityGraph(){

	if(chartStatus){

		
		document.getElementById("debug2").innerHTML="Humidity %";
		var temperatureChartData = {
				labels : ["1h","2h","3h","4h","5h","6h","7h","8h","9h","10h","11h","12h"],
				datasets : [
				{
					fillColor : "rgba(222,222,220,0.7)",
					strokeColor : "rgba(255,255,255,0.8)",
					highlightFill: "rgba(60,0,220,0.75)",
					highlightStroke: "rgba(255,220,210,1)",
					data : [parseFloat(dataTable[2][0]),parseFloat(dataTable[2][1]),parseFloat(dataTable[2][2]),parseFloat(dataTable[2][3]),
							parseFloat(dataTable[2][4]),parseFloat(dataTable[2][5]),parseFloat(dataTable[2][6]),parseFloat(dataTable[2][7]),
							parseFloat(dataTable[2][8]),parseFloat(dataTable[2][9]),parseFloat(dataTable[2][10]),parseFloat(dataTable[2][11])]
				},

			]
		}

		var canvs = document.getElementById("canvas").getContext("2d");

			window.myBar = new Chart(canvs).Line(temperatureChartData, {
				responsive : true
		});
	
	}
	
}

function displayCoGraph(){

	if(chartStatus){

		
		document.getElementById("debug2").innerHTML="CO Concentration";
		var temperatureChartData = {
				labels : ["1h","2h","3h","4h","5h","6h","7h","8h","9h","10h","11h","12h"],
				datasets : [
				{
					fillColor : "rgba(222,0,0,0.7)",
					strokeColor : "rgba(255,0,0,0.8)",
					highlightFill: "rgba(60,0,220,0.75)",
					highlightStroke: "rgba(255,220,210,1)",
					data : [parseInt(dataTable[3][0]),parseInt(dataTable[3][1]),parseInt(dataTable[3][2]),parseInt(dataTable[3][3]),
							parseInt(dataTable[3][4]),parseInt(dataTable[3][5]),parseInt(dataTable[3][6]),parseInt(dataTable[3][7]),
							parseInt(dataTable[3][8]),parseInt(dataTable[3][9]),parseInt(dataTable[3][10]),parseInt(dataTable[3][11])]
				},

			]
		}

		var canvs = document.getElementById("canvas").getContext("2d");

			window.myBar = new Chart(canvs).Line(temperatureChartData, {
				responsive : true
		});
	
	}
	
}

function displayAirqGraph(){

	if(chartStatus){

		
		
		document.getElementById("debug2").innerHTML="Overall Quality";
		var temperatureChartData = {
				labels : ["1h","2h","3h","4h","5h","6h","7h","8h","9h","10h","11h","12h"],
				datasets : [
				{
					fillColor : "rgba(222,222,0,0.7)",
					strokeColor : "rgba(255,255,0,0.8)",
					highlightFill: "rgba(60,0,220,0.75)",
					highlightStroke: "rgba(255,220,210,1)",
					data : [parseInt(dataTable[4][0]),parseInt(dataTable[4][1]),parseInt(dataTable[4][2]),parseInt(dataTable[4][3]),
							parseInt(dataTable[4][4]),parseInt(dataTable[4][5]),parseInt(dataTable[4][6]),parseInt(dataTable[4][7]),
							parseInt(dataTable[4][8]),parseInt(dataTable[4][9]),parseInt(dataTable[4][10]),parseInt(dataTable[4][11])]
						
				},

			]
		}

		var canvs = document.getElementById("canvas").getContext("2d");

			window.myBar = new Chart(canvs).Line(temperatureChartData, {
				responsive : true
		});

	}
	
}

function displayDate(){

}

function clearCanvas(context, canvas) {
  context.clearRect(0, 0, canvas.width, canvas.height);
  var w = canvas.width;
  canvas.width = 1;
  canvas.width = w;
}
