// Based on examples made by Edward Angel

"use strict";

const s = {}; // The global singleton

// makes selecting more concise
s.g = function(id) { return document.getElementById(id); }

s.get = function(shader, callback) {
    const xmlHttp = new XMLHttpRequest();
    xmlHttp.onerror = function() {
        alert('Server not up')
    };
    xmlHttp.onreadystatechange = callback;
    xmlHttp.open('GET', `http://localhost/${shader}`,true);
    xmlHttp.send();
}

// This gets called second by the callback of the first one below.
s.getVertexShader = function(callback) {
    //  Load shaders and initialize attribute buffers
    s.get('vshader21.glsl', function() {
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

// This gets called first and passes the callback to the next one above.  It's
//  important to note that I need not declare the above function expression,
//  above this one instead of below because it's called in a callback and would
//  be defined by the time it's called.
s.getShaders = function(callback) {
    //  Load fragment shaders and initialize attribute buffers
    s.get('fshader21.glsl', function() {
        if(this.readyState === 4 && this.status === 200) {
            const c = document.createElement('script');
            c.id = "fragment-shader";
            c.type = "x-shader/x-fragment";
            c.textContent = this.responseText;
            document.head.appendChild(c);
            s.getVertexShader(callback);
        }
    });
}

s.render = function() {
    // before clearing and drawing set fragment values
    s.program.fr = s.gl.getUniformLocation(s.program, 'fr');
    s.program.fg = s.gl.getUniformLocation(s.program, 'fg');
    s.program.fb = s.gl.getUniformLocation(s.program, 'fb');
    s.program.fa = s.gl.getUniformLocation(s.program, 'fa');

    s.gl.uniform1f(s.program.fr, parseFloat(s.redRange.value));
    s.gl.uniform1f(s.program.fg, parseFloat(s.greenRange.value));
    s.gl.uniform1f(s.program.fb, parseFloat(s.blueRange.value));
    s.gl.uniform1f(s.program.fa, parseFloat(s.alphaRange.value));

    // clear and draw
    s.gl.clear(s.gl.COLOR_BUFFER_BIT);
    s.gl.drawArrays(s.gl.POINTS, 0, s.points.length);
}

s.loadDataIntoGPU = function() {
    if(!s.program) return;

    // Load the data into the GPU
    s.gl.bindBuffer(s.gl.ARRAY_BUFFER, s.gl.createBuffer());
    s.gl.bufferData(s.gl.ARRAY_BUFFER, flatten(s.points), s.gl.STATIC_DRAW);

    // Associate our shader variables with our data buffer
    const vPosition = s.gl.getAttribLocation(s.program, 'vPosition');
    s.gl.vertexAttribPointer(vPosition, 2, s.gl.FLOAT, false, 0,
        0);
    s.gl.enableVertexAttribArray(vPosition);

    s.program.vPointSize = s.gl.getUniformLocation(s.program, 'vPointSize')
    s.gl.uniform1f(s.program.vPointSize, parseFloat(s.PSRange.value));

    s.render();
}

s.changeGeometry = function() {
    const ratio = s.SGCanvas.height / s.SGCanvas.width;
    const third = Math.PI * 2 / 3;
    const rot = parseFloat(s.rotRange.value);
    const zoom = parseFloat(s.zoomRange.value);
    const ox = parseFloat(s.xRange.value);
    const oy = parseFloat(s.yRange.value);

    // Specify a starting point p for our iterations p must lie inside any set
    //  of three vertices
    const vertices = [
        vec2(
            ox + Math.cos(third + rot) * ratio * zoom,
            oy + Math.sin(third + rot) * zoom
        ),
        vec2(
            ox + Math.cos(third * 2 + rot) * ratio * zoom,
            oy + Math.sin(third * 2 + rot) * zoom
        ),
        vec2(
            ox + Math.cos(third * 3 + rot) * ratio * zoom,
            oy + Math.sin(third * 3 + rot) * zoom
        )
    ];
    const u = add(vertices[0], vertices[1]);
    const v = add(vertices[0], vertices[2]);
    let p = scale(0.25, add(u, v));

    // And, add our initial point into our array of points
    s.points = [p];

    // Compute new points - Each new point is located midway between last point
    //  and a randomly chosen vertex
    /** @property NOPRange */
    for(let i = 0; s.points.length < NOPRange.value; ++i) {
        const j = Math.floor(Math.random() * 3);
        p = add(s.points[i], vertices[j]);
        p = scale(0.5, p);
        s.points.push(p);
    }

    s.loadDataIntoGPU();
}

s.resizeCanvasViewport = function() {
    // the width of the canvas is the innerWidth of window minus the width of
    //  the controlDiv
    const controlDivBCR = s.g('controlDiv').getBoundingClientRect();
    const w = innerWidth - controlDivBCR.width - 50;
    const h = controlDivBCR.height;

    s.SGCanvas.width = w;
    s.SGCanvas.height = h;
    s.SGCanvas.style.width = w + 'px';
    s.SGCanvas.style.height = h + 'px';

    s.gl.viewport(0, 0, s.SGCanvas.width, s.SGCanvas.height);

    s.changeGeometry();
}

s.sierpinskiGasket = function() {
    //  Configure WebGL
    s.SGCanvas = s.g( "sierpinskiCanvas" );
    // noinspection JSCheckFunctionSignatures
    s.gl = WebGLUtils.setupWebGL(s.SGCanvas);
    if(s.gl === null) {
        alert('sierpinskiGasket: call to WebGLUtils.setupWebGL returned null');
        return;
    }
    // white with full opacity
    s.gl.clearColor(1.0, 1.0, 1.0, 1.0);

    s.redRange   = s.g('redRange');
    s.greenRange = s.g('greenRange');
    s.blueRange  = s.g('blueRange');
    s.alphaRange = s.g('alphaRange');
    s.PSRange    = s.g('PSRange');
    s.NOPRange   = s.g('NOPRange');

    s.xRange = s.g('xRange');
    s.yRange = s.g('yRange');
    s.rotRange = s.g('rotRange');
    s.zoomRange = s.g('zoomRange');

    s.xRange.value = 0;
    s.yRange.value = 0;
    s.rotRange.value = 0;
    s.zoomRange.value = 1;

    s.resizeCanvasViewport();

    // default values
    s.redRange.value = s.greenRange.value = s.blueRange.value = 0.5;
    s.alphaRange.value = s.PSRange.value = 1.0;
    s.NOPRange.value = 100000;

    // assign event handlers
    // ranges that change fragment shaders
    s.redRange.oninput = s.greenRange.oninput =
        s.blueRange.oninput = s.alphaRange.oninput = s.render;
    s.PSRange.oninput = s.loadDataIntoGPU;
    // ranges that change vertex shaders
    s.NOPRange.oninput = s.xRange.oninput = s.yRange.oninput = s.rotRange.oninput =
        s.zoomRange.oninput = s.changeGeometry;

    s.g('randColorButton').onclick = function() {
        s.redRange.value   = Math.random();
        s.greenRange.value = Math.random();
        s.blueRange.value  = Math.random();
        s.render();
    };

    s.getShaders(function() {
        s.program = initShaders(s.gl, 'vertex-shader',
            'fragment-shader');
        s.gl.useProgram(s.program);
        s.changeGeometry();
    });
}

s.sierpinskiGasket3D = function() {
}

onresize = s.resizeCanvasViewport;

// window is the "this", the context therefore no need to specify it here.
//  Saves keystrokes. :)
onload = function init() {
    const examplesSelect = s.g('examplesSelect');
    const changeDiv = function() {
        let div = 0;
        let o;
        while(o = s.g(`div${div++}`)) {
            o.style.visibility = 'hidden';
            o.style.display = 'none';
        }
        o = s.g(`div${examplesSelect.value}`);
        o.style.visibility = 'visible';
        o.style.display = 'inline';
    }
    examplesSelect.onchange = changeDiv;
    changeDiv();

    s.sierpinskiGasket();
    s.sierpinskiGasket3D();
};
