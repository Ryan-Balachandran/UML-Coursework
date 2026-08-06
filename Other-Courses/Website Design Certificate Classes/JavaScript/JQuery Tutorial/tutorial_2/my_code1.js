/* ELEMENT SELECTOR */
// Select elements by tag name. Example: "div" - Selects all <div> elements.
$(document).ready(function() {
     $("#testbutton").click(function() {
          $("div").css("background-color","red");	
     });
});

// Select elements by tag name. Example: "p" - Selects all <p> elements.
$(document).ready(function() {
     $("#testbutton").click(function() {
          $("p").css("background-color","red");	
     });
});




/* MULTIPLE SELECTOR */
/* 
     Select multiple elements by separating selectors with comas. 
     Example: "div, strong, #testbutton" - Selects all <div> elements, 
     <strong> elements, and the <input> element (the Test button) 
     since its ID attribute is set to testbutton. 
*/
$(document).ready(function() {
     $("#testbutton").click(function() {
          $("div, strong, #testbutton").css("background-color","red");	
     });
});




/* ALL SELECTOR */

// Select all elements by using an asterisk. Example: "*" - Selects all elements.
$(document).ready(function() {
     $("#testbutton").click(function() {
          $("*").css("background-color","red");	
     });
});




/* CHILD SELECTOR */
/* 
     Selects a child element by using the following syntax. 
     "parent > child". Example: "div > p" - Selects all <p> elements 
     that are children of <div> elements. 
*/
$(document).ready(function() {
     $("#testbutton").click(function() {
          $("div > p").css("background-color","red");	
     });
});




/*  FIRST/LAST CHILD SELECTOR */
/*
     Selects first child elements by using the syntax :first-child. 
     Example: "div > p:first-child" - Selects all <p> elements that 
     are first children of <div> elements.

     Selects last child elements by using the syntax :last-child. 
     Example: "div > p:last-child" - Selects all <p> elements that 
     are last children of <div> elements.
*/
$(document).ready(function() {
     $("#testbutton").click(function() {
          $("div > p:first-child").css("background-color","red");	
          // $("div > p:last-child").css("background-color","red");	
     });
});




/* DESCENDANT SELECTOR */
/* 
     Selects a descendant element by using the following syntax. 
     "ancestor descendant". Example: "div strong" - Selects all 
     <strong> elements that are descendants of <div> elements.
*/
$(document).ready(function() {
     $("#testbutton").click(function() {
          $("div strong").css("background-color","red");	
     });
});




/* EVEN/ODD SELECTOR */
/*
     Selects matched elements based on their position. 
     Even positioned elements are selected using the following syntax. 
     :even. Example: "p:even" - Selects the first and third <p> elements.

     Selects matched elements based on their position. 
     Odd positioned elements are selected using the following syntax. 
     :odd. Example: "p:odd" - Selects the second and fourth <p> elements.
*/
$(document).ready(function() {
     $("#testbutton").click(function() {
          $("p:even").css("background-color","red");	
          // $("p:odd").css("background-color","red");	
     });
});
