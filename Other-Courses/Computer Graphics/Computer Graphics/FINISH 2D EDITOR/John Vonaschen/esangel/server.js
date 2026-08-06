const express = require('express');
const app = express();
const PORT = 80;
const fs = require('fs');

// serve up files local to the server
app.use(express.static('.'));

// serve the main html if no file or endpoint is specified
app.get('/', (req, res) => {
    res.end(fs.readFileSync('index.html'));
});

app.listen(PORT, () => {
    console.log(`Listening on port ${PORT}`);
});
