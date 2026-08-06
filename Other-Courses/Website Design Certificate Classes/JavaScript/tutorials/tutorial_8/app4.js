// Object Literal
const object1 = new Object();
object1.first = 'Laurence';
object1['last'] = 'Svekis';
object1.fullName = function() {
     return `${tjis.first} ${this.last}`;
}

console.log(object1.fullName);

const object2 = {
     first : 'Laurence',
     last : 'Svekis',
     fullName : function() {
          return `${this.first} ${this.last}`
     },
     full : () => `${object2.first} ${object2.last}`
};
