"use strict";

window.addEventListener("load", createLightbox);
window.addEventListener("load", calculateLightbox);
window.addEventListener("resize", calculateLightbox);

function createLightbox(){
   let folderPath = "studioImages/";

    // lightbox contatiner
    let lightBox = document.getElementById("lightbox");

    calculateLightbox;

    // parts of the lightbox
    let lbPlay = document.createElement("div");
    let lbImages = document.createElement("div");
    let lbCounter = document.createElement("div");

    // desgin the lightbox slide counter
    lbCounter.id = "lbCounter";
    let currentImg = 1;

    // design the lightbox play-pause button
    lightBox.appendChild(lbPlay);
    lbPlay.id = "lbPlay";
    lbPlay.innerHTML = "&#9199;";
    let timeID;
    lbPlay.onclick = function () {
        if (timeID) {
            // stop the slideshow
            window.clearInterval(timeID);
            timeID = undefined;
        } else {
            // start the slideshow
            showNext();
            timeID = window.setInterval(showNext,3000);
        }
    }

    // design the lightbox images container
    lightBox.appendChild(lbImages);
    lbImages.id = "lbImages";

    // add images from the imgFiles array to the container
    for (let i=0;i<imgCount;i++){
        let image = document.createElement("img");
        image.src = folderPath+imgArray[i];
        image.alt = imgCaptions[i];
        lbImages.appendChild(image);
    }

    // function to move forward through the image list
    function showNext() {
        lbImages.appendChild(lbImages.firstElementChild);
        (currentImg < imgCount) ? currentImg++ : currentImg = 1;
    }

    // function to move backward through the image list
    function showPrev() {
        lbImages.insertBefore(lbImages.lastElementChild, lbImages.firstElementChild) ;
        (currentImg > 1) ? currentImg-- : currentImg = imgCount;
    }

    window.setInterval(showNext,3000);
}

window.addEventListener("load", setupGallery);

function setupGallery() {
   let imageCount = imgFiles.length;
   let galleryBox = document.getElementById("gallery");
   let currentSlide = 1;
   let runShow = true;
   let showRunning;
           
   let playPause = document.createElement("div");
   playPause.id = "playPause";
   playPause.innerHTML = "&#9199;";
   playPause.onclick = startStopShow;
   galleryBox.appendChild(playPause);
   
   let slideBox = document.createElement("div");
   slideBox.id = "slideBox";
   galleryBox.appendChild(slideBox);
   
   
   for (let i = 0; i < imageCount; i++) {
      let image = document.createElement("img");
      image.src = imgFiles[i];
      //image.alt = imgCaptions[i];
      slideBox.appendChild(image);
   }
      
   function moveToRight() {
      let firstImage = slideBox.firstElementChild.cloneNode("true");
      //firstImage.onclick = createModal;
      slideBox.appendChild(firstImage);
      slideBox.removeChild(slideBox.firstElementChild);
      currentSlide++;
      if (currentSlide > imageCount) {
         currentSlide = 1;
      }
      //slideCounter.textContent = currentSlide + " / " + imageCount;
   }
   
   function moveToLeft() {
      let lastImage = slideBox.lastElementChild.cloneNode("true");
      slideBox.removeChild(slideBox.lastElementChild);
      slideBox.insertBefore(lastImage, slideBox.firstElementChild);
      currentSlide--;
      if (currentSlide === 0) {
         currentSlide = imageCount;
      }
      //slideCounter.textContent = currentSlide + " / " + imageCount;      
   }  
   
   function startStopShow() {
      if (runShow) {
         showRunning = window.setInterval(moveToRight, 2000);
         runShow = false;
      } else {
         window.clearInterval(showRunning);
         runShow = true;
      }
   }   
}

function calculateLightbox() {
   let divWidth = document.getElementById("lightbox").clientWidth;
   let remainder = Math.trunc(divWidth / 160);

   if ((divWidth % 160) != 0) {
      divWidth = remainder*160;
      document.getElementById("lightbox").setAttribute("style","width:"+divWidth+"px");
   }  
}



