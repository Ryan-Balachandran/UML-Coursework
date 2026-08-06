"use strict";

// define an array with html file names
let htmlAddresses = [
    ["pcHardware.html"],
    ["linuxOS.html"],
    ["audioInterfaces.html"],
    ["midiControllers.html"],
    ["hardwarePeripherals.html"],
    ["recordingSoftware.html"],
    ["softInstruments.html"],
    ["sound.html"],
    ["newsletterSignup.html"],
    ["functionalityList.html"],
    ["index.html"]];

// define an array with javascript file names
let extFiles = [
    ["navMenu.js"],
    ["studio.js"],
    ["functionality.js"],
    ["pages.js"],
    ["newsletterSumbit.js"],
    ["head.js"]
]

// define variables that contain messages to be displayed in the overlay
let tutorial1_externalFiles = `Each page on this site uses references to external files. None of the HTML pages use inline styling or scripting.
                                You'll find numerous Javascript and CSS files. Some are used on each page.
                                Others are included as additions to a particular page. All the script tags on this site use the defer attribute.`;

let tutorial1_eventHandlers = `There are many event handlers throughout this site. Most of the pages display information about various topics. Each topic
                                uses a 'click' event handler that runs code to show or hide information about each topic. This functionality page also uses
                                click events from the HTML code to call the function that creates this animated overlay.`;

let tutorial2_regularFunctions = `There are many functions throughout this site. The navigation menu that appears on each page is created by the 
                                makeMenu function and is probably the most interesting on this site. Before the function is called, an array is created 
                                that contains relevant information about each item. Then it uses this information and a loop to create the HTML code and 
                                onmouseover event handlers for each link. It also performs a check to ensure that a link to the current page does not 
                                appear in the menu.`;

let tutorial2_evalFunction = `As you roll over each item in the navigation menu on the main page, you'll notice that the picture above changes. When the navigation menu is
                                created, each item is given an id. When a user hovers over a navigation link, the onmouseover event handler calls a function 
                                called 'whichPic' that receives the id and uses the 'eval' function to make the id name usable as a variable that can be
                                used to reference the respective variable containing a file name to a particular picture. 'Eval' is also used to call the
                                functions that create the animations on this page. A random number is generated and appended to the end of a function
                                name, which is called to make the animation`;

let tutorial3_switch = `As you roll over each item in the navigation menu, you'll notice that the text next to the picture above changes. When the 
                        navigation menu is created, each item is given an id. When a user hovers over a navigation link, the onmouseover event handler 
                        calls a function called 'whichMsg' that receives the id and uses it as the expression in a switch statement to choose the respective 
                        message.`;

let tutorial3_array = `The navigation menu uses an array called 'items' and a loop to populate the menu. The array contains three pieces of information for
                        each item; the page title, the page address, and the page id`;

let tutorial3_forLoop = `A for loop is used to create the navigation menu. The loop iterates through an array containing information about the links to be
                        contained in the menu and creates HTML code for each of those links. A for loop is also used to populate the light box seen on each
                        page.`;

let tutorial3_conditionalIfElse = `A conditional if/else statement is used during the creation of the navigation menu to determine whether or not to
                                    include the onmouseover events that are resposible for changing the picture and message on the home page, 'studio.html'
                                    If the menu is being created for the homepage, we want the pictures and messages. If it's being created for any other
                                    page, then the pictures and message are not to be diplayed.`;

let tutorial4_useStrict = `All the javascript code on this site executes in strict mode to reduce processing time and to promote well written code.`;

let tutorial4_exceptionHandler = `An exception handler is used during the creation of the navigation menu to check that all there are an equal number of page
                            titles, page addresses, and page id's. If any information has mistakenly been omitted, the site will not function properly. This 
                            check is useful for the person maintaining the page, should they make a coding mistake to the navigation menu.`;

let tutorial5_location = `The 'location' object is used on the newsletter sign up page when a user closes the confimration overlay that opens upon clicking 
                            the 'nevermind' button on the sign up form.`;

let tutorial5_nodes = `An overlay is used on this page to display each functionality message. When an item on this page is clicked, an onclick event 
                        calls a function called 'createOverlay' that creates the elements and uses nodes to append and remove them. This function receives 
                        three pieces of information; the message to be displayed and height/width values to create a custom size box to contain the message.`;

let tutorial5_timedCommand = `A timed command is used on the main page to generate another image every 3 seconds`;

let tutorial6_formValidation = `The newsletter sign up page contains a form where some of the information entered by the user, is validated. Signing
                                up for the newsletter requires the user enter a first name, a last name, and a valid email address. If any of the required
                                fields are not filled out, a custom message is displayed.`;

