class WebGLExample {
    constructor(width, height) {
        this.div = document.createElement('div');
        document.body.appendChild(this.div);

        // add controls
        this.randomColorButton = document.createElement('button');
        this.randomColorButton.textContent = 'Different Random Color';

        const colorElements = [
            {c:'red',    dis:'Red',              min:0, max:1,     step:0.1},
            {c:'green',  dis:'Green',            min:0, max:1,     step:0.1},
            {c:'blue',   dis:'Blue',             min:0, max:1,     step:0.1},
            {c:'alpha',  dis:'Alpha',            min:0, max:1,     step:0.1},
            {c:'size',   dis:'Point Size',       min:1, max:100,   step:0.1},
            {c:'points', dis:'Number of Points', min:0, max:10000, step:100}
        ];
        colorElements.forEach(c => {
            const id = `${c.c}Range`;
            const label = document.createElement('label');
            label.for = id;
            const o = this[id] = document.createElement('input');
            label.textContent = c.dis;
            o.id = `${c.c}Range`;
            o.type = 'range';
            o.min = c.min;
            o.max = c.max;
            o.step = c.step;
            label.appendChild(o);
            this.div.appendChild(label);
        });

        // add canvas
        this.canvas = document.createElement('canvas');
        document.body.appendChild(this.canvas);

        // Configure WebGL
        this.gl = WebGLUtils.setupWebGL(this.canvas);
        this.gl.viewport(0,0, width, height);
        this.gl.clearColor(1.0,1.0,1.0,1.0);

        this.program;
    }
}