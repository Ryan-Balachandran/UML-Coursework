class RangeRow {
    constructor(p) {
        // set the data members of this object
        this.name    = p.name;
        this.label   = p.label;
        this.title   = p.title;
        this.value   = p.value;
        this.max     = p.max;
        this.min     = p.min;
        this.step    = p.step;

        // reused variables
        let trE, tdE, labelE, buttonE, inputE;

        // capture this one, so it can be appended where it's wanted from the
        //  instance
        trE = document.createElement('tr');
        this.tableRow = trE;

        // the range label
        tdE = document.createElement('td');
        trE.appendChild(tdE);
        labelE = document.createElement('label');
        tdE.appendChild(labelE);
        labelE.htmlFor = `${this.name}Range`;
        labelE.title = this.title;
        labelE.textContent = this.label;

        // the range input
        tdE = document.createElement('td');
        trE.appendChild(tdE);
        inputE = document.createElement('input');
        tdE.appendChild(inputE);
        this.range = inputE; // capture this one so methods have access to it
        inputE.type = 'range';
        inputE.id = `${this.name}Range`;
        inputE.max = this.max;
        inputE.min = this.min;
        inputE.step = this.step;
        inputE.value = this.value;
        inputE.oninput = this.set;

        // the up/down buttons
        tdE = document.createElement('td');
        trE.appendChild(tdE);

        buttonE = document.createElement('button');
        tdE.appendChild(buttonE);
        const that = this;
        buttonE.onclick = function() {
            that.set(that.value + 1);
        };
        buttonE.classList.add('halfButtons');
        buttonE.textContent = '⇧';

        buttonE = document.createElement('button');
        tdE.appendChild(buttonE);
        buttonE.onclick = function() {
            that.set(that.value - 1);
        };
        buttonE.classList.add('halfButtons');
        buttonE.textContent = '⇩';

        // the input
        tdE = document.createElement('td');
        trE.appendChild(tdE);
        inputE = document.createElement('input');
        tdE.appendChild(inputE);
        inputE.value = this.value;
        inputE.onchange = this.set;
        this.input = inputE; // capture this one so methods have access to it
    }

    set = newValue => {
        if(newValue.target) newValue = newValue.target.value;
        if(newValue < this.min) newValue = this.min;
        if(newValue > this.max) newValue = this.max;
        this.range.value = this.input.value = this.value = newValue;
        s.drawAll();
    }
}