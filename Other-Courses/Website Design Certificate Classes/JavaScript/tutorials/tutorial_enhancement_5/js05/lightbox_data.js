"use strict";
/*    JavaScript 7th Edition
      Chapter 5
      Chapter Case

      Image List

      Filename:lightbox_data.js
*/

// Title of the slideshow
let lightboxTitle = "Dragons! Dragons! Dragons!";

// Names of the image files shown in the slideshow
let imgFiles = ["images/bronzedragon.jpg", "images/dragon_background.jpg", "images/dragoncity.jpg", "images/dragonfantasy.jpg", 
                "images/dragonfantasy1.jpg", "images/dragonfire.jpg", "images/dragonflight.jpg", "images/dragonmount.jpg",
                "images/dragonparent.jpg", "images/european.jpg", "images/dragontamer2.jpg", "images/dragontamer3.jpg", 
                "images/earthdragon.jpg", "images/fantasy_city.jpg", "images/fantasy_landscape1.jpg", "images/fantasy_landscape2.jpg", 
                "images/fantasybackground.jpg", "images/statue_valley.jpg", "images/fantasytree.jpg", "images/firedragon.jpg", 
                "images/forestdragon.jpg", "images/greatdragon.jpg", "images/green_dragon.jpg", "images/green_dragon2.jpg", 
                "images/green_dragon3.jpg", "images/ice_fire.jpg", "images/smaug.jpg", "images/smaug2.jpg", 
                "images/waterdragon.jpg", "images/westerndragon.jpg", "images/whitedragon.jpg", "images/whitedragon2.jpg", 
                "images/whitedragon3.png", "images/wyvern1.jpg", "images/wyvern2.jpg", "images/wyvern3.jpg", 
                "images/wyvern4.jpg", "images/wyvern5.jpg", "images/wyvern6.jpg", "images/wyvernbackground.jpg", 
                "images/wyvernhunt.jpg"]

// Captions associated with each image
let imgCaptions = new Array(12);
imgCaptions[0]="A large bronze dragon from D&D";
imgCaptions[1]="A dark mountainous landscape with swarms of dragons in the sky"; 
imgCaptions[2]="A dark, cloudy day with a large dragon city in the back"; 
imgCaptions[3]="A large mountain range with a flying wyvern"; 
imgCaptions[4]="A large mountain range with a couple flying dragons";
imgCaptions[5]="A silver dragon breathing fire on a grassy plain under a moonlit night";
imgCaptions[6]="A large floating city of dragons above a wide valley";
imgCaptions[7]="A boy riding a wingless dragon";
imgCaptions[8]="A family of orange black-stripped dragons in a forest";
imgCaptions[9]="A blonde man in blue garb next to an earth dragon";
imgCaptions[10]="A large black dragon in an areana being tamed by a woman with a whip";
imgCaptions[11]="A mountainous earth dragon rising from the ground";
imgCaptions[12]="A regal red dragon from D&D";
imgCaptions[13]="A large forest with a dragon city in the background";
imgCaptions[14]="A beautiful landscape of mountains and grassy plains";
imgCaptions[15]="A large snowy mountain range";
imgCaptions[16]="A Large snowy mountain range with a waterfall and lake";
imgCaptions[17]="A gigantic tree towering over the lands";
imgCaptions[18]="A red scaled fire dragon";
imgCaptions[19]="A green forest dragon with a hawk perched on its tail";
imgCaptions[20]="A mountainous red dragon standing atop a large mountain";
imgCaptions[21]="A large green dragon standing atop a hill";
imgCaptions[22]="A large green dragon in a dark forest";
imgCaptions[23]="A small green dragon posing on some rocks";
imgCaptions[24]="A battle between a silver and red dragon";
imgCaptions[25]="Painting of smaug sleeping on his hoard with a hobbit overlooking him";
imgCaptions[26]="Smaug searching for Bilbo Baggins";
imgCaptions[27]="A large valley with two giant statues on either side";
imgCaptions[28]="A large water dragon beneath the sea above a ruined ship";
imgCaptions[29]="A silver dragon posing on a cliff";
imgCaptions[30]="A white dragon from D&D";
imgCaptions[31]="A white dragon resting on a hill";
imgCaptions[32]="A white wyvern";
imgCaptions[33]="A tigrex from monster hunter";
imgCaptions[34]="A green wyvern";
imgCaptions[35]="A tv show wyvern";
imgCaptions[36]="A small wyvern sitting atop an egg";
imgCaptions[37]="A brown wyvern with a big tail fan";
imgCaptions[38]="Smaug with open maw";
imgCaptions[39]="A large wyvern sitting atop of large mountain";
imgCaptions[40]="A white dragon hunting a centaur";

// Count of images in the slideshow
let imgCount = imgFiles.length;
