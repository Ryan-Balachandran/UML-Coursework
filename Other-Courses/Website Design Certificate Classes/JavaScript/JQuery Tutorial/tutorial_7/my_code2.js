/* ATTR() CHANGE ATTRIBUTE */
/*
     Changes attribute values. 
     Example: attr("src", "floatingball.gif") 
     - Click on the heading text to change the image.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("#picture").attr("src", "floatingball.gif");
     });
});