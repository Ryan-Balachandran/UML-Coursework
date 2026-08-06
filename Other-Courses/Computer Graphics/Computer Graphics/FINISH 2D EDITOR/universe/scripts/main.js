s.drawAll = () => {
    // clear the canvas before painting stuff
    // panning shouldn't affect the canvas clearing
    s.ctx.clearRect(0, 0, s.universeCanvas.width, s.universeCanvas.height);


    // show where the global pan point is without any panning or scaling
    s.ctx.strokeStyle = 'white';
    s.ctx.beginPath();
    s.ctx.moveTo(s.panX, s.panY - 10);
    s.ctx.lineTo(s.panX, s.panY + 10);
    s.ctx.stroke();
    s.ctx.moveTo(s.panX - 10, s.panY);
    s.ctx.lineTo(s.panX + 10, s.panY);
    s.ctx.stroke();


    s.ctx.save();
    s.ctx.translate(s.panX, s.panY);
    s.ctx.scale(s.scale, s.scale); // always scale equally
    s.ctx.rotate(s.rotation);


    // show where the mouse pointer
    s.ctx.beginPath();
    s.ctx.moveTo(s.mx, s.my - 10);
    s.ctx.lineTo(s.mx, s.my + 10);
    s.ctx.stroke();
    s.ctx.moveTo(s.mx - 10, s.my);
    s.ctx.lineTo(s.mx + 10, s.my);
    s.ctx.stroke();


    s.stepArray.forEach(sh => { if(sh.show) sh.draw(); });
    s.ctx.restore();
}




// MAYBE ------------------------
s.resizeCanvasViewport = () => {
    const h = innerHeight - 80;

    const controlDiv = s.g(`controlDiv`);
    controlDiv.style.height = `${h}px`;
    const w = innerWidth - controlDiv.getBoundingClientRect().width - 40;

    s.universeCanvas.width = w;
    s.universeCanvas.height = h;
    s.universeCanvas.style.width = `${w}px`;
    s.universeCanvas.style.height = `${h}px`;

    s.panX = s.universeCanvas.width / 2;
    s.panY = s.universeCanvas.height / 2;

    s.drawAll();
}

// IGNORE ------------------------------------------
s.backgroundImage = (image, how) => {
    const st = document.body.style;
    st.backgroundImage = `url("images/${image}")`;
    switch(how) {
        case 'repeat':
            st.backgroundRepeat = 'repeat';
            st.backgroundSize = 'initial';
            alert("HERE1");
            break;
        case 'cover':
            st.backgroundRepeat = 'initial';
            st.backgroundSize = 'cover';
            alert("HERE2");
            break;
        default:
            break;
    }
}





s.controlSelectChange = (e) => {
    let tbody;
    if(e.currentTarget) tbody = e.currentTarget.value;
    else tbody = e;
    s.controlTbodyList.forEach(t => {
        s.g(`${t}TBody`).style.display = 'none';
    })
    s.g(`${tbody}TBody`).style.display = 'table-row-group';
}







s.modeEscapeEventHandler = (e) => {
    if(e.code === 'Escape') s.noneMode();
}

s.noneMode = () => {
    // Set display 'none' all controls that provide default values for shapes
    //  and '' to all controls needed by a line shape
    const disableList = ['textShape', 'fontSize', 'fontFamily',
        'fillNStrokeButtonsRow', 'shapeFillStyle', 'shapeFillAlpha',
        'shapeStrokeStyle', 'shapeStrokeAlpha', 'lineWidth', 'lineCap',
        'lineDash', 'composite', 'lineJoin'];
    disableList.forEach(c => { s[c].tableRow.style.display = 'none'; });

    /** @property shapeSelect */
    s.shapeSelect.select.value = 'none';
    s.universeCanvas.onmousemove = undefined;
    s.universeCanvas.onmousedown = s.panningOnmousedown;
    s.universeCanvas.onmouseup = s.panningOnmouseup;
    s.universeCanvas.style.cursor = 'grab';
    s.universeCanvas.onmouseenter = () => {
        s.universeCanvas.style.cursor = 'grab';
    }
}







s.reset = () => {
    s.stepArray = [];
    s.shapeCount = 0;
    s.rotation = 0;
    s.stepListRow.update();
    s.resetZoomNPan();
    s.drawAll();
}







