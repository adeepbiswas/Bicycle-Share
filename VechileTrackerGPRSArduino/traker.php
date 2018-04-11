<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Vechile Tracker</title>
    <style>
      /* Always set the map height explicitly to define the size of the div
       * element that contains the map. */
      #map {
        height: 100%;
      }
      /* Optional: Makes the sample page fill the window. */
      html, body {
        height: 100%;
        margin: 0;
        padding: 0;
      }
    </style>
    <script src="https://code.jquery.com/jquery-1.9.1.min.js"></script>
  </head>
  <body>
    <div id="map"></div>
    <script>

      // The following example creates a marker in Stockholm, Sweden using a DROP
      // animation. Clicking on the marker will toggle the animation between a BOUNCE
      // animation and no animation.

      var marker;
      var map;

      function initMap() {
          map = new google.maps.Map(document.getElementById('map'), {
              zoom: 13,
              center: {lat: 59.325, lng: 18.070}
          });
          
          marker = new google.maps.Marker({
              map: map,
              draggable: true,
              animation: google.maps.Animation.DROP,
              position: {lat: 59.327, lng: 18.067}
          });
          
          var loc = new google.maps.LatLng(marker.position.lat(), marker.position.lng());
          marker.addListener('click', toggleBounce);
      }

      function toggleBounce() {
        if (marker.getAnimation() !== null) {
          marker.setAnimation(null);
        } else {
          marker.setAnimation(google.maps.Animation.BOUNCE);
        }
      }
    $( document ).ready(function() {
        console.log( "document loaded" );
    });
    
    function changeMarkerPosition() {
        var xmlhttp = new XMLHttpRequest();
        xmlhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                var myObj = JSON.parse(this.responseText);
                var latlng = new google.maps.LatLng(myObj.lat, myObj.lag);
                console.log(latlng);
                marker.setPosition(latlng);                
            }
        };
        
        xmlhttp.open("GET", "sensor.php?json", true);
        xmlhttp.send(); 
    }
    
    $( window ).on( "load", function() {
        setInterval(changeMarkerPosition, 5000);
    });
    </script>        

    <script async defer
    src="https://maps.googleapis.com/maps/api/js?key=AIzaSyBeG8RvAXZQzDDh2PPj3VwIMIvmlyYutas&callback=initMap">
    </script>
  </body>
</html>