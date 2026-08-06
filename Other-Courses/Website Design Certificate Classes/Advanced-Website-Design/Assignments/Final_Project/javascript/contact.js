// JavaScript Document

"use strict";

class FormValidator {
     constructor() {
          this.form = document.getElementById("contactMe");
          this.createError = document.getElementById('createError');
          this.validationRules = {
               firstName: {
                    pattern: /^[A-Za-z]+$/,
                    messages: {
                         valueMissing: "You forgot to enter your first name",
                         patternMismatch: "Please use only letters"
                    }
               },
               lastName: {
                    pattern: /^[A-Za-z]+$/,
                    messages: {
                         valueMissing: "You forgot to enter your last name",
                         patternMismatch: "Please use only letters"
                    }
               },
               age: {
                    messages: {
                         valueMissing: "You forgot to enter your age"
                    }
               },
               phone: {
                    pattern: /^\(?([0-9]{3})\)?[-. ]?([0-9]{3})[-. ]?([0-9]{4})$/,
                    messages: {
                         valueMissing: "You forgot to enter phone number",
                         patternMismatch: "Please enter a valid phone number format: (123)456-7890"
                    }
               },
               email: {
                    pattern: /^[^\s@]+@[^\s@]+\.[^\s@]+$/,
                    messages: {
                         valueMissing: "You forgot to enter your email",
                         patternMismatch: "Please provide a valid email"
                    }
               },
               state: {
                    pattern: /^(?:A[KLRZ]|C[AOT]|D[CE]|FL|GA|HI|I[ADLN]|K[SY]|LA|M[ADEINOST]|N[CDEHJMVY]|O[HKR]|P[AR]|RI|S[CD]|T[NX]|UT|V[AT]|W[AIVY])*$/,
                    messages: {
                         valueMissing: "You forgot to enter your state",
                         patternMismatch: "Please provide a valid two-letter state code"
                    }
               },
               zip: {
                    pattern: /^\d{5}(-\d{4})?$/,
                    messages: {
                         valueMissing: "You forgot to enter your zip code",
                         patternMismatch: "Please provide a valid 5-digit zip code"
                    }
               }
          };

          this.initialize();
     }

     initialize() {
          // Set up form submission handler
          this.form.addEventListener('submit', (e) => this.handleSubmit(e));

          // Set up input validation handlers
          Object.keys(this.validationRules).forEach(fieldName => {
               const element = document.getElementById(fieldName);
               if (element) {
                    element.addEventListener('input', () => this.validateField(fieldName));
                    element.addEventListener('blur', () => this.validateField(fieldName));
               }
          });
     }

     validateField(fieldName) {
          const element = document.getElementById(fieldName);
          const rules = this.validationRules[fieldName];

          if (!element || !rules) return;

          let message = "";

          if (element.validity.valueMissing) {
               message = rules.messages.valueMissing;
          } else if (element.validity.patternMismatch) {
               message = rules.messages.patternMismatch;
          }

          element.setCustomValidity(message);
          return message === "";
     }

     showError(message) {
          this.createError.style.display = 'block';
          this.createError.textContent = message;
          setTimeout(() => {
               this.createError.style.display = 'none';
          }, 3000);
     }

     validateForm() {
          let isValid = true;
          Object.keys(this.validationRules).forEach(fieldName => {
               if (!this.validateField(fieldName)) {
                    isValid = false;
               }
          });
          return isValid;
     }

     handleSubmit(e) {
          e.preventDefault();
          if (this.validateForm()) {
               // Form is valid, proceed with submission
               this.form.submit();
          } else {
               this.showError('Please fix any error(s) to submit');
          }
     }
}

// Initialize the form validator when the DOM is loaded
document.addEventListener('DOMContentLoaded', () => {
     new FormValidator();
});