"use strict";

// define array for main navigation menu
// 
// jagged array, 3 columns wide
// each row has a: page title, filename, id name
// the ID values specified in the third column of this array are used to reference variable names later using eval()

/* constructor function for menu items */
function menuItem(pageTitle, pageAddress, pageID) {
    this.title = pageTitle;
    this.address = pageAddress;
    this.id = pageID;
}

/* constructor function for the menu */
function theMenu() {
    let pages = ["PC Hardware", "Linux OS: Ubuntu Studio", "Audio Interfaces", "Midi Controllers", "Hardware Peripherals", "Recording Software", 
                "Virtual Instruments", "Sound", "Connections", "Newsletter Signup", "Functionality"];
    let addresses = ["pcHardware.html", "linuxOS.html", "audioInterfaces.html", "midiControllers.html", "hardwarePeripherals.html", "recordingSoftware.html",
                "softInstruments.html", "sound.html", "connections.html", "newsletterSignup.html", "functionalityList.html"];
    let ids = ["pc", "os", "ai", "midi", "hardPerf", "recording", "soft", "sound", "connections", "newsletter", "functionalityList"];
    this.menu = [];

    let p=pages.length;
    let a=addresses.length;
    let i=ids.length;

    // set up error handling that checks to be sure the arrays contain the same number of items
    try {
        if ((a!=p) || (a!=i)) throw "missing items";
    } catch(err) {
        alert(`There is information missing from the navigation menu.\n The sitemay not work properly.\n
        There are:
            ${p} page titles
            ${a} page addresss  
            ${i} page ids`);
    } finally {
        // add an item for each combination of page, address, and id
        for (let i=0;i<pages.length;i++) {
            this.menu.push(new menuItem(pages[i], addresses[i], ids[i]));
        }
    }
}

//var myMenu = new menuObj(); // create an instance of menu

let newMenu = new theMenu(); // create an instance of the menu
let numberOfItems = newMenu.menu.length;
let items = new Array(numberOfItems);

for (let i=0;i<numberOfItems;i++) {
    items[i]=new Array(3);
}

for (let i=0;i<numberOfItems;i++) {
    items[i][0]=newMenu.menu[i].title;
    items[i][1]=newMenu.menu[i].address;
    items[i][2]=newMenu.menu[i].id;
    console.log(newMenu.menu[i].title, newMenu.menu[i].address,newMenu.menu[i].id);
}

/*let items = [
    ["PC Hardware","pcHardware.html","pc"],
    ["Linux OS: Ubuntu Studio","linuxOS.html","os"],
    ["Audio Interfaces","audioInterfaces.html","ai"],
    ["Midi Controllers","midiControllers.html","midi"],
    ["Hardware Peripherals","hardwarePeripherals.html","hardPerf"],
    ["Recording Software","recordingSoftware.html","recording"],
    ["Virtual Instruments","softInstruments.html","soft"],
    ["Sound","sound.html","sound"],
    ["Connections","connections.html","connections"],
    //["Configuration","construction.html","configuration"],
    ["Newsletter Signup", "newsletterSignup.html", "newsletter"],
    ["Functionality","functionalityList.html","functionalityList"]];
*/

//function makeMenu(newMenu){
function makeMenu(newMenu){
    var menu = document.getElementById("theMenu");
    var docName = document.getElementsByTagName("title")[0];
    var homePage = "Studio Tech Talk";
    let text="";

    for (let i=items.length-1;i>=0;i--) {       // iterate through the array
        if (docName.innerHTML == homePage) {    // if the current page is the homepage, include the onmouseover events
            text=                               // to change the picture on the main page
            "<li>"+
            "<a href="+items[i][1]+
            " id="+items[i][2]+
            " title="+"'"+items[i][0]+"'"+
            " tabindex="+i+items[i][0]+    
            " onmouseover='whichPic(this.id); whichMsg(this.id)'"+">"+items[i][0]+
            "</a>"+
            "</li>";
        } else {                                // otherwise do not include onmouseover events
            text=
            "<li>"+
            "<a href="+items[i][1]+
            " id="+items[i][2]+
            " title="+"'"+items[i][0]+"'"+
            " tabindex="+i+">"+items[i][0]+
            "</a>"+
            "</li>";            
        }

        // add links to the menu, except for the current page
        if (items[i][0] != docName.innerHTML) {
            menu.insertAdjacentHTML("afterbegin",text);
        } 
    }
}

makeMenu(newMenu);
//makeMenu();