let tutorial6_formReset = `The newsletter sign up page contains a form with a nevermind button. If the user decides they do not wish to finish filling
                            out the form, they can click the nevermind button. Upon clicking the button, any information entered by the user is erased and
                            a confirmation message is displayed.`;

let tutorial7_regex = `The form on the newsletter sign up page performs validation when the user clicks the submit button. The email address is validated 
                        by using the 'test()' method with a pattern that is assigned to a variable.`;

let tutorial7_random = `The large image in the middle of the home page is chosen randomly from a pool of fifteen different images each time the page is loaded. 
                        Each file has a name of #.jpg. A random number is chosen and then concatenated to the .jpg file extension. The filename that is
                        generated, is used as the source in the image tag.`;

let tutorial8_customObj = `The navigation menu uses an object called menu() to create its content. Its constructor takes three pieces of information;
                            the page title, the page address, and the page id. An instance of the menu object is created, called newMenu and it contains
                            each page title, with its corresponding html address and its id. This site was originally designed with the data for the menu items 
                            stored in a 2D/jagged array. The array is still in use, but now it is populated using properties from the menu object instead.
                            As did the original array, the menu object is a centralized place to easily add/remove menu items. Anytime a page is added to the site, 
                            all that needs to be done is to add the relevant pieces of information to the arrays containing the menu item information. Removing items 
                            is just as easy.`

let tutorial8_dotOper = `The array that stores the data for the navigation menu is called 'items', and is populated using the properties from the custom menu object. 
                        These properties are .title, .address, & .id. A loop iterates through the entries in the menu object and assigns the value of each property 
                        to its corresponding place in the 'items' array.`;

let tutorial12_animation = `This page uses five different animations to display the overlay message on the screen. Each time a link is clicked, a random number 
                            is generated and used with 'eval' to call the corresponding function.`;

let tutorial12_attsCSS = `Most of the pages on this site have discussion topics, which open and close to reveal or hide information related to the topic.
                            To accomplish this, the 'toggleclass()' and 'hasclass()' methods are used.`;

