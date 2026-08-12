// Based on examples made by Edward Angel

"use strict";

let gl;
let points;
const NUM_POINTS = 100000;
let redRange, greenRange, blueRange, alphaRange;

const g = function(id) { return document.getElementById(id); }

const get = function(shader, callback) {
    const xmlHttp = new XMLHttpRequest();
    xmlHttp.onerror = function() { alert('Server not up') };
    xmlHttp.onreadystatechange = callback;
    xmlHttp.open('GET', `http://localhost/${shader}`,true);
    xmlHttp.send();
}

const getShaders = function(callback) {
    //  Load shaders and initialize attribute buffers
    get('fshader21.glsl', function() {
        if(this.readyState === 4 && this.status === 200) {
            const s = document.createElement('script');
            s.id = "fragment-shader";
            s.type = "x-shader/x-fragment";
            s.textContent = this.responseText;
            document.head.appendChild(s);
            getVertexShader(callback);
        }
    });
}

const getVertexShader = function(callback) {
    //  Load shaders and initialize attribute buffers
    get('vshader21.glsl', function() {
        if(this.readyState === 4 && this.status === 200) {
            const s = document.createElement('script');
            s.id = "vertex-shader";
            s.type = "x-shader/x-vertex";
            s.textContent = this.responseText;
            document.head.appendChild(s);
            callback();
        }
    });
}

let program;

const render = function() {
    program.r = gl.getUniformLocation(program, "r");
    program.g = gl.getUniformLocation(program, "g");
    program.b = gl.getUniformLocation(program, "b");
    program.a = gl.getUniformLocation(program, "a");

    gl.uniform1f(program.r, parseFloat(redRange.value));
    gl.uniform1f(program.g, parseFloat(greenRange.value));
    gl.uniform1f(program.b, parseFloat(blueRange.value));
    gl.uniform1f(program.a, parseFloat(alphaRange.value));

    gl.clear( gl.COLOR_BUFFER_BIT );
    gl.drawArrays( gl.POINTS, 0, points.length );
}

const sierpinskiGasket = function() {
    const canvas = g( "sierpinskiCanvas" );

    // Specify a starting point p for our iterations p must lie inside any set
    //  of three vertices
    const vertices = [vec2(-1, -1), vec2(0, 1), vec2(1, -1)];
    const u = add(vertices[0], vertices[1]);
    const v = add(vertices[0], vertices[2]);
    let p = scale(0.25, add(u, v));

    // And, add our initial point into our array of points
    points = [p];

    // Compute new points - Each new point is located midway between last point
    //  and a randomly chosen vertex
    for(let i = 0; points.length < NUM_POINTS; ++i) {
        const j = Math.floor(Math.random() * 3);
        p = add(points[i], vertices[j]);
        p = scale(0.5, p);
        points.push(p);
    }

    //  Configure WebGL
    gl = WebGLUtils.setupWebGL(canvas);
    gl.viewport(0,0, canvas.width, canvas.height);
    gl.clearColor(1.0,1.0,1.0,1.0);

    getShaders(function() {
        program = initShaders( gl, 'vertex-shader', 'fragment-shader' );
        gl.useProgram( program );

        // Load the data into the GPU
        const bufferId = gl.createBuffer();
        gl.bindBuffer( gl.ARRAY_BUFFER, bufferId );
        gl.bufferData( gl.ARRAY_BUFFER, flatten(points), gl.STATIC_DRAW );

        // Associate out shader variables with our data buffer
        const vPosition = gl.getAttribLocation( program, "vPosition" );
        gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
        gl.enableVertexAttribArray( vPosition );

        render();
    });
}

const other = function() {
    g('otherSpan').textContent = 'Other';
}

// window is the "this", the context therefore no need to specify it here.
//  Saves keystrokes. :)
onload = function init() {
    redRange = g('redRange');
    greenRange = g('greenRange');
    blueRange = g('blueRange');
    alphaRange = g('alphaRange');

    sierpinskiGasket();
    other();

    const examplesSelect = g('examplesSelect');

    const changeDiv = function() {
        let div = 0;
        let o;
        while(o = g(`div${div++}`)) {
            o.style.visibility = 'hidden';
            o.style.display = 'none';
        }
        o = g(`div${examplesSelect.value}`);
        o.style.visibility = 'visible';
        o.style.display = 'inline';
    }

    examplesSelect.onchange = changeDiv;
    changeDiv();

    redRange.value = greenRange.value = blueRange.value = 0.5;
    alphaRange.value = 1.0;

    redRange.oninput = render;
    greenRange.oninput = render;
    blueRange.oninput = render;
    alphaRange.oninput = render;

    const randColorButton = g('randColorButton');
    randColorButton.onclick = function() {
        redRange.value = Math.random();
        greenRange.value = Math.random();
        blueRange.value = Math.random();
        alphaRange.value = Math.random();
        render();
    };
};
