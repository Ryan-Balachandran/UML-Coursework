"use strict";

let folderPath = "studioImages/";

// define variables containing file names
let defaultIndexPic = "";

let ai = "studioImages/Scarlett-18i8_3quart-Left_LR-150x150.png";
let pc = "studioImages/pc-150x150.png";
let os = "studioImages/ubuntuStudio-150x150.png";
let midi = "studioImages/p1_hero-150x150.png";
let hardPerf = "studioImages/juno-ds61_rev1_gal-150x150.png";
let recording ="studioImages/retina_no_plugs2-150x150.png";
let softInst = "studioImages/Zyn-Fusion-150x150.png";
let sound = "studioImages/studioMonitors-150x150.png";
let connections = "studioImages/connections-150x150.png";
let functionalityList = "studioImages/list-150x150.png";
let newsletter = "studioImages/newsletter-150x150.jpg";
let home = "/home/kevin/Programing/Programs/info-3020/kevbook/indexProject.html";
let studio = "/home/kevin/Programing/Programs/info-3020/kevbook/studio.html";

// define variables containing messages
let pcMsg = "Here you will find information about PC system requirements.";
let aiMsg = "Here you will find information about audio interfaces";
let osMsg = "Here you will find information about the Ubuntu Studio linux operating system"
let midiMsg = "Here you will find information about midi controllers";
let hardPerfMsg = "Here you will find information about exernal audio sources";
let recordingMsg = "Here you will find information about Ardour";
let softInstMsg = "Here you will find information about virtual instruments";
let soundMsg = "Information about studio quality monitor speakers and headphones";
let connectionsMsg = "Here you will find information on how to make all the connections";


// function receives the element id as an argument and uses it as the source of the index pic
function whichPic(thisPic) { 
        document.getElementById("indexPic").src = eval(thisPic) ;
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
        case "softInst":
            msg = softInstMsg;
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
                }
    document.getElementById("picMsg").innerHTML = msg;
}

defaultIndexPic = "";
document.getElementById("indexPic").src = ""; // the default index pic is displayed

$(() => {
    // add click events to each topic in the list
    $("dl#info dt").click(e => {
        // alternate between hiding and showing the information
        let topic = $(e.target);
        let info = $(topic.next());

        $(topic).toggleClass("hiddenInfo");

        if ($(topic).hasClass("hiddenInfo")) {
            $(info).hide(600);
        } else {
            $(info).show(600);
        }
    });
});