"use strict";

let signupBtn = document.getElementById("signupBtn");
let cancelBtn = document.getElementById("cancelBtn");


// validate the payment when the submit button is clicked
signupBtn.addEventListener("click", validateFirstName);
signupBtn.addEventListener("click", validateLastName);
signupBtn.addEventListener("click", validateEmail);
cancelBtn.addEventListener("click", cancelSignUp);

// check if a first name has been entered
function validateFirstName() {
    let firstName = document.getElementById("firstName");
    if (firstName.validity.valueMissing) {
        firstName.setCustomValidity("Please enter your first name");
    } else {
        firstName.setCustomValidity("");
    }
}

// check if a last name has been entered
function validateLastName() {
    let lastName = document.getElementById("lastName");
    if (lastName.validity.valueMissing) {
        lastName.setCustomValidity("Please enter your last name");
    } else {
        lastName.setCustomValidity("");
    }
}

// function to check if an email address has been entered
function validateEmail() {
    let email = document.getElementById("email");
    let theEmail = email.value;
    let pattern = /^\w+[\w-\.]*\@\w+((-\w+)|(\w*))\.[a-z]{2,3}$/;
    let testResult = pattern.test(theEmail);
    
    if (email.validity.valueMissing) {
        email.setCustomValidity("Please enter your email address");
    } else if (!(testResult)) {
        email.setCustomValidity("Please enter a valid email address");
    } else {
        email.setCustomValidity("");
    }
}

// function to cancel signing up for the newsletter
function cancelSignUp() {
    this.form.reset();
    let overlayFlag=1;
    creatOverlay(overlayFlag);
}

// function to create overlay that displays confirmation message regarding the cancelation
function creatOverlay(overlayFlag) {
    let overlay = document.createElement("div");
    overlay.id = "messageOverlay";

    // add the figure box to the overlay
    let figureBox = document.createElement("figure");
    overlay.appendChild(figureBox);

    // add the caption to the figure box
    let overlayCaption = document.createElement("figcaption");
    if (overlayFlag) {
        overlayCaption.textContent = "No information will be submitted. Thank you for you interest. You'll be redirected to the main page. Thank you.";
    }
    figureBox.appendChild(overlayCaption);

    // add a close button to the overlay
    let closeBox = document.createElement("div");
    closeBox.id = "messageOverlayClose";
    closeBox.innerHTML = "&times;";
    closeBox.onclick = function() {
        document.body.removeChild(overlay);
        location.href="index.html"
    }
    overlay.appendChild(closeBox);

    // display the overlay
    document.body.appendChild(overlay);
}
