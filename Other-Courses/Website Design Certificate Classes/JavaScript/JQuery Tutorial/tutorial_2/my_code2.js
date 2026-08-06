/* ID/CLASS SELECTOR */
/*
     Selects the element whose ID attribute matches the specified name. 
     The specified name is preceded by a #. Example: "#third" - Selects 
     the element that has an ID attribute value of third.

     Select the elements whose class attribute matches the specified name. 
     The specified name is preceded by a period. Example: ".multiple" - Selects 
     all the element that have class attribute values of multiple.
*/
$(document).ready(function() {
     $("#testbutton").click(function() {
          $("#third").css("background-color","red");	
          // $(".multiple").css("background-color","red");	
     });
});




/* ELEMENT WITH CLASS SELECTOR */
/*
     Select elements by the combination of tag name and class attribute. 
     Specify the tag name, followed by a period, followed by a class name. 
     Example: "strong.multiple" - Selects all <strong> elements that have 
     class attribute values of multiple.
*/
$(document).ready(function() {
     $("#testbutton").click(function() {
          $("strong.multiple").css("background-color","red");	
     });
});




/* MULTIPLE SELECTOR FOR THE CLICK EVENT */
/*
     The click event is using an ID selector and an element selector by 
     specifying "#testbutton, strong" When either the Test Button, or a 
     <strong> element is clicked, the background color of the <strong> 
     element on the second line will turn red.
*/
$(document).ready(function() {
     // two selectors
     $("#testbutton, strong").click(function() {
          $("strong.multiple").css("background-color","red");	
     });
});




/* THIS KEYWORD SELECTOR */
/* 
     The element that caused the click function to be executed is specified 
     by using the keyword this, without quote marks. Clicking on the Test Button, 
     or any of the <strong> elements, will cause the clicked element's background 
     color to turn red.
*/
$(document).ready(function() {
     $("#testbutton, strong").click(function() {
          $(this).css("background-color","red");	
     });
});
