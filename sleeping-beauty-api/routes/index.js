const express = require('express');
const router = express.Router();
const moment = require('moment');

const config = require('../config');
const logger = require('../logger');

const Alarm = require('../database').models.Alarm;

function executeIfValidToken(req, res, needed_token, callback) {
  let token = req.get("auth_token");
  logger.info(req.headers);

  if (token != needed_token) {
    logger.warn("Somebody tried to do %s with invalid or missing token " +
      "authorizing that action.", req.originalUrl);
    res.sendStatus(401);
    return;
  }

  callback();
}

// ============================================================================
// === BASIC AUTHORISATION REQUIRED ===========================================
// ============================================================================
// For these you need to include the correct basic access auth_token HTTP header

router.post('/setAlarm', function (req, res) {
  executeIfValidToken(req, res, config.tokens.basic_access, () => {
    let alarm = {
      isAlarmSet: true,
      alarmTime: req.body.desiredAlarmTime,
    };

    Alarm.findOneAndUpdate({}, alarm, { upsert: true, new: true, setDefaultsOnInsert: true }).exec()
    .then(() => {
      let humanReadableResponse = "Alarm was set for " +
        moment(req.body.desiredAlarmTime).format("kk:mm Z") + ".";
      res.json({
        humanReadableResponse,
      });
      logger.debug("/setAlarm says: " + humanReadableResponse);
    })
    .catch((err) => logger.error(err));
  });
});

router.get('/cancelAlarm', function (req, res) {
  executeIfValidToken(req, res, config.tokens.basic_access, () => {
    let alarm = {
      isAlarmSet: false,
      alarmTime: null,
    };

    Alarm.findOneAndUpdate({}, alarm, { new: true }).exec()
    .then(() => {
      let humanReadableResponse = "Canceled the alarm.";
      res.json({
        humanReadableResponse
      });
      logger.debug("/cancelAlarm says: " + humanReadableResponse);
    })
    .catch((err) => logger.error(err));
  });
});

router.get('/getAlarmInfo', function (req, res) {
  executeIfValidToken(req, res, config.tokens.basic_access, () => {
    Alarm.findOne({}, '-_id -__v').exec()
    .then((alarm) => {
      res.json(alarm);
      logger.debug("/getAlarmInfo says: Sent the newest alarm info.");
    })
    .catch((err) => logger.error(err));
  });
});

// ============================================================================
// === FULL ACCESS AUTHORISATION REQUIRED =====================================
// ============================================================================
// For these you need to include the correct full access auth_token HTTP header

router.get('/test-availability', function (req, res) {
  res.send("yeah we're good");
});

router.get('/get-all-alarms', function (req, res) {
  executeIfValidToken(req, res, config.tokens.full_access, () => {
    Alarm.find({}, '-_id -__v')
    .then(alarms => res.json(alarms))
    .catch((err) => console.error(err.message));
  });
});

router.delete('/delete-all-alarms', function (req, res) {
  executeIfValidToken(req, res, config.tokens.full_access, () => {
    Alarm.remove().exec()
    .then(() => {
      logger.info("deleted all alarms");
      res.send("deleted all alarms");
    })
    .catch((err) => logger.error(err));
    Alarm.collection.dropIndexes();
  });
});

module.exports = router;