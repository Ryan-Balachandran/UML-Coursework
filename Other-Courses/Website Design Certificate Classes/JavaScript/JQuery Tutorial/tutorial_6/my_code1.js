/* CSS() MARGIN-LEFT */
/*
     Sets the margin-left property. Example: css("margin-left", "50px") 
     - Move the mouse over the <h1> elements to set the margin-left property.
*/
$(document).ready(function() {
     $("h1").mouseenter(function() {
          $(this).css("margin-left", "50px");
     });
});




/* CSS()  INCREMENTING MARGIN-LEFT PROPERTY */
/*
    Sets the margin-left property. Example: css("margin-left", "50px") 
    - Move the mouse over the <h1> elements to set the margin-left property.
*/
$(document).ready(function() {
     $("h1").mouseenter(function() {
          $(this).css("margin-left", "50px");
     });
});




/* CSS() MULTIPLE PROPERTIES */
/*
     Increments the margin-left property and sets the background-color property. 
     Example: {"margin-left": "+=50px", "background-color": "red"} 
     - Move the mouse over the <h1> elements to set the properties.
*/
$(document).ready(function() {
     $("h1").mouseenter(function() {
          $(this).css({
               "margin-left": "+=50px",
               "background-color": "red"
          });
     });
});




/* ADDCLASS() SINGLE/MULTIPLE CLASS */
/*
     Adds a class to an HTML element. Example: addClass("emphasis") 
     - Click an <h1> element to add the emphasis class.

     Adds multiple classes to an HTML element. 
     Example: addClass("emphasis shrink") 
     - Click an <h1> element to add the emphasis and shrink classes.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $(this).addClass("emphasis");
     });
});

$(document).ready(function() {
     $("h1").click(function() {
          $(this).addClass("emphasis shrink");
     });
});
