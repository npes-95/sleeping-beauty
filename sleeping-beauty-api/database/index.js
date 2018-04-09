const Mongoose = require('mongoose');
const config = require('../config');
const logger = require('../logger');

// Connect to the database
if (process.env.MONGODB_URI) {
  logger.info("running on heroku, using mongo instance at %s", process.env.MONGODB_URI);
  Mongoose.connect(process.env.MONGODB_URI);
} else {
  logger.info("running somewhere random, using mongo instance at %s", 'mongodb://localhost/sleeping-buty-smart-alarm');
  Mongoose.connect('mongodb://localhost/sleeping-buty-smart-alarm');
}

// Throw an error if the connection fails
Mongoose.connection.on('error', function (err) {
  if (err) throw err;
});

// mpromise (mongoose's default promise library) is deprecated, 
// Plug-in your own promise library instead.
// Use native promises
Mongoose.Promise = global.Promise;

module.exports = {
  Mongoose,
  models: {
    Alarm: require('./AlarmModel')
  }
};