// function that creates an overlay to display a functionality message from above 
function createOverlay(caption,h,w,page) {
    let parent = document.getElementById("functionality");
    let child = document.getElementById("messageOverlay");

    // if the previous overlay is still being displayed, remove it
    if (parent.contains(child)) {
        document.body.removeChild(child);
    };

    let overlay = document.createElement("div");
    overlay.id = "messageOverlay";
    overlay.className = "msgBox";
    overlay.style.height=h+"px";
    overlay.style.width=w+"px";

    // add the figure box to the overlay
    let figureBox = document.createElement("figure");
    overlay.appendChild(figureBox);

    // add the caption to the figure box
    let overlayCaption = document.createElement("figcaption");
    overlayCaption.textContent = caption;
    figureBox.appendChild(overlayCaption);

    // add the link to the figure box
    let overlayLink = document.createElement("a");
    overlayLink.href = page;
    overlayLink.target = "_blank";
    overlayLink.textContent = "Check It Out";
    figureBox.appendChild(overlayLink);

    // add a close button to the overlay
    let closeBox = document.createElement("div");
    closeBox.id = "messageOverlayClose";
    closeBox.innerHTML = "&times;";
    closeBox.onclick = function() {
        document.body.removeChild(overlay);
    }
    overlay.appendChild(closeBox);

    // choose a random number and use it to select one of the animation functions
    let randomNumber = Math.floor(1+5*Math.random());
    let whichAnimation = "animation" +randomNumber;
    eval(whichAnimation+"()");

    // functions that  create the animations for displaying the message overlay
    function animation1() {
        $( () => {
            $(overlay).css({
                opacity: 0,
                height: h+"px",
                width: 0,
                borderRadius: 50+"%",
                top: 0,
                left: 0,
                marginTop: 0+"px",
                marginLeft: 0+"px",
                display: "", /**/
                borderRadius: "0px"/**/   
            })
        })
        
        document.body.appendChild(overlay);

        $( () => {
            $(overlay).animate({
                opacity: 1,
                height: h+"px",
                width: w+"px",
                borderRadius: "25px",
                top: 50+"%",
                left: 50+"%",
                marginTop: "-"+h/2+"px",
                marginLeft: "-"+w/2+"px",
            }, 1000)
        })        
    }

    function animation2() {
        $( () => {
            $(overlay).css({
                opacity: 0,
                height: h+"px",
                width: 0,
                borderRadius: 50+"%",
                top: -100+"%",
                right: -100+"%",
                marginTop: 0+"px",
                marginLeft: 0+"px",
                display: "", /**/
                borderRadius: "0px"/**/   
            })
        })
        
        document.body.appendChild(overlay);

        $( () => {
            $(overlay).animate({
                opacity: 1,
                height: h+"px",
                width: w+"px",
                borderRadius: "25px",
                top: 50+"%",
                left: 50+"%",
                marginTop: "-"+h/2+"px",
                marginLeft: "-"+w/2+"px",
            }, 1000)
        })        
    }

    function animation3() {
        $( () => {
            $(overlay).css({
                opacity: 0,
                height: 10+"px",
                width: 10+"px",
                borderRadius: 50+"%",
                top: 0+"%",
                right: 0+"%",
                marginTop: 0+"px",
                marginLeft: 0+"px",
                display: "", /**/
                borderRadius: "0px"/**/   
            })
        })
        
        document.body.appendChild(overlay);

        $( () => {
            $(overlay).animate({
                opacity: 1,
                height: 10+"px",
                width: 10+"px", /*w+"%",*/
                borderRadius: "25px",
                top: 50+"%",
                left: 50+"%",
                marginTop: "-"+h/2+"px",
                marginLeft: "-"+w/2+"px",
            }, 1500)
        })        

        $( () => {
            $(overlay).animate({
                opacity: 1,
                height: h+"px",
                width: w+"px", /*w+"%",*/
                borderRadius: "25px",
                top: 50+"%",
                left: 50+"%",
                marginTop: "-"+h/2+"px",
                marginLeft: "-"+w/2+"px",
            }, 1000)
        })        
    }

    function animation4() {
        $( () => {
            $(overlay).css({
                opacity: 0,
                height: 10+"px",
                width: 10+"px",
                borderRadius: 50+"%",
                bottom: 0+"%",
                left: 50+"%",
                marginTop: 0+"px",
                marginLeft: 0+"px",
                display: "", /**/
                borderRadius: "0px"/**/   
            })
        })
        
        document.body.appendChild(overlay);

        $( () => {
            $(overlay).animate({
                opacity: 1,
                height: 10+"px",
                width: 10+"px", /*w+"%",*/
                borderRadius: "25px",
                top: 50+"%",
                left: 50+"%",
                /*marginTop: "-"+h/2+"%",
                marginLeft: "-"+w/2+"%",*/
            }, 1500)
        })        

        $( () => {
            $(overlay).animate({
                opacity: 1,
                height: h+"px",
                /*width: w+"%", /*w+"%",*/
                borderRadius: "25px",
                top: 50+"%",
                left: 50+"%",
                marginTop: "-"+h/2+"px",
                marginLeft: "-"+w/2+"px",
            }, 1000)
        })        

        $( () => {
            $(overlay).animate({
                opacity: 1,
                height: h+"px",
                width: w+"px", /*w+"%",*/
                borderRadius: "25px",
                top: 50+"%",
                left: 50+"%",
                marginTop: "-"+h/2+"px",
                marginLeft: "-"+w/2+"px",
            }, 1000)
        })        

    }

    function animation5() {
        $( () => {
            $(overlay).css({
                opacity: 0,
                height: 10+"px",
                width: 10+"px",
                borderRadius: 50+"%",
                top: -100+"%",
                left: 50+"%",
                marginTop: 0+"px",
                marginLeft: 0+"px",
                display: "", /**/
                borderRadius: "0px"/**/   
            })
        })
        
        document.body.appendChild(overlay);

        $( () => {
            $(overlay).animate({
                opacity: 1,
                height: 10+"px",
                width: 10+"px", /*w+"%",*/
                borderRadius: "25px",
                top: 25+"%",
                left: 50+"%",
                /*marginTop: "-"+h/2+"%",
                marginLeft: "-"+w/2+"%",*/
            }, 1500)
        })        

        $( () => {
            $(overlay).animate({
                opacity: 1,
                height: h+"px",
                /*width: w+"%", /*w+"%",*/
                borderRadius: "25px",
                top: 25+"%",
                left: 50+"%",
                /*marginTop: "-"+h/2+"%",
                marginLeft: "-"+w/2+"%",*/
            }, 1000)
        })        

        $( () => {
            $(overlay).animate({
                opacity: 1,
                height: h+"px",
                width: w+"px", /*w+"%",*/
                borderRadius: "25px",
                top: 50+"%",
                left: 50+"%",
                marginTop: "-"+h/2+"px",
                marginLeft: "-"+w/2+"px",
            }, 1000)
        })        

    }

}