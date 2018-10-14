const SaveModel = require('../models/save');
const {logFile, currenciesFile} = require('../constants');
const fs = require('fs');

module.exports.saveLog = err => {

    const errModel = new SaveModel(err);

    fs.appendFile(logFile, '\n' + errModel.toString(), innerSaveingError => {
        if (innerSaveingError) {

            console.log('We had an error to save anything! Work better!')
            console.log(err, innerSaveingError);
        } else
            console.log(err)
    });
};



module.exports.saveCurrValue = value => {

    const currModel = new SaveModel(value);
    fs.appendFile(currenciesFile, currModel.toString(), err => {

        if (err) saveLog(err);
    });
};

