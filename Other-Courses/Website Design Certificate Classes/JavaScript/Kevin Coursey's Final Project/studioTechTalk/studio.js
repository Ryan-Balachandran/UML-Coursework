"use strict";

let folderPath = "studioImages/";

// define variables containing file names
let ai = "studioImages/Scarlett-18i8_3quart-Left_LR-150x150.png";
let pc = "studioImages/pc-150x150.png";
let os = "studioImages/ubuntuStudio-150x150.png";
let midi = "studioImages/p1_hero-150x150.png";
let hardPerf = "studioImages/juno-ds61_rev1_gal-150x150.png";
let recording ="studioImages/retina_no_plugs2-150x150.png";
let soft = "studioImages/Zyn-Fusion-150x150.png";
let sound = "studioImages/studioMonitors-150x150.png";
let connections = "studioImages/connections-150x150.png";
let functionalityList = "studioImages/list-150x150.png";
let newsletter = "studioImages/newsletter-150x150.jpg";
let home = "/home/kevin/Programing/Programs/info-3020/kevbook/indexProject.html";
let studio = "/home/kevin/Programing/Programs/info-3020/kevbook/studio.html";

// define variables containing messages
let pcMsg = "The central hub of the entire studio.";
let aiMsg = "Converts incoming analog signals to digital signals and transmits them to the PC.";
let osMsg = "Ubuntu Studio linux operating system.";
let midiMsg = "Midi controllers allow hands-on access to the software on the computer.";
let hardPerfMsg = "External audio sources, like guitars, keyboards, drums, microphones, etc.";
let recordingMsg = "The digital audio workstation (DAW) handles all recording, processing, and playback.";
let softMsg = "Internal audio sources like software synthesizers, drum machines, etc. ";
let soundMsg = "Studio quality monitor speakers and headphones";
let connectionsMsg = "Make all the connections you need to get up and running";
let newsletterMsg = "Sign up for our newsletter";
let functionalityMsg = "The functionality list provides information on the functionality behind the features on this website";

// function receives the element id as an argument and uses it as the source of the index pic
function whichPic(thisPic) {    
        document.getElementById("indexPic").src = eval(thisPic);
        document.getElementById("indexPic").alt="";
    }

// function receives the element id as an argument and passes it to picMsg. picMsg returns the corresponding message and it is diplayed in the alert window
function whichMsg(thisPic) { 
    let msg = "";

    switch(thisPic) {
        case "pc":
            msg = pcMsg;
            break;
        case "os":
            msg = osMsg;
            break;
        case "midi":
            msg = midiMsg;
            break;
        case "hardPerf":
            msg = hardPerfMsg;
            break;
        case "recording":
            msg = recordingMsg;
            break;
        case "soft":
            msg = softMsg;
            break;
        case "sound":
            msg = soundMsg;
            break;
        case "ai":
            msg = aiMsg;
            break;
        case "connections":
            msg = connectionsMsg;
            break;
        case "configuration":
            msg = configurationMsg;
            break;
        case "newsletter":
            msg = newsletterMsg;
            break;
        case "functionalityList":
            msg = functionalityMsg;
            break;
                }
    document.getElementById("picMsg").innerHTML = msg;
};

let defaultIndexPic = pc;
document.getElementById("picMsg").innerHTML = pcMsg;
document.getElementById("indexPic").src = defaultIndexPic; // the default index pic is displayed

// declare associative array to store picture names and a corresponding number key
let randomPicArray = {1:"feelTheMusic.jpg", 2:"girlListening.jpg", 3:"headphonesHeart.jpg", 4:"musicaHand.jpg", 5:"musicArtLife.jpg",
                    6:"musicCreateIt.jpg", 7:"musicFeelings.jpg", 8:"musicGraffiti.jpg", 9:"musicIs.jpg", 10:"musicIsLove.jpg",
                    11:"musicLifeline.jpg", 12:"musicNotes.jpg", 13:"pianoKeys.jpg", 14:"speaker.jpg", 15:"youAreTheMusic.jpg" }
                    
changeRandPic();
let timeVar = window.setInterval(changeRandPic, 3000);

// function that chooses a random number and displays the associated picture
function changeRandPic() {
    let randomNumber = Math.floor(1+15*Math.random()); // the random number becomes the key to be chosen
    let randomPic ="randomImages/"+randomPicArray[randomNumber];
    document.getElementById("randomPic").src = randomPic; // the random pic is displayed
};