/* ANIMATE() FONT SIZE */
/*
     Animates the font size. Example: "font-size": "3em" - Click on the 
     top heading element to change the <h2> element font size.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("h2").animate({
          "font-size": "3em"
          }, 1000);
     });
});




/* ANIMATE() WIDTH */
/*
     Animates the width. Example: "width": "50%" - Click on the top 
     heading element to change the <h2> element width.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("h2").animate({
               "font-size": "3em",
               "width": "50%"
          }, 1000);
     });
});




/* ANIMATE() LEFT PROPERTY */
/*
     Animates the left property. Animating the left property will
     have no effect if the element's position property is set to
     static. Example: "left": "100px" - Click on the top heading 
     element to change the <h2> element's left property.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("h2").animate({
               "font-size": "3em",
               "width": "50%",
               "left": "100px"
          }, 1000);
     });
});




/* ANIMATE() LEFT PROPERTY BY INCREMENTING */
/*
     Increments the left property each time the event is triggered. 
     Animating the left property will have no effect if the element's 
     position property is set to static. Example: "left": "+=100px" - 
     Click on the top heading element to increment the <h2> element's 
     left property. The left property will be incremented each time the 
     heading element is clicked.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("h2").animate({
               "font-size": "3em",
               "width": "50%",
               "left": "+=100px"
          }, 1000);
     });
});




/* ANIMATE() FONT USING "HIDE" VALUE */
/*
     Font size animation can use a value of "hide". 
     Example: "font-size": "hide" - Click on the top 
     heading element to hide the <h2> element by reducing its font size.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("h2").animate({
               "font-size": "hide",
               "width": "50%",
               "left": "+=100px"
          }, 1000);
     });
});




/* ANIMATE() FONT SIZE USING "TOGGLE" VALUE */
/*
     Font size animation can use a value of "toggle". 
     Example: "font-size": "toggle" - Click on the top 
     heading element to hide the <h2> element by reducing 
     its font size. Click again to show the <2> element by 
     increasing its font size.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("h2").animate({
               "font-size": "toggle",
               "width": "50%",
               "left": "+=100px"
          }, 1000);
     });
});




/* CALLBACK FUNCTION */
/*
     The callback function, passed as the third argument to the animate() method, 
     will be executed at the completion of the animation. 
     Example: $("h3").fadeOut(1000); - Click on the top heading element to 
     hide the <h2> element. After the <h2> animation finishes hiding,
     the <h3> element will fade out over a period of 1 second. Click again 
     to show the <2> element by increasing its font size.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("h2").animate({
               "font-size": "toggle",
               "width": "50%",
               "left": "+=100px"
          }, 1000, function() {
               $("h3").fadeOut(1000);
          });
     });
});