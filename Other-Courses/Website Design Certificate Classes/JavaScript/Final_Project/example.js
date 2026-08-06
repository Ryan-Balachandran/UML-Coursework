"use strict";
/*
Author: Justin Schelkin
Date:   7/4/2023

Filename: veigar.js
 */

/* Constructor for ability */

function ability(header, paragraph, youtubeCode) {
    this.header = header;
    this.paragraph = paragraph;
    this.youtubeCode = youtubeCode;
}

ability.prototype.getDescription = function () {
    return 	"<h2>" + this.header + "</h2>" + 
			"<p>" + this.paragraph + "</p>" +
			"<iframe width='560' height='315' src='https://www.youtube.com/embed/" + this.youtubeCode +
				"' title='YouTube video player'></iframe>";
}

// created an object literal for activityPassive
let abilityPassive = {
        header: "Passive - Phenomenal Evil Power",
        paragraph: "Veigar infinitely stacks on ability power. Everytime veigar hits an enemy " +
			"champion with an ability, he gains 1 ability power.",
		youtubeCode: "6kcaLh7ZdAM",
		getDescription: function () {
			return 	"<h2>" + this.header + "</h2>" + 
				"<p>" + this.paragraph + "</p>" +
				"<iframe width='560' height='315' src='https://www.youtube.com/embed/" + this.youtubeCode +
				"' title='YouTube video player'></iframe>";
		}
};

// the rest of abilities are created using an object class
let abilityQ = new ability(
        "Q - Baleful Strike",
        "Veigar throws a fast bolt of magic in a line infront of him dealing damage " +
			"to the first two enemy units hit. Units killed by this ability grant 1 ability power.",
        "yPc3bKUBjwk");

let abilityW = new ability(
        "W - Dark Matter",
        "Veigar deals a huge burst of magic damage in a small circular location. " +
			"Every 50 stacks of Phenomenal Evil reduces this abilities cooldown.",
        "fdUVtXnpy2w");

let abilityE = new ability(
        "E - Event Horizon",
        "Veigar places down a cage stunning enemy units that try to pass through the walls of this cage.",
        "aM1bzxaz3yw");

let abilityR = new ability(
        "R - Primordial Burst",
        "Veigar blasts an enemy champion dealing a large amount of magic damage. This abilities " +
			"damage is increased based on the missing health of the enemy unit.",
        "jniF1G75WRc");

// create a JSON text for abilities and show it in the console
let JSONstring = 
	JSON.stringify(abilityPassive) + 
	JSON.stringify(abilityQ) + 
	JSON.stringify(abilityW) + 
	JSON.stringify(abilityE) + 
	JSON.stringify(abilityR);
console.log(JSONstring);


//add event handlers to ability icons
document.getElementById("passive").onclick = function () {
    document.getElementById("abilityDescription").innerHTML = abilityPassive.getDescription();
}
document.getElementById("q").onclick = function () {
    document.getElementById("abilityDescription").innerHTML = abilityQ.getDescription();
}
document.getElementById("w").onclick = function () {
    document.getElementById("abilityDescription").innerHTML = abilityW.getDescription();
}
document.getElementById("e").onclick = function () {
    document.getElementById("abilityDescription").innerHTML = abilityE.getDescription();
}
document.getElementById("r").onclick = function () {
    document.getElementById("abilityDescription").innerHTML = abilityR.getDescription();
}