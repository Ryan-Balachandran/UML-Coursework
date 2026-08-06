const openBtn = document.getElementById("open");
const closeBtn = document.getElementById("close");

let newWindow;

openBtn.addEventListener('click', function() {
     // Code run upon 'open' click
     // newWindow = window.open('http://google.com', '_blank');
     // window.open('http://google.com', 'googleWindow', 'width=400, height=400, left=200, right=200');
     newWindow = window.open('', 'newWindow', 'width=400, height=400, left=200, right=200');
     newWindow.document.body.innerHTML = `
     <!DOCTYPE html>

     <html lang="en">
          <head>
               <meta charset="UTF-8">
               <meta name="viewport" content="width=device-width, initial-scale=1.0">
               <title>Form</title>
          </head>

          <body>
               <form id="form">
                    <label for="username">Username: </label>
                    <input type="text" name="username"><br>

                    <label for="password">Password: </label>
                    <input type="password" name="password"><br>

                    <button type="submit">Login</button>
               </form>
          </body>
     </html>
     `;

     const form = newWindow.document.getElementById('form');

     form.addEventListener('submit', function() {
          if (form.username.value === "test" &&  form.password.value === "test"){
               document.getElementById('output').textContent = "login Successful";
          }
          else {
               document.getElementById('output').textContent = "login Failed";
          }

          newWindow.close();
     })
})

closeBtn.addEventListener('click', function() {
     // Code run upon 'close' click
     newWindow.close();
})