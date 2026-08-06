// JavaScript Document
"use strict";

document.addEventListener('DOMContentLoaded', function () {
     // Get DOM elements
     const menuToggle = document.querySelector('.menu-toggle');
     const sidenav = document.querySelector('#sidenav');
     const overlay = document.querySelector('.nav-overlay');
     const dropdown = document.getElementsByClassName("dropdown-btn");
     var dropdownBtns = document.querySelectorAll('.dropdown-btn');

     // Function to check if we're in mobile view
     const isMobileView = () => window.innerWidth <= 1024;

     // Initialize mobile navigation
     function initMobileNav() {
          // Toggle menu
          menuToggle?.addEventListener('click', function () {
               this.classList.toggle('active');
               sidenav.classList.toggle('nav-open');
               overlay.classList.toggle('active');
               document.body.style.overflow = sidenav.classList.contains('nav-open') ? 'hidden' : '';
          });

          // Close menu when clicking overlay
          overlay?.addEventListener('click', function () {
               menuToggle.classList.remove('active');
               sidenav.classList.remove('nav-open');
               this.classList.remove('active');
               document.body.style.overflow = '';
          });

          // Close menu when clicking a link
          sidenav.querySelectorAll('a').forEach(link => {
               link.addEventListener('click', function () {
                    if (isMobileView()) {
                         menuToggle.classList.remove('active');
                         sidenav.classList.remove('nav-open');
                         overlay.classList.remove('active');
                         document.body.style.overflow = '';
                    }
               });
          });
     }

     // Initialize desktop navigation
     function initDesktopNav() {
          // Get current page path
          const currentPath = window.location.pathname;

          // Check if any dropdown item is active
          const isDropdownActive = Array
               .from(document.querySelectorAll('.dropdown-container a'))
               .some(link => link.getAttribute('href') === currentPath);

          // Initialize dropdown buttons
          for (let i = 0; i < dropdown.length; i++) {
               const btn = dropdown[i];
               const dropdownContent = btn.nextElementSibling;

               // If current page is in dropdown, open it automatically
               if (isDropdownActive && !isMobileView()) {
                    btn.classList.add('active');
                    dropdownContent.classList.add('show');
               }

               // Add click event listener
               btn.addEventListener("click", function (e) {
                    // For mobile: allow normal operation
                    if (isMobileView()) {
                         this.classList.toggle("active");
                         dropdownContent.classList.toggle('show');
                    } else {
                         // For desktop: handle session storage
                         this.classList.toggle("active");
                         dropdownContent.classList.toggle('show');

                         // Save state to sessionStorage only in desktop view
                         const isOpen = dropdownContent.classList.contains('show');
                         sessionStorage.setItem('dropdownState', isOpen);
                    }
               });
          }

          // Restore state from sessionStorage (desktop only)
          if (!isMobileView()) {
               const savedState = sessionStorage.getItem('dropdownState');
               if (savedState === 'true' || isDropdownActive) {
                    const firstDropdown = dropdown[0];
                    if (firstDropdown) {
                         firstDropdown.classList.add('active');
                         firstDropdown.nextElementSibling.classList.add('show');
                    }
               }
          }
     }

     // Handle current page
     function currentPage() {
          const current = document.querySelector(".active_tab");
          if (current) {
               current.removeAttribute("href");
               current.setAttribute('title', "You're already here");
          }
     }

     // Initialize both navigation systems
     initMobileNav();
     initDesktopNav();
     currentPage();

     // Handle resize events
     let resizeTimer;
     window.addEventListener('resize', function () {
          clearTimeout(resizeTimer);
          resizeTimer = setTimeout(function () {
               // Reset mobile nav elements when switching to desktop
               if (!isMobileView()) {
                    menuToggle.classList.remove('active');
                    sidenav.classList.remove('nav-open');
                    overlay.classList.remove('active');
                    document.body.style.overflow = '';
               }
          }, 250);
     });
});