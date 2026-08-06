"use strict";

class DragonValidator {
     constructor() {
          // Use object destructuring and optional chaining for safer element selection
          const { dragonMaker: form } = document.forms;

          // Initialize key form elements
          this.form = form;
          this.createBtn = document.getElementById("create");
          this.createError = document.getElementById("createError");

          // Performance optimization: Pre-bind methods
          this.validators = {
               species: this.validateSpecies.bind(this),
               age: this.validateAge.bind(this),
               wings: this.validateWings.bind(this),
               legs: this.validateLegs.bind(this),
               wingPair: this.validateWingsPair.bind(this),
               eggs: this.validateEggs.bind(this),
               height: this.validateHeight.bind(this)
          };

          this.init();
     }

     init() {
          // Use event delegation for more efficient event handling
          this.form.addEventListener("input", this.handleInput.bind(this));
          this.form.addEventListener("change", this.handleChange.bind(this));
          this.form.addEventListener("submit", this.handleSubmit.bind(this));
     }

     // Centralized input handling with dynamic validation
     handleInput(event) {
          const field = event.target.id;
          if (this.validators[field]) {
               this.validators[field](event.target);
          }
     }

     // Centralized change handling
     handleChange(event) {
          if (event.target.name === "wings") {
               this.handleWingsChange(event);
          }
     }

     // Simplified form submission handler
     handleSubmit(event) {
          event.preventDefault();
          if (this.validateForm()) {
               this.createDragon();
               this.form.reset();
          }
     }

     handleWingsChange(event) {
          const wingPairInput = document.getElementById("wingPair");
          const hasWings = event.target.value === "Yes";

          wingPairInput.disabled = !hasWings;
          wingPairInput.required = hasWings;
          wingPairInput.value = hasWings ? "" : "0";
     }

     // Memoized validation to reduce redundant checks
     validateForm() {
          const invalidFields = Object.keys(this.validators)
               .map(field => document.getElementById(field))
               .filter(element => element && !element.validity.valid);

          if (invalidFields.length > 0) {
               this.showError('Please fix any error(s) to submit');
               return false;
          }
          return true;
     }

     showError(message, duration = 3000) {
          this.createError.textContent = message;
          this.createError.style.display = 'block';

          // Use requestAnimationFrame for smoother timing
          requestAnimationFrame(() => {
               setTimeout(() => {
                    this.createError.style.display = 'none';
               }, duration);
          });
     }

     // Individual validation methods remain largely the same
     validateSpecies() {
          const species = document.getElementById("species");
          if (species.validity.valueMissing) {
               species.setCustomValidity("You forgot to enter a species");
          } else if (species.validity.patternMismatch) {
               species.setCustomValidity("Please use only letters and a single space between words");
          } else {
               species.setCustomValidity("");
          }
     }

     // // Individual validation methods remain largely the same
     // validateSpecies(input) {
     //      input.setCustomValidity(
     //           input.validity.valueMissing ? "You forgot to enter a species" :
     //                input.validity.patternMismatch ? "Please use only letters and a single space between words" : ""
     //      );
     // }

     validateAge() {
          const age = document.getElementById("age");
          if (age.validity.valueMissing) {
               age.setCustomValidity("You forgot to enter an age for your dragon");
          } else if (age.validity.patternMismatch) {
               age.setCustomValidity("Please use only numbers, optionally followed by a '+'");
          } else {
               age.setCustomValidity("");
          }
     }

     validateWings() {
          const wings = document.getElementById("wings");
          wings.setCustomValidity(wings.validity.valueMissing ?
               "You forgot to check whether your dragon has wings" : "");
     }

     validateLegs() {
          const legs = document.getElementById("legs");
          if (legs.validity.valueMissing) {
               legs.setCustomValidity("You forgot to enter the number of legs");
          } else if (legs.validity.patternMismatch) {
               legs.setCustomValidity("Please enter an even number (0, 2, 4, 6, or 8)");
          } else {
               legs.setCustomValidity("");
          }
     }

     validateWingsPair() {
          const wingPair = document.getElementById("wingPair");
          if (wingPair.validity.valueMissing && !wingPair.disabled) {
               wingPair.setCustomValidity("Please enter the number of wing pairs");
          } else if (wingPair.validity.patternMismatch) {
               wingPair.setCustomValidity("Please use only numbers");
          } else {
               wingPair.setCustomValidity("");
          }
     }

     validateEggs() {
          const eggs = document.getElementById("eggs");
          if (eggs.validity.valueMissing) {
               eggs.setCustomValidity("Please enter the number of eggs in a clutch");
          } else if (eggs.validity.patternMismatch) {
               eggs.setCustomValidity("Please enter a number between 1 and 9");
          } else {
               eggs.setCustomValidity("");
          }
     }

     validateHeight() {
          const height = document.getElementById("height");
          if (height.validity.valueMissing) {
               height.setCustomValidity("Please enter the dragon's height");
          } else if (height.validity.patternMismatch) {
               height.setCustomValidity("Please use the format: 3' or 3' 5''");
          } else {
               height.setCustomValidity("");
          }
     }

     createDragon() {
          const characteristics = document.getElementById("characteristics");
          const row = document.createElement("tr");

          const fields = ['species', 'age', 'wings', 'legs', 'wingPair', 'eggs', 'scale', 'height'];

          // Use map and forEach for more functional approach
          fields.map(field => {
               const cell = document.createElement("td");
               let value = this.form[field].value;

               // Add specific formatting for certain fields
               switch (field) {
                    case 'age': value += ' years'; break;
                    case 'scale': value = parseFloat(value).toFixed(1); break;
               }

               cell.textContent = value;
               return cell;
          }).forEach(cell => row.appendChild(cell));

          characteristics.appendChild(row);
     }
}

// Initialize the dragon validator when the DOM is loaded
document.addEventListener('DOMContentLoaded', () => new DragonValidator());