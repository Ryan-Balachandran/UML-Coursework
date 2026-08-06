/* HIDE() EFFECT */
/* 
     Hides the elements by changing the height, width, and opacity. 
     Example: $("h2").hide(1000) - Click on the top heading element 
     to hide the <h2> element over a period of 1 second.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("h2").hide(1000);
     });
});




/* SHOW() EFFECT */
/*
     Shows the elements by changing the height, width, and opacity. 
     Example: $("h2").show(1000) - Click on the top heading element 
     to show the <h2> element over a period of 1 second.
*/
$(document).ready(function() {
     $("h2").hide();
     
     $("h1").click(function() {
          $("h2").show(1000);
     });
});




/* TOGGLE() EFFECT */
/*
     Alternately shows or hides the elements by changing the height, width, and opacity.
     Example: $("h2").toggle(1000) - Click on the top heading element to alternately show
     or hide the <h2> element over a period of 1 second.
*/
$(document).ready(function() {
     $("h2").hide();
     
     $("h1").click(function() {
       $("h2").toggle(1000);
     });
   });




/* SLIDEUP()/SLIDEDOWN() EFFECT */
/*
     Hides the elements by changing the height.
     Example: $("h2").slideUp(1000) - Click on the top heading element to 
     hide the <h2> element over a period of 1 second.

     Shows the elements by changing the height. 
     Example: $("h2").slideDown(1000) - Click on the top heading element to 
     show the <h2> element over a period of 1 second.
*/
$(document).ready(function() {
     //$("h2").hide();
     
     $("h1").click(function() {
          $("h2").slideUp(1000);
     });
});

$(document).ready(function() {
     $("h2").hide();
     
     $("h1").click(function() {
          $("h2").slideDown(1000);
     });
});




/* SLIDETOGGLE() EFFECT */
/*
     Alternately shows or hides the elements by changing the height. 
     Example: $("h2").slideToggle(1000) - Click on the top heading 
     element to alternately show or hide the <h2> element over a period of 1 second.
*/
$(document).ready(function() {
     $("h2").hide();
     
     $("h1").click(function() {
          $("h2").slideToggle(1000);
     });
});




/* FADEOUT()/FADEIN() EFFECT */
/*
     Hides the elements by changing the opacity. 
     Example: $("h2").fadeOut(1000) - Click on the top heading element 
     to hide the <h2> element over a period of 1 second.

     Shows the elements by changing the opacity. 
     Example: $("h2").fadeIn(1000) - Click on the top heading element 
     to show the <h2> element over a period of 1 second.
*/
$(document).ready(function() {
     //$("h2").hide();
     
     $("h1").click(function() {
          $("h2").fadeOut(1000);
     });
});

   $(document).ready(function() {
     $("h2").hide();
     
     $("h1").click(function() {
          $("h2").fadeIn(1000);
     });
});




/* FADETOGGLE() EFFECT */
/*
     Alternately shows or hides the elements by changing the opacity. 
     Example: $("h2").fadeToggle(1000) - Click on the top heading element 
     to alternately show or hide the <h2> element over a period of 1 second.
*/
$(document).ready(function() {
     $("h2").hide();
     
     $("h1").click(function() {
          $("h2").fadeToggle(1000);
     });
});




/* FADETO() EFFECT */
/*
     Changes the opacity until the specified opacity is reached. 
     Example: $("h2").fadeTo(1000, 0.3) - Click on the top heading
     element to change the opacity of the <h2> element to 30% over a period of 1 second.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("h2").fadeTo(1000, 0.3);
     });
});




/* DELAY() EFFECT */
/*
     Delays the effect that follows it. 
     Example: $("h2").delay(2000).fadeToggle(1000) - Click on the top heading element 
     to alternately show or hide the <h2> element, over a period of 1 second, 
     after a delay of 2 seconds.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("h2").delay(2000).fadeToggle(1000);
     });
});




/* CALLBACK FUNCTION */
/*
     The callback function, passed as the second argument to the effect method, 
     will be executed at the completion of the effect. Example: $("h2").hide(1000, 
     function() {$("h3").fadeOut(1000);}); - Click on the top heading element 
     to hide the <h2> element, over a period of 1 second. After the <h2> finishes hiding, 
     the <h3> element will fade out over a period of 1 second.
*/
$(document).ready(function() {
     $("h1").click(function() {
          $("h2").hide(1000, function() {
               $("h3").fadeOut(1000);
          });
     });
});