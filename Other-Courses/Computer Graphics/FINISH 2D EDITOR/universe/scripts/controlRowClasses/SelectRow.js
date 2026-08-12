class SelectRow {
    constructor(p) {
        this.name = p.name;
        this.label = p.label;
        this.title = p.title;
        this.options = p.options;

        // reused variables
        let trE, tdE, labelE, selectE, optionE;

        // capture this one so it can be appended where it's wanted from the
        //  instance
        trE = document.createElement('tr');
        trE.title = this.title;
        this.tableRow = trE;

        // the select label
        tdE = document.createElement('td');
        trE.appendChild(tdE);
        tdE.colSpan = 1;
        labelE = document.createElement('label');
        tdE.appendChild(labelE);
        labelE.htmlFor = `${this.name}Select`;
        labelE.textContent = this.label;

        // the select
        tdE = document.createElement('td');
        trE.appendChild(tdE);
        tdE.colSpan = 3;
        selectE = document.createElement('select');
        this.select = selectE;
        tdE.appendChild(selectE);
        this.options.forEach(o => {
            optionE = document.createElement('option');
            selectE.appendChild(optionE);
            optionE.textContent = o.display;
            optionE.value = o.value;
        });
        selectE.onchange = this.selectChange;
    }

    selectChange = () => {
        const option = this.options.find(o => {
           return o.value === this.select.value;
        });
        if(option.onchange) option.onchange();
    }
}



