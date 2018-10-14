const moment = require('moment');
const {format} = require('../constants');

module.exports = class SaveModel {
    constructor(info) {

        this.info = info;
        this.date = moment().format(format);
    }

    toString(){
        return `${this.date}$${this.info},`;
    }
}
