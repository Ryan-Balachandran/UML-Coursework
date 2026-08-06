s.loadControls = () => {
    s.controls = [
        {
            tbody: 'Main', rows: [
                // {
                //     type: 'select', name: 'background', label: 'BGI',
                //     title: 'Background image for the page',
                //     options: [
                //         {display: 'Wood', value:'wood', onchange:
                //             function () {
                //             s.backgroundImage('wood.webp', 'cover');}
                //         }, {display: 'Rock Bottom', value:'rockBottom', onchange:
                //             function () {
                //             s.backgroundImage('rockBottom.webp', 'cover');}
                //         }, {display: 'Blue Storm', value:'blueStorm', onchange:
                //             function () {
                //             s.backgroundImage('blueStorm.jpg', 'cover');}
                //         }, {display: 'City Lights', value:'cityLights', onchange:
                //             function () {
                //             s.backgroundImage('cityLights.jpg', 'cover');}
                //         }, {display: 'Micro Dark', value:'microDark', onchange:
                //             function () {
                //             s.backgroundImage('microorganismsDark.webp',
                //                 'repeat');}
                //         }
                //     ]
                // },
                {
                    type: 'select', name: 'shapeSelect',
                    label: 'Shape', title: 'Shape Mode',
                    options: [
                        {
                            value: 'none', display: 'None (esc)',
                            onchange: s.noneMode
                        },
                        {
                            value: 'line', display: 'Line (l)',
                            onchange: s.lineMode
                        },
                        {
                            value: 'arc', display: 'Arc (a)',
                            onchange: s.arcMode
                        },
                        {
                            value: 'rect', display: 'Rectangle (r)',
                            onchange: s.rectMode
                        },
                        {
                            value: 'text', display: 'Text (t)',
                            onchange: s.textMode
                        },
                        {
                            value: 'qCurve', display: 'Quadratic Curve (q)',
                            onchange: s.qCurveMode
                        },
                        {
                            value: 'bCurve', display: 'Bezier Curve (b)',
                            onchange: s.bCurveMode
                        },
                        {
                            value: 'scrim', display: 'Scrim (s)',
                            onchange: s.scrimMode
                        }
                    ]
                },
                {
                    type: 'color', name: 'shapeStrokeStyle', label: 'Stroke Style',
                    title: 'The default stroke style for all new shapes',
                    value: '#FFFFFF'
                },
                {
                    type: 'range', name: 'shapeStrokeAlpha', label: 'Stroke A',
                    title: 'The default alpha for strokes', value: 100,
                    max: 100, min: 0, step: 1
                },
                {
                    type: 'color', name: 'shapeFillStyle', label: 'Fill Style',
                    title: 'The default fill style for all new shapes',
                    value: '#FFFFFF'
                },
                {
                    type: 'range', name: 'shapeFillAlpha', label: 'Fill A',
                    title: 'The default alpha for fills', value: 100,
                    max: 100, min: 0, step: 1
                },
                {
                    type: 'range', name: 'lineWidth', label: 'Width',
                    title: 'The default line width for all new shapes',
                    value: 1, max: 100, min: 1, step: 1
                },
                {
                    type: 'select', name: 'lineCap', label: 'Ln Cap',
                    title: 'Line Cap',
                    options: [
                        { value: 'butt', display: 'Butt' },
                        { value: 'round', display: 'Round' },
                        { value: 'square', display: 'Square' }
                    ]
                },
                {
                    type: 'select', name: 'lineJoin', label: 'Ln Join',
                    title: 'Line Join',
                    options: [
                        { value: 'miter', display: 'Miter' },
                        { value: 'round', display: 'Round' },
                        { value: 'bevel', display: 'Bevel' }
                    ]
                },
                {
                    type: 'textInput', name: 'lineDash', label: 'Ln Dash',
                    title: 'Line Dash - Enter a list of positive whole ' +
                        'numbers, each followed by at least one space.',
                    valRegex: /^\s*(\d+(\.\d+)?\s*,*\s*){2,}$/, value: '',
                    placeholder: '# # # #'
                },
                {
                    type: 'select', name: 'composite', label: 'Comp',
                    title: 'composite operations for new shapes',
                    options: [
                        { value: 'source-over', display: 'Source Over' },
                        { value: 'source-in', display: 'Source In' },
                        { value: 'source-out', display: 'Source Out' },
                        { value: 'source-atop', display: 'Source Atop' },
                        { value: 'destination-over', display: 'Destination Over' },
                        { value: 'destination-in', display: 'Destination In' },
                        { value: 'destination-out', display: 'Destination Out' },
                        { value: 'destination-atop', display: 'Destination Atop' },
                        { value: 'lighter', display: 'Lighter' },
                        { value: 'copy', display: 'Copy' },
                        { value: 'xor', display: 'Xor' },
                        { value: 'screen', display: 'Screen' },
                        { value: 'overlay', display: 'Overlay' },
                        { value: 'darken', display: 'Darken' },
                        { value: 'lighten', display: 'Lighten' },
                        { value: 'color-dodge', display: 'Color Dodge' },
                        { value: 'color-burn', display: 'Color Burn' },
                        { value: 'soft-light', display: 'Soft Light' },
                        { value: 'difference', display: 'Difference' },
                        { value: 'exclusion', display: 'Exclusion' },
                        { value: 'hue', display: 'Hue' },
                        { value: 'saturation', display: 'Saturation' },
                        { value: 'color', display: 'Color' },
                        { value: 'luminosity', display: 'Luminosity' }
                    ]
                },
                { // at least one should be enabled
                    type: 'buttons', name: 'fillNStrokeButtonsRow', buttons: [
                        {
                            name: 'fillNewShapes', colspan: 2, display: 'Fill',
                            click: s.fillNewShapeClick,
                            title: 'Any new shapes that can be filled will be.'
                        },
                        {
                            name: 'strokeNewShapes', colspan: 2, display: 'Stroke',
                            click: s.strokeNewShapeClick,
                            title: 'Any new shapes that can be stroked will be.'
                        }
                    ]
                },
                {
                    type: 'textInput', name: 'textShape', label: 'Text',
                    title: 'Text to be rendered', value: 'Hello World!'
                },
                {
                    type: 'range', name: 'fontSize', label: 'Font PX',
                    title: 'Font Size', value: 50, max: 200, min: 1, step: 1
                },
                {
                    type: 'select', name: 'fontFamily', label: 'Font FM',
                    title: 'Font Family',
                    options: [
                        { value: 'serif', display: 'Serif' },
                        { value: 'sans-serif', display: 'Sans Serif' },
                        { value: 'monospace', display: 'Monospace' },
                        { value: 'cursive', display: 'Cursive' },
                        { value: 'fantasy', display: 'Fantasy' },
                        { value: 'system-ui', display: 'System UI' },
                        { value: 'ui-serif', display: 'UI Serif' },
                        { value: 'ui-sans-serif', display: 'UI Sans Serif' },
                        { value: 'ui-monospace', display: 'UI Monospace' },
                        { value: 'ui-rounded', display: 'UI Rounded' },
                        { value: 'emoji', display: 'Emoji' },
                        { value: 'math', display: 'Math' },
                        { value: 'fangsong', display: 'Fangsong' }
                    ]
                },
                {
                    type: 'stepList', name: 'stepListRow'
                },
                {
                    type: 'buttons', name: 'resetButtonsRow', buttons: [
                        {
                            name: 'reset', colspan: 4, display: 'Reset',
                            click: s.reset, title: 'Reset everything'
                        }
                    ]
                }
            ]
        }
    ];
}