// USELESS ---------------------------
s.cross = (x, y, color) => {
    const crossSize = 20;

    let newLine = new Line({mx: x - crossSize, my: y - crossSize,
        lx: x + crossSize, ly: y + crossSize, lineWidth:1,
        strokeStyle:color, lineCap:'butt', alpha:100, lineDash:'',
        compositeOperation:'source-over'
    });
    s.stepArray.push(newLine);
    newLine = new Line({mx: x + crossSize, my: y - crossSize,
        lx: x - crossSize, ly: y + crossSize, lineWidth:1,
        strokeStyle:color, lineCap:'butt', alpha:100, lineDash:'',
        compositeOperation:'source-over'
    });
    s.stepArray.push(newLine);
}




s.fillNewShapeClick = () => {
    s.mFillShapes = !s.mFillShapes;
    if(!s.mFillShapes && !s.mStrokeShapes) s.mStrokeShapes = true;
    s.vStrokeNFill();
}

s.strokeNewShapeClick = () => {
    s.mStrokeShapes = !s.mStrokeShapes;
    if(!s.mFillShapes && !s.mStrokeShapes) s.mFillShapes = true;
    s.vStrokeNFill();
}

// STROKE AND FILL BUTTONS TO DETERMINE IT YOU ARE DRAWING THE STROKE, FILL OR BOTH
s.vStrokeNFill = () => {
    /** @property fillNStrokeButtonsRow */
    let st = s.fillNStrokeButtonsRow.buttons.
        find(e => e.name === 'fillNewShapes').button.style;
    st.backgroundColor = 'black';
    st.color = 'white';
    // alert("before here");

    if(s.mFillShapes) {
        // alert("here");
        st.backgroundColor = 'white';
        st.color = 'black';
    }

    st = s.fillNStrokeButtonsRow.buttons.
        find(e => e.name === 'strokeNewShapes').button.style;
    st.backgroundColor = 'black';
    st.color = 'white';
    if(s.mStrokeShapes) {
        st.backgroundColor = 'white';
        st.color = 'black';
    }
}

s.rotate = function(cx, cy, x, y, radians) {
    const
        cos = Math.cos(radians),
        sin = Math.sin(radians),
        nx = (cos * (x - cx)) + (sin * (y - cy)) + cx,
        ny = (cos * (y - cy)) - (sin * (x - cx)) + cy;
    return [nx, ny];
}





