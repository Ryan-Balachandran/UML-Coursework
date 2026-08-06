"use strict"

function dragon(species, age, wings, legs, pair, eggs, scale, height) {
     this.species = species;
     this.age = age;
     this.wings = wings;
     this.legs = legs;
     this.pair = pair;
     this.eggs = eggs;
     this.scale = scale;
     this.height = height;
}

// created an object literal
let sound = {
     getCry: function () {
          return "RRRRRRRAAAAAAAAAAAWWWWWWWWWWWRRRRRRR!!!!!!!";
     },

     setCry: function () {
          let cry = prompt("Enter the sound you want your dragon to make");
          return cry;
     }
};

dragon.prototype.getDescription = function () {
     return    "Dragon Species: " + this.species + "\n" +
               "Dragon Age: " + this.age + "\n" + 
               "Dragon has Wings: " + this.wings + "\n" + 
               "# of legs: " + this.legs + "\n" + 
               "Pairs of wings: " + this.pair + "\n" + 
               "# of eggs: " + this.eggs + "\n" + 
               "Strength of Scales: " + this.scale + "\n" + 
               "Dragon Height: " + this.height + "\n";
}