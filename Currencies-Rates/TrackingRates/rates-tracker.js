const fs = require('fs');
const {
    Builder,
    By,
    Key,
    until
} = require('selenium-webdriver');
const { xpath, url } = require('./constants');
const SaveModel = require('./models/save');
const {saveCurrValue, saveLog} = require('./utils/files-manager');


const getCurrencyValue = async (driver) => {

    const element = await driver.findElement(By.xpath(xpath));
    return await element.getText();
};


module.exports = async () => {

    require('chromedriver');
    var webdriver = require('selenium-webdriver');
    var driver = new webdriver.Builder().forBrowser('chrome').build();

    await driver.get(url);
    console.log('Page Loaded!');

    setInterval(async () => {

        try {
            const currVal = await getCurrencyValue(driver);
            saveCurrValue(currVal);
        } catch (err) {
            const error = new SaveModel(err);
            console.log(err);
            saveLog(error);
        }
    }, 3000);
};