const _ = require('underscore');
const request = require('request');
const express = require('express');
const app = express();
const bodyParser = require('body-parser');
const cors = require('cors');
const server = require('http').createServer(app);
const mongoose = require('mongoose');

const logger = require('./logger');
const routes = require('./routes');

// Routing
app.use(bodyParser.json());
app.use(cors());
app.use((req, res, next) => {
    res.header('Access-Control-Allow-Headers', 'Content-Type,Authorization,auth_token');
    next();
});

app.use('/', routes);
app.set('json spaces', 2);

let port = process.env.PORT || 3000;

logger.info("Server litnening on port %s", port);
server.listen(port, "0.0.0.0");

// pings itself, keeps the free-tier heroku from going to sleep
const http = require("http");
setInterval(function() {
  http.get("https://sleeping-beauty-api.herokuapp.com/test-availability");
}, 300000); // every 5 minutes (300000)
