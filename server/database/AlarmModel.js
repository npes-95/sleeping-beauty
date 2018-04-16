const mongoose = require('mongoose');
const Schema = mongoose.Schema;

let AlarmSchema = Schema({
  alarmTime: {type: Date},
  isAlarmSet: String,
});

let Alarm = mongoose.model('Alarm', AlarmSchema);

module.exports = Alarm;