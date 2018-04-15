'use strict';

const logger = require('../logger');

const init = function () {

  return {
    tokens: {
      full_access: process.env.FULL_ACCESS_TOKEN || "dev-full-access-token",
      basic_access: process.env.BASIC_ACCESS_TOKEN || "dev-basic-access-token",
    }
  }
};

module.exports = init();

