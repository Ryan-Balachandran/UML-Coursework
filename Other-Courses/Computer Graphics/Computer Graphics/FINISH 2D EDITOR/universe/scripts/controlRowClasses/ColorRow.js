class ColorRow {
    constructor(p) {
        // set the data members of this object
        this.name = p.name;
        this.label = p.label;
        this.title = p.title;
        this.value = p.value;
        this.oninput = p.oninput;

        // reused variables
        let trE, tdE, labelE, inputE;

        // capture this one, so it can be appended where it's wanted
        trE = document.createElement('tr');
        this.tableRow = trE;
        trE.title = this.title;

        // the label
        tdE = document.createElement('td');
        trE.appendChild(tdE);
        tdE.colSpan = 2;
        labelE = document.createElement('label');
        tdE.appendChild(labelE);
        labelE.htmlFor = `${this.name}Color`;
        labelE.textContent = this.label;

        // the input
        tdE = document.createElement('td');
        trE.appendChild(tdE);
        tdE.colSpan = 2;
        inputE = document.createElement('input');
        tdE.appendChild(inputE);
        this.input = inputE; // capture this one so methods have access to it
        inputE.type = 'color';
        inputE.id = `${this.name}Color`;
        inputE.value = this.value;
        inputE.oninput = this.set;
    }

    // the c in MVC
    set = newValue => { // this method can be called with an event or a value
        if(newValue.currentTarget) newValue = // event
            newValue.currentTarget.value;
        this.value = newValue;
        this.show();
    }

    // the v in MVC
    show() {
        this.input.value = this.value;
        if(this.oninput) this.oninput();
    }
}