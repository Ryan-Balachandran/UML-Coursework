/* REMOVECLASS() & ADDCLASS() */
/*
     removeClass() and addClass() can be used together. 
     Example: $(this).removeClass("emphasis").addClass("shrink"); 
     - Click the first <h1> element to remove its emphasis class and add the shrink class.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $(this).removeClass("emphasis").addClass("shrink");
     });
});




/* TOGGLECLASS SINGLE/MULTIPLE CLASS*/
/*
     Alternately removes and adds a class. 
     Example: toggleClass("emphasis") 
     - Repeatedly click an <h1> element to toggle the emphasis class.

     Alternately removes and adds multiple classes. 
     Example: toggleClass("shrink emphasis") 
     - Repeatedly click an <h1> element to toggle the shrink and emphasis classes.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $(this).toggleClass("emphasis");
     });
});

$(document).ready(function() {
     $("h1").click(function() {
          $(this).toggleClass("shrink emphasis");
     });
});




/* TOGGLECLASS() */
/*
     Alternately removes and adds currently used classes. 
     Example: toggleClass() 
     - Repeatedly click the first <h1> element to toggle its emphasis class.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $(this).toggleClass();
     });
});
