class TextInputRow {
    constructor(p) {
        this.name        = p.name;
        this.label       = p.label;
        this.title       = p.title;
        this.onchange    = p.onchange;
        this.valRegex    = p.valRegex;
        this.value       = p.value;
        this.placeholder = p.placeholder

        // reused variables
        let trE, tdE, labelE, inputE;

        // capture this one, so it can be appended where it's wanted from the
        //  instance
        trE = document.createElement('tr');
        trE.title = this.title;
        this.tableRow = trE;

        // the label
        tdE = document.createElement('td');
        trE.appendChild(tdE);
        tdE.colSpan = 1;
        labelE = document.createElement('label');
        tdE.appendChild(labelE);
        labelE.htmlFor = `${this.name}TextInput`;
        labelE.textContent = this.label;

        // the input
        tdE = document.createElement('td');
        trE.appendChild(tdE);
        tdE.colSpan = 3;
        inputE = document.createElement('input');
        inputE.value = this.value;
        inputE.placeholder = this.placeholder;
        this.input = inputE;
        tdE.appendChild(inputE);
        this.input.id = `${this.name}TextInput`;
        if(this.valRegex) this.input.oninput = this.validate;
        if(this.onchange) this.input.onchange = this.onchange;
    }

    validate = () => {
        if(this.valRegex.test(this.input.value)) {
            this.input.style.color = 'white';
        } else {
            this.input.style.color = 'red';
        }
    }
}