onload = () => {
    s.shapeCount = 0;
    s.stepArray = [];

    s.mFillShapes = false;
    s.mStrokeShapes = true;

    // If an image is loaded, and it is not the same size displayed as is it's
    //  natively it can flash momentarily while it's loaded and waiting for the
    //  css to load and apply styles.  This way it does not do that.  This
    //  function is only called when the page is fully loaded including images.
    s.g('universeImg').style.visibility = 'visible';    //IGNORE----------------------

    s.borderOffset = 1; // The border around the canvas is 1 pixel

    // The list and order of shapes to draw into the main canvas and

    s.universeCanvas = s.g('universeCanvas');
    s.universeCanvas.style.borderWidth = `${s.borderOffset}px`;
    s.loadControls();
    s.ctx = s.universeCanvas.getContext('2d');
    s.ctx.textAlign = 'left';




    // capture keydown events to exit from the mode
    document.addEventListener('keydown', (e) => {
        switch(e.key) {
            case 'l': s.lineMode();   break;
            case 'a': s.arcMode();    break;
            case 'r': s.rectMode();   break;

            case 't': s.textMode();   break;

            case 'q': s.qCurveMode(); break;
            case 'b': s.bCurveMode(); break;
            case 's': s.scrimMode();  break;
            default:                  break;
        }
    });



    // panning
    const panXTD = s.g('panXTD');
    const panYTD = s.g('panYTD');
    const updatePanDisplay = () => {
        panXTD.textContent = `Pan X: ${Math.floor(s.panX)}`;
        panYTD.textContent = `Pan Y: ${Math.floor(s.panY)}`;
    }

    let zoom; // The "accumulated" zoom
    s.rotation = 0;
    s.altKey = false;





    // panning
    s.universeCanvas.onmouseenter = () => {
        s.universeCanvas.style.cursor = 'grab';
    }

    s.universeCanvas.onmouseout = () => {
        s.universeCanvas.style.cursor = 'default';
    }

    s.universeCanvas.onmousedown = (e) => {
        if(s.stepArray.length === 0) return;
        s.universeCanvas.style.cursor = 'grabbing';
        let panStartX = e.clientX - s.panX;
        let panStartY = e.clientY - s.panY;
        s.universeCanvas.onmousemove = (e) => {
            s.panX = e.clientX - panStartX;
            s.panY = e.clientY - panStartY;
            updatePanDisplay();
            s.drawAll();
        }
        s.universeCanvas.onmouseup = () => {
            s.universeCanvas.style.cursor = 'grab';
            s.universeCanvas.onmousemove = undefined;
            s.universeCanvas.onmouseup = undefined;
        }
        s.panningOnmouseup = s.universeCanvas.onmouseup;
    }
    s.panningOnmousedown = s.universeCanvas.onmousedown;






    // zooming
    const zoomTD = s.g('zoomTD');
    const scaleTD = s.g('scaleTD');
    const updateZoomNScaleDisplay = () => {
        zoomTD.textContent = `Zoom: ${zoom}`;
        scaleTD.textContent = `Scale: ${Math.floor(s.scale * 10000) /
            10000}`;
        updatePanDisplay();
    }





    updateZoomNScaleDisplay();
    s.resetZoomNPan = () => {
        s.zx = s.zy = zoom = 0;
        s.scale = 1;
        updateZoomNScaleDisplay();
    }
    s.resetZoomNPan();



    
    s.universeCanvas.onwheel = (e) => {
        [s.mx, s.my] = s.mousePosition(e);
        if(s.mx !== s.panX) {
            const adjustX = s.mx - s.panX;
            const adjustY = s.my - s.panY;
            s.stepArray.forEach(st => {
                if(st.panX) {
                    st.panX += adjustX;
                    st.panY += adjustY;
                }
            });
            s.panX = s.mx;
            s.panY = s.my;
        }



        if(e.altKey) {
            const rotationIncrement = (e.deltaY / 100) * (Math.PI / 180);
            s.rotation += rotationIncrement;
            updatePanDisplay();
        } else {
            const growthFactor = 1.1;
            const zoomIncrement = e.deltaY / 100; // This one zoom
            zoom += zoomIncrement; // The "accumulated" zoom
            s.scale = Math.pow(growthFactor, zoom); // The "accumulated" scale
            updateZoomNScaleDisplay();
        }

        s.drawAll();
    }





    

    s.controlSelect = s.g('controlSelect');
    s.controlSelect.onchange = s.controlSelectChange;
    s.controlTbodyList = [];

    // rows of controls will be appended to this table
    const controlTable = s.g('controlTable')

    // defined above is an array of complex objects of defined controls
    s.controls.forEach((t) => {
        // Each element of the array is a table body of controls that can be
        //  displayed or hidden
        const tbE = document.createElement('tbody');
        controlTable.appendChild(tbE);
        tbE.id = `${t.tbody}TBody`;

        // For each table body add an option to the pull-down list
        {   const optionE = document.createElement('option');
            s.controlSelect.appendChild(optionE);
            optionE.textContent = t.tbody;
        }




        // later the select change will need a list of the table body names
        s.controlTbodyList.push(t.tbody);

        // Each table body has n number of control rows
        t.rows.forEach(c => {
            switch(c.type) {
                case 'color':     s[c.name] = new ColorRow(c); break;
                case 'range':     s[c.name] = new RangeRow(c); break;
                case 'buttons':
                    s[c.name] = new ButtonRow(c.buttons);
                    break;
                case 'select':    s[c.name] = new SelectRow(c); break;
                case 'textInput': s[c.name] = new TextInputRow(c); break;
                case 'group':     s[c.name] = new GroupRow(c); break;
                case 'stepList':  s[c.name] = new SteplistRow(c);
                    break;
                default: break;
            }
            if(s[c.name].tableRow) {
                //s[c.name].tableRow.style.backgroundColor = 'black';
                tbE.appendChild(s[c.name].tableRow);
            }
            if(s[c.name].tableBody) controlTable.appendChild(s[c.name].tableBody);
        });
        s.vStrokeNFill();
    });








    
    s.noneMode();

    // set the default selection for controls
    s.controlSelectChange('Main');

    s.resizeCanvasViewport();

    s.drawAll();
}

onresize = s.resizeCanvasViewport;
