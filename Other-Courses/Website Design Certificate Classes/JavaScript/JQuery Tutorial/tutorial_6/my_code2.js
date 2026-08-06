/* REMOVECLASS() */
/*
     Removes all classes from the specified HTML element. 
     Example: removeClass() - Click the first <h1> element to remove all of its classes.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $(this).removeClass();
     });
});

/* REMOVECLASS() SINGLE/MULTIPLE CLASS */
/*
     Removes a class from the specified HTML element. 
     Example: removeClass("emphasis") - Click the first <h1> element to remove its emphasis class.

     Removes multiple classes from the specified HTML element. 
     Example: removeClass("shrink emphasis") - Click the first <h1> element 
     to remove its shrink and emphasis classes.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $(this).removeClass("emphasis");
     });
});

$(document).ready(function() {
     $("h1").click(function() {
          $(this).removeClass("shrink emphasis");
     });